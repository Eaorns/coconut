#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h>
#include <unistd.h>
#include <err.h>

#include "ccngen/ast.h"
#include "ccngen/debugger_helper.h"
#include "ccn/dynamic_core.h"
#include "ccn/phase_driver.h"
#include "ccn/action_types.h"
#include "ccn/ccn_dbg.h"
#include "palm/str.h"
#include "palm/memory.h"
#include "palm/watchpoint.h"

#ifdef INCLUDE_DEBUGGER

#define ANSI_COLOR_BLACK    "\x1b[30m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BRED     "\x1b[91m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_BGREEN   "\x1b[92m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BYELLOW  "\x1b[93m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_BBLUE    "\x1b[94m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_BMAGENTA "\x1b[95m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_BCYAN    "\x1b[96m"
#define ANSI_BG_RED         "\x1b[41m"
#define ANSI_BG_GREEN       "\x1b[42m"
#define ANSI_BG_YELLOW      "\x1b[43m"
#define ANSI_RESET          "\x1b[0m"

char *executable_name = NULL;
bool current_path_initialized = false;
char current_path[256];

size_t curr_ast_state = (size_t)-1;

/**
 *  Declare command functions
 */

int comm_view(char*);
int comm_list(char*);
int comm_setv(char*);
int comm_goto(char*);
int comm_tree(char*);
int comm_rern(char*);
int comm_quit(char*);
int comm_cont(char*);
int comm_help(char*);

argument args_list[] = {{"travhist", "Print all past traversals", NULL},
                        {(char*)NULL, NULL, NULL}};

argument args_goto[] = {{"child",  "Move to a given child (by name or index)", NULL},
                        {"parent", "Move to the parent",                       NULL},
                        {(char*)NULL, NULL, NULL}};

argument args_tree[] = {{"revert", "Change the state of the tree to the given point. Can be forward.", NULL},
                        {(char*)NULL, NULL, NULL}};

argument args_rern[] = {{"last", "Restart last traversal", NULL},
                        {(char*)NULL, NULL, NULL}};

command commands[] = {{"view",     "v", comm_view, "Display a node and its history",           NULL},
                      {"list",     "l", comm_list, "Print information about a given argument", args_list},
                      {"set",      "s", comm_setv, "Change a value in a node",                 NULL},
                      {"goto",     "g", comm_goto, "Move to another node",                     args_goto},
                      {"tree",     "t", comm_tree, "Change the state of the tree",             args_tree},
                      {"rerun",    "r", comm_rern, "Rerun from a given traversal",             args_rern},
                      {"quit",     "q", comm_quit, "Exit debugger and exit program",           NULL},
                      {"continue", "c", comm_cont, "Exit debugger and continue execution",     NULL},
                      {"help",     "h", comm_help, "Display possible commands",                NULL},
                      {(char*)NULL, NULL, (comm_func_t*)NULL, (char*)NULL, NULL}};

bool node_exists(node_st *ptr);
char *run_addr2line(void *addr);
char *strip_path(char *path);

node_st *curr_node;
int cocodbg_start(node_st *start_node)
{
    if (!current_path_initialized) {
        (void)!getcwd(current_path, 255);
        current_path_initialized = true;
    }
    ccndbg_repl_commands = commands;
    if (curr_node != NULL && start_node != CCNgetRootNode() && !node_exists(start_node))
        curr_node = CCNgetRootNode();
    else
        curr_node = start_node;

    if (CCNisSegfaulting()) {
        Dl_info func_info = { 0 };
        void *rip = (void*)(CCNgetCrashContext()->uc_mcontext.gregs[REG_RIP]);
        dladdr(rip, &func_info);
        printf("\n"ANSI_COLOR_BLACK ANSI_BG_YELLOW"Segfault generated at %s"ANSI_RESET"\n",
               strip_path(run_addr2line((void*)((char*)rip - (char*)func_info.dli_fbase))));
    }
    printf("\n "ANSI_COLOR_GREEN"-- Starting CoCoNut debugger --"ANSI_RESET"\n\n");

    if (!executable_name) {
        printf("Executable name not set! please specify to be able to get files and lines of operations.\n\n");
    }

    curr_ast_state = (size_t)-1;

    int retc = cocodbg_repl();

    if (curr_ast_state != (size_t)-1) {
        node_st *node, **nodelist = get_node_tracker_list();
        hist_item *hist, **hist_ptr;
        for (size_t i = 0; i < get_node_id_counter(); i++) {
            node = nodelist[i];
            if (node == NULL)
                continue;
            for (int j = 0; j < DBGHelper_node_numvals(NODE_TYPE(node)); j++) {
                hist_ptr = DBGHelper_nodehist(NODE_TYPE(node), NODE_HIST(node), j);
                hist = *hist_ptr;
                while (hist != NULL && hist->action >= curr_ast_state) {
                    *hist_ptr = hist->next;
                    free(hist);
                    hist = *hist_ptr;
                }
            }
        }
    }

    // Assumes watchpoints have already been disabled and will re re-enabled by caller.
    return retc;
}


