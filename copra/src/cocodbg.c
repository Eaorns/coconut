#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>
#include <ctype.h>

#include "ccngen/ast.h"
#include "ccngen/debugger_helper.h"
#include "ccn/ccn_dbg.h"
#include "palm/str.h"
#include "palm/watchpoint.h"

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_BBLUE    "\x1b[94m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_BMAGENTA "\x1b[95m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

/**
 *  Declare command functions
 */

int comm_tree(char*);
int comm_view(char*);
int comm_goto(char*);
int comm_quit(char*);
int comm_help(char*);

argument args_tree_get[] = {{"first", "Get first", NULL},
                            {"last",  "Get last",  NULL},
                            {(char*)NULL, NULL, NULL}};

argument args_tree[] = {{"get", "Get an element from the tree", args_tree_get},
                        {"set", "Set an element in the tree",   NULL},
                        {(char*)NULL, NULL, NULL}};

argument args_view[] = {{"current", "Get an element from the tree", NULL},
                        {"parent",  "Set an element in the tree",   NULL},
                        {(char*)NULL, NULL, NULL}};

argument args_goto[] = {{"child",  "Move to a given child (by name or index)", NULL},
                        {"parent", "Move to the parent",   NULL},
                        {(char*)NULL, NULL, NULL}};

command commands[] = {{"tree",  "t", comm_tree,  "Interact with the tree", args_tree},
                      {"view",  "v", comm_view,  "Display a node and its history", args_view},
                      {"goto",  "m", comm_goto,  "Go to another node", args_goto},
                      {"quit",  "q", comm_quit,  "Exit debug view", NULL},
                      {"help",  "h", comm_help,  "Display possible commands", NULL},
                      {(char*)NULL, NULL, (comm_func_t*)NULL, (char*)NULL, NULL}};

struct ccn_node *curr_node;
void cocodbg_start(struct ccn_node *start_node)
{
    ccndbg_repl_commands = commands;
    curr_node = start_node;
    // watchpoint_disable_all();
    cocodbg_repl();
    // watchpoint_enable_all();
}


bool isnumber(char *str)
{
    while (str[0]) {
        if (!isdigit(str[0]))
            return false;
        str++;
    }
    return true;
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
                printf(ANSI_COLOR_BBLUE"(nil)"ANSI_COLOR_RESET"("ANSI_COLOR_YELLOW"-1"ANSI_COLOR_RESET", "ANSI_COLOR_CYAN"%p"ANSI_COLOR_RESET")", data);
            }
            else {
                printf(ANSI_COLOR_BBLUE"%s"ANSI_COLOR_RESET"("ANSI_COLOR_YELLOW"%i"ANSI_COLOR_RESET", "ANSI_COLOR_CYAN"%p"ANSI_COLOR_RESET")", 
                       DBGHelper_nodename(NODE_TYPE(*(node_st**)data)), NODE_ID(*(node_st**)data), data);
                if (NODE_TRASHED(*(node_st**)data))
                    printf(ANSI_COLOR_RED" (trashed)"ANSI_COLOR_RESET);
            }
            break;
        case HDT_link_or_enum:
            printf("enum %i", *(int*)data);
            break;
        case HDT_int:
            printf("%i", *(int*)data);
            break;
        case HDT_string:
            printf("\"%s\"", (char*)data);
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

void print_hist(hist_item *hitem, enum H_DATTYPES dattype)
{
    bool skipping = false;
    int j;
    hist_item *hitem_prev;

    for (j = 0; hitem; j++) {
        // 'May be uninitialized'-bug in GCC!
        if (hitem_prev && hitem->val == hitem_prev->val && hitem->rip == hitem_prev->rip) {
            if (!skipping) {
                printf("   ...\n");
                skipping = true;
            }
            hitem_prev = hitem;
            hitem = hitem->next;
            continue;
        }
        if (skipping) {
            printf("   #%i ", j-1);
            print_val(dattype, &(hitem_prev->val));
            char **funcname = backtrace_symbols(&(hitem_prev->rip), 1);
            printf(" at %s\n", funcname[0]);
            free(funcname);
            skipping = false;
        }
        printf("   #%i ", j);
        print_val(dattype, &(hitem->val));
        char **funcname = backtrace_symbols(&(hitem->rip), 1);
        printf(" at %s\n", funcname[0]);
        free(funcname);
        hitem_prev = hitem;
        hitem = hitem->next;
    }
    if (skipping) {
        printf("   #%i ", j-1);
        print_val(dattype, &(hitem_prev->val));
        char **funcname = backtrace_symbols(&(hitem_prev->rip), 1);
        printf(" at %s\n", funcname[0]);
        free(funcname);
    }
}


/**
 *  Define command functions
 */

int comm_tree(char *comm)
{
    char *token = strtok(comm, " ");
    if (token == NULL) {
        printf("'tree' requires additional arguments.\n");
        return -1;
    }

    switch (parse_arg(args_tree, token)) {
    case 0:
        printf("Tree get '%s'\n", strtok(NULL, ""));
        break;
    case 1:
        printf("Tree set '%s'\n", strtok(NULL, ""));
        break;
    default:
        printf("Unknown argument '%s' for command 'tree'\n", token);
        return -1;
    }

    return 0;
}

int comm_view(char *comm __attribute__((unused)))
{
    printf("  node %s (index %i, addr %p)\n", 
           DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
    char *valname = DBGHelper_iton(NODE_TYPE(curr_node), 0);
    ccn_hist *hist = NODE_HIST(curr_node);
    for (int i = 0; valname; valname = DBGHelper_iton(NODE_TYPE(curr_node), ++i)) {
        printf("%i: "ANSI_COLOR_BMAGENTA"%s"ANSI_COLOR_RESET" -- ", i, valname);
        print_val(DBGHelper_gettype(NODE_TYPE(curr_node), i), DBGHelper_getptr(curr_node, i));
        printf("\n");

        print_hist(DBGHelper_nodehist(NODE_TYPE(curr_node), hist, i), DBGHelper_gettype(NODE_TYPE(curr_node), i));
    }   
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
            printf("\nMoved to child %i (node %s (index %i, addr %p))\n\n", 
                   idx, DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
            break;
        case 1:
            if (NODE_PARENT(curr_node)) {
                curr_node = NODE_PARENT(curr_node);
                printf("\nMoved to parent (node %s (index %i, addr %p))\n\n", 
                       DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
            }
            else
                printf("Current node has no parent!\n");
            break;
        default:
            break;  
    }
    fflush(stdout);
    return 0;
}

int comm_quit(char *comm __attribute__((unused)))
{
    ccndbg_repl_done = 1;
    return 0;
}

int comm_help(char *comm __attribute__((unused)))
{
    printf("TODO: loop through commands and print their description.\n");
    return 0;
}
