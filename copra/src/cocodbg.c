#include <stdio.h>
#include <string.h>

#include "ccn/ccn_dbg.h"

/**
 *  Declare command functions
 */

int comm_tree(char*);
int comm_print(char*);
int comm_quit(char*);
int comm_help(char*);

argument args_tree_get[] = {{"first", "Get first", NULL},
                            {"last",  "Get last",  NULL},
                            {(char*)NULL, NULL, NULL}};

argument args_tree[] = {{"get", "Get an element from the tree", args_tree_get},
                        {"set", "Set an element in the tree",   NULL},
                        {(char*)NULL, NULL, NULL}};

command commands[] = {{"tree",  "t", comm_tree,  "Interact with the tree", args_tree},
                      {"print", "p", comm_print, "Print stuff", NULL},
                      {"quit",  "q", comm_quit,  "Exit debug view", NULL},
                      {"help",  "h", comm_help,  "Display possible commands", NULL},
                      {(char*)NULL, NULL, (comm_func_t*)NULL, (char*)NULL, NULL}};

struct ccn_node *curr_node;
void cocodbg_start(struct ccn_node *start_node)
{
    ccndbg_repl_commands = commands;
    curr_node = start_node;
    cocodbg_repl();
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

int comm_print(char *comm)
{
    printf("Print '%s'\n", comm);
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