bool isnumber(char *str)
{
    if (str[0] == '\0')
        return false;

    while (str[0]) {
        if (!isdigit(str[0]))
            return false;
        str++;
    }
    return true;
}

bool ishex(char *str)
{
    if (str[0] != '0' || str[1] != 'x')
        return false;
    str += 2;

    if (str[0] == '\0')
        return false;

    while (str[0]) {
        if (!isxdigit(str[0]))
            return false;
        str++;
    }
    return true;
}

char *strip_path(char *path)
{
    size_t len = STRlen(current_path);
    if (len > 1 && STReqn(current_path, path, len)) {
        path += len - 1;
        if (path[1] != '/') {
            path--;
            path[1] = '/';
        }
        path[0] = '.';
    }
    return path;
}

node_st *find_node_by_id(size_t id)
{
    if (get_node_id_counter() <= id)
        return NULL;
    return get_node_tracker_list()[id];
}

bool node_exists(node_st *ptr)
{
    if (ptr == NULL)
        return false;
    node_st **node_tracker_list = get_node_tracker_list();
    for (size_t i = 0; i < get_node_id_counter(); i++) {
        if (node_tracker_list[i] == ptr)
            return true;
    }
    return false;
}

char *run_addr2line(void *addr)
{
    if (!executable_name)
        return "??:??";
    char command[128];
    snprintf(command, 128, "addr2line -e %s %p", executable_name, addr);
    FILE *out = popen(command, "r");
    char *output = MEMmalloc(256);
    char c = fgetc(out);
    int i;
    for (i = 0; i < 255 && c != '\r' && c != '\n' && c != EOF; i++) {
        output[i] = c;
        c = fgetc(out);
    }
    output[i] = '\0';
    pclose(out);
    return output;
}

char *color_addrline(char *str)
{
    char *path = strtok(str, ":");
    char *line = strtok(NULL, "");
    return STRcatn(7, ANSI_COLOR_BCYAN, path, ANSI_RESET, ":", ANSI_COLOR_YELLOW, line, ANSI_RESET);
}


void print_val(enum H_DATTYPES type, void *data)
{
    if (data == NULL) {
        printf("(null)");
        return;
    }
    switch (type) {
        case HDT_NULL:
            printf("(null)");
            break;
        case HDT_user:
            printf("user (%p)", data);
            break;
        case HDT_link:
            /* Assume the node is invalid if the first value (node_type) is 0 */
            if (*(int*)data == 0) {
                printf(ANSI_COLOR_BBLUE"(nil)"ANSI_RESET"("ANSI_COLOR_YELLOW"-1"ANSI_RESET", "ANSI_COLOR_CYAN"%p"ANSI_RESET")", data);
            }
            else {
                printf(ANSI_COLOR_BBLUE"%s"ANSI_RESET"("ANSI_COLOR_YELLOW"%li"ANSI_RESET", "ANSI_COLOR_CYAN"%p"ANSI_RESET")",
                       DBGHelper_nodename(NODE_TYPE(*(node_st**)data)), NODE_ID(*(node_st**)data), (void*)*(node_st**)data);
                if (NODE_TRASHED(*(node_st**)data))
                    printf(ANSI_COLOR_RED" (trashed)"ANSI_RESET);
            }
            break;
        case HDT_link_or_enum:
            printf("enum %i", *(int*)data);
            break;
        case HDT_int:
            printf("%i", *(int*)data);
            break;
        case HDT_string:
            printf("\"%s\"", *(char**)data);
            break;
        case HDT_bool:
            printf("%s", ((*(int*)data) ? "true" : "false"));
            break;
        case HDT_int8:
            printf("%i", *(int8_t*)data);
            break;
        case HDT_int16:
            printf("%i", *(int16_t*)data);
            break;
        case HDT_int32:
            printf("%i", *(int32_t*)data);
            break;
        case HDT_int64:
            printf("%li", *(int64_t*)data);
            break;
        case HDT_float:
            printf("%f", *(float*)data);
            break;
        case HDT_double:
            printf("%f", *(double*)data);
            break;
        case HDT_uint:
            printf("%lu", *(size_t*)data);
            break;
        case HDT_uint8:
            printf("%u", *(uint8_t*)data);
            break;
        case HDT_uint16:
            printf("%u", *(uint16_t*)data);
            break;
        case HDT_uint32:
            printf("%u", *(uint32_t*)data);
            break;
        case HDT_uint64:
            printf("%lu", *(uint64_t*)data);
            break;
    }
}

