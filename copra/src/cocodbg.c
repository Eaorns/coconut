#include <stdio.h>
#include <string.h>

#include "ccn/ccn_dbg.h"

/**
 *  Declare command functions
 */

int comm_tree(char*);
int comm_print(char*);
int comm_quit(char*);

argument args_tree_get[] = {{"first", NULL},
                            {"last", NULL},
                            {(char*)NULL, NULL}};

argument args_tree[] = {{"get", args_tree_get},
                        {"set", NULL},
                        {(char*)NULL, NULL}};

command commands[] = {{"tree",  comm_tree,  "View tree", args_tree},
                      {"print", comm_print, "View tree", NULL},
                      {"quit",  comm_quit,  "View tree", NULL},
                      {(char*)NULL, (comm_func_t*)NULL, (char*)NULL, NULL}};
// ccndbg_repl_commands = commands;


/**
 *  Define command functions
 */

int comm_tree(char *comm)
{
    char *token = strtok(comm, " ");
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
