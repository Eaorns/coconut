#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>

#include "ccngen/ast.h"
#include "ccngen/debugger_helper.h"
#include "ccn/ccn_dbg.h"
#include "palm/str.h"
#include "palm/watchpoint.h"

/**
 *  Declare command functions
 */

int comm_tree(char*);
int comm_view(char*);
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

command commands[] = {{"tree",  "t", comm_tree,  "Interact with the tree", args_tree},
                      {"view",  "v", comm_view,  "Display a node and its history", args_view},
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
            printf("user (%p)", (void*)*(long*)data);
            break;
        case HDT_link:
            printf("node %s(%i, %p)", DBGHelper_nodename(NODE_TYPE(*(node_st**)data)), NODE_ID(*(node_st**)data), (void*)*(long*)data);
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

int comm_view(char *comm)
{
    printf("  node %s (index %i, addr %p)\n", DBGHelper_nodename(NODE_TYPE(curr_node)), NODE_ID(curr_node), (void*)curr_node);
    // enum H_DATTYPES dattype = DBGHelper_gettype(NODE_TYPE(curr_node), 0);
    char *valname = DBGHelper_iton(NODE_TYPE(curr_node), 0);
    ccn_hist *hist = NODE_HIST(curr_node);
    hist_item *hitem, *hitem_prev;
    bool skipping = false;
    int j;
    for (int i = 0; valname; valname = DBGHelper_iton(NODE_TYPE(curr_node), ++i)) {
        printf("%i: %s  \t", i, valname);
        print_val(DBGHelper_gettype(NODE_TYPE(curr_node), i), DBGHelper_getptr(curr_node, i));
        printf("\n");

        hitem = DBGHelper_nodehist(NODE_TYPE(curr_node), hist, i);
        hitem_prev = NULL;
        skipping = false;
        for (j = 0; hitem; j++) {
            printf("enter %p...\n", hitem);
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
                print_val(DBGHelper_gettype(NODE_TYPE(curr_node), i), &(hitem_prev->val));
                char **funcname = backtrace_symbols(&(hitem_prev->rip), 1);
                printf(" at %s\n", funcname[0]);
                free(funcname);
                skipping = false;
            }
            printf("   #%i ", j);
            print_val(DBGHelper_gettype(NODE_TYPE(curr_node), i), &(hitem->val));
            char **funcname = backtrace_symbols(&(hitem->rip), 1);
            printf(" at %s\n", funcname[0]);
            free(funcname);
            hitem_prev = hitem;
            printf("asdfasdfasdf\n");
            hitem = hitem->next;
            printf("asdfasdfasdf\n");
        }
        printf("Done with %i\n", i);
        if (skipping) {
            printf("   #%i ", j-1);
            print_val(DBGHelper_gettype(NODE_TYPE(curr_node), i), &(hitem_prev->val));
            char **funcname = backtrace_symbols(&(hitem_prev->rip), 1);
            printf(" at %s\n", funcname[0]);
            free(funcname);
        }
    }
    // printf("Print '%s'\n", comm);
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