void print_trav_hist()
{
    enum ccn_action_id *action_hist = CCNgetActionHist();
    for (size_t i = 1; i <= CCNgetCurrentActionCtr(); i++) {
        printf("  #%lu: \t%s\n", i, CCNgetActionFromID(action_hist[i])->name);
    }
    printf("\n");
}

void print_node_hist_line(int i, hist_item *hitem, enum H_DATTYPES dattype)
{
    if (hitem->rip == (void*)-1) {
        printf("   #%i ", i);
        print_val(dattype, &(hitem->val));
        printf(", in debugger\n");
    } else {
        Dl_info func_info = { 0 };
        printf("   #%i ", i);
        print_val(dattype, &(hitem->val));
        dladdr(hitem->rip, &func_info);
        printf(", %s() at %s", func_info.dli_sname, color_addrline(strip_path(run_addr2line((void*)((char*)hitem->rip - (char*)func_info.dli_fbase)))));
        printf(" (action %lu: %s)\n", hitem->action, CCNgetActionFromID(CCNgetActionHist()[hitem->action])->name);
    }

}

void print_node_hist(hist_item *hitem, enum H_DATTYPES dattype)
{
    bool skipping = false;
    int j;
    hist_item *hitem_prev = NULL;

    for (j = 0; hitem; j++) {
        // 'May be uninitialized'-bug in GCC!
        if (hitem_prev && hitem->val == hitem_prev->val && hitem->rip == hitem_prev->rip && hitem->action == hitem_prev->action) {
            if (!(!skipping && hitem->next && (hitem->val != hitem->next->val || hitem->rip != hitem->next->rip || hitem->action != hitem->next->action))) {
                if (!skipping) {
                    printf("   ...\n");
                    skipping = true;
                }
                hitem_prev = hitem;
                hitem = hitem->next;
                continue;
            }
        }
        if (skipping) {
            print_node_hist_line(j-1, hitem_prev, dattype);
            skipping = false;
        }
        print_node_hist_line(j, hitem, dattype);
        hitem = hitem->next;
    }
    if (skipping) {
        print_node_hist_line(j-1, hitem_prev, dattype);
    }
}

void setAST(size_t action)
{
    node_st *node, **nodelist = get_node_tracker_list();
    hist_item *hist;
    for (size_t i = 0; i < get_node_id_counter(); i++) {
        node = nodelist[i];
        if (node == NULL)
            continue;
        for (int j = 0; j < DBGHelper_node_numvals(NODE_TYPE(node)); j++) {
            hist = *DBGHelper_nodehist(NODE_TYPE(node), NODE_HIST(node), j);
            while (hist != NULL && hist->action >= action)
                hist = hist->next;
            if (hist != NULL)
                DBGHelper_setval(node, j, hist->val);
        }
    }
    curr_ast_state = action;
}

/**
 *  Define command functions
 */

int comm_view(char *comm __attribute__((unused)))
{
    printf("  node %s (index %li, addr %p)\n",
           DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
    char *valname = DBGHelper_iton(NODE_TYPE(curr_node), 0);
    ccn_hist *hist = NODE_HIST(curr_node);
    for (int i = 0; valname; valname = DBGHelper_iton(NODE_TYPE(curr_node), ++i)) {
        printf("%i: "ANSI_COLOR_BMAGENTA"%s"ANSI_RESET" -- ", i, valname);
        print_val(DBGHelper_gettype(NODE_TYPE(curr_node), i), DBGHelper_getptr(curr_node, i));
        printf("\n");

        print_node_hist(*DBGHelper_nodehist(NODE_TYPE(curr_node), hist, i), DBGHelper_gettype(NODE_TYPE(curr_node), i));
    }
    return 0;
}

int comm_list(char *comm)
{
    char *token = strtok(comm, " ");
    if (token == NULL) {
        printf("'print' requires additional arguments.\n");
        return -1;
    }
    switch (parse_arg(args_list, token)) {
        case 0:
            print_trav_hist();
            break;
        default:
            printf("Invalid argument '%s' given!\n", token);
    }
    return 0;
}

int comm_setv(char *comm)
{
    int idx = -1;
    char *token = strtok(comm, " ");
    if (!token) {
        printf("Please specify a child by name or index!\n");
        return -1;
    }
    if (isnumber(token)) {
        idx = atoi(token);
    } else {
        idx = DBGHelper_ntoi(NODE_TYPE(curr_node), token);
    }
    if (idx == -1) {
        printf("Given value is not a field of the current node!\n");
        return -1;
    }

    token = strtok(NULL, " ");

    void *val;
    if (isnumber(token)) {
        val = (void*)strtol(token, NULL, 10);
    } else if (ishex(token)) {
        val = (void*)strtol(token + 2, NULL, 16);
    } else if (STReq(token, "true")) {
        val = (void*)1;
    } else if (STReq(token, "false")) {
        val = (void*)0;
    } else {
        printf("Please specify a value or address!\n");
        return -1;
    }

    DBGHelper_setval(curr_node, idx, val);

    // TODO add hist entry
    hist_item **hist_ptr = DBGHelper_nodehist(NODE_TYPE(curr_node), NODE_HIST(curr_node), idx);
    hist_item *new_hist = MEMmalloc(sizeof(hist_item));
    new_hist->val = val;
    new_hist->rip = (void*)-1;
    new_hist->action = (size_t)-1;
    new_hist->next = *hist_ptr;
    *hist_ptr = new_hist;

    return 0;
}

int comm_goto(char *comm)
{
    char *token = strtok(comm, " ");
    if (token == NULL) {
        printf("'goto' requires additional arguments.\n");
        return -1;
    }
    node_st *new_node;
    int idx = -1;
    switch (parse_arg(args_goto, token)) {
        case 0:
            token = strtok(NULL, " ");
            if (!token) {
                printf("Please specify a child by name or index!\n");
                break;
            }
            if (isnumber(token)) {
                idx = atoi(token);
            } else {
                idx = DBGHelper_ntoi(NODE_TYPE(curr_node), token);
            }
            if (idx == -1 || !DBGHelper_ischild(NODE_TYPE(curr_node), idx)) {
                printf("Given value is not a child of the current node!\n");
                break;
            }
            new_node = *(node_st**)DBGHelper_getptr(curr_node, idx);
            if (new_node == NULL) {
                printf("The given child has value NULL, cannot goto.\n");
                break;
            }
            curr_node = new_node;
            printf("\nMoved to child %i (node %s (index %li, addr %p))\n\n",
                   idx, DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
            break;
        case 1:
            if (NODE_PARENT(curr_node)) {
                curr_node = NODE_PARENT(curr_node);
                printf("\nMoved to parent (node %s (index %li, addr %p))\n\n",
                       DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
            }
            else
                printf("Current node has no parent!\n");
            break;
        default:
            if (isnumber(token)) {
                idx = atoi(token);
                new_node = find_node_by_id(idx);
            } else if (ishex(token)) {
                new_node = (node_st*)strtol(token + 2, NULL, 16);
                if (!node_exists(new_node)) {
                    printf("The given address does not contain a node!\n");
                    break;
                }
            } else {
                printf("Please specify a node by id or address, or give a subargument like 'parent' or 'child'\n");
                break;
            }
            curr_node = new_node;
            printf("\nMoved to %s (node %s (index %li, addr %p))\n\n",
                   token, DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
            break;
    }
    fflush(stdout);
    return 0;
}

int comm_tree(char *comm)
{
    char *token = strtok(comm, " ");
    switch (parse_arg(args_tree, token)) {
        case 0:
            token = strtok(NULL, " ");
            if (!isnumber(token))
                printf("Please provide a point to revert the AST to!\n");
            else
                setAST(atoi(token));
            break;
        default:
            break;
    }
    return 0;
}

int comm_rern(char *comm)
{
    char *token = strtok(comm, " ");
    switch (parse_arg(args_rern, token)) {
        case 0:
            ccndbg_repl_done = 3;
            return 0;
        default:
            break;
    }

    if (!isnumber(token)) {
        printf("Please provide the number of the action to restart from.\n");
        return -1;
    }
    // TODO atoi cannot handle same sizes as size_t
    size_t action = (size_t)atoi(token);
    if (!CCNstartRestartAt(action)) {
        printf("Invalid action given!\n");
    }
    printf("Restarting from action %lu (%s). Exiting debugger...\n\n", action,
           CCNgetActionFromID(CCNgetActionHist()[action])->name);
    ccndbg_repl_done = 3;
    return 0;
}

int comm_quit(char *comm __attribute__((unused)))
{
    ccndbg_repl_done = 1;
    return 0;
}

int comm_cont(char *comm __attribute__((unused)))
{
    ccndbg_repl_done = 2;
    return 0;
}

int comm_help(char *comm __attribute__((unused)))
{
    // TODO: also print arguments
    for (int i = 0; commands[i].command != NULL; i++) {
        printf("%s (%s): \t%s\n", commands[i].command, commands[i].alt, commands[i].desc);
        if (commands[i].args != NULL) {
            for (int j = 0; commands[i].args[j].arg != NULL; j++) {
                printf("  - %s: \t  %s\n", commands[i].args[j].arg, commands[i].args[j].desc);
            }
        }
    }
    printf("\n");
    return 0;
}

#endif