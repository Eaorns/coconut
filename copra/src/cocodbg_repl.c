#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <editline/readline.h>

#include "ccn/ccn_dbg.h"

#ifndef COCODBG_PROMPT
#define COCODBG_PROMPT "cocodbg> "
#endif

int ccndbg_repl_done = 0;
command null_commands[] = {{(char*)NULL, (comm_func_t*)NULL, (char*)NULL, NULL}};


/**
 *  Declare command functions
 */

// int comm_tree(char*);
// int comm_print(char*);
// int comm_quit(char*);

// argument args_tree_get[] = {{"first", NULL},
//                             {"last", NULL},
//                             {(char*)NULL, NULL}};
//
// argument args_tree[] = {{"get", args_tree_get},
//                         {"set", NULL},
//                         {(char*)NULL, NULL}};
//
// command ccndbg_repl_commands[] = {{"tree",  comm_tree,  "View tree", args_tree},
//                       {"print", comm_print, "View tree", NULL},
//                       {"quit",  comm_quit,  "View tree", NULL},
//                       {(char*)NULL, (comm_func_t*)NULL, (char*)NULL, NULL}};


/**
 *  Define command functions
 */

// int parse_arg(argument[], char*);

// int comm_tree(char *comm)
// {
//     char *token = strtok(comm, " ");
//     switch (parse_arg(args_tree, token)) {
//     case 0:
//         printf("Tree get '%s'\n", strtok(NULL, ""));
//         break;
//     case 1:
//         printf("Tree set '%s'\n", strtok(NULL, ""));
//         break;
//     default:
//         printf("Unknown argument '%s' for command 'tree'\n", token);
//         return -1;
//     }
//
//     return 0;
// }
//
// int comm_print(char *comm)
// {
//     printf("Print '%s'\n", comm);
// }
//
// int comm_quit(char *comm)
// {
//     ccndbg_repl_done = 1;
//     return 0;
// }

command *ccndbg_repl_commands;


/**
 *  Helper functions
 */

char *strip(char *str)
{
    while (isspace(str[0]))
        str++;

    for (int i = strlen(str); isspace(str[i]); i--)
        str[i] = '\0';

    return str;
}

char *strdup(const char *str)
{
    char *cpy = malloc(strlen(str) + 1);
    strcpy(cpy, str);
    return cpy;
}

command *find_command(char *comm)
{
    if (comm == NULL)
        return (command*)NULL;

    for (int i = 0; ccndbg_repl_commands[i].command; i++) {
        if (strcmp(comm, ccndbg_repl_commands[i].command) == 0)
            return (&ccndbg_repl_commands[i]);
    }

    return (command*)NULL;
}

int parse_arg(argument args[], char *arg)
{
    for (int i = 0; args[i].arg; i++) {
        if (strcmp(arg, args[i].arg) == 0)
            return i;
    }

    return -1;
}


/**
 *  Actual repl code
 */

char *completer_matcher(const char *text, int state)
{
    static int index, len;
    static argument *args;

    if (state == 0) {
        index = 0;
        len = strlen(text);
        args = NULL;

        char *token = strtok(rl_line_buffer, " ");
        command *comm = find_command(token);

        if (comm) {
            if (comm->args == NULL)
                return (char*)NULL;

            token = strtok(NULL, " ");
            args = comm->args;

            while (token) {
                for (int i = 0; args[i].arg; i++) {
                    if (strcmp(token, args[i].arg) == 0) {
                        if (args[i].subargs == NULL)
                            return (char*)NULL;
                        args = args[i].subargs;
                        break;
                    }
                }
                token = strtok(NULL, " ");
            }
        }
    }

    if (args == NULL) {
        while (ccndbg_repl_commands[index].command) {
            if (strncmp(text, ccndbg_repl_commands[index++].command, len) == 0)
                return strdup(ccndbg_repl_commands[index - 1].command);
        }
    } else {
        while (args[index].arg) {
            if (strncmp(text, args[index++].arg, len) == 0)
                return strdup(args[index - 1].arg);
        }
    }

    return (char*)NULL;
}

int cocodbg_repl()
{
    rl_completion_entry_function = completer_matcher;

    if (ccndbg_repl_commands == NULL)
        ccndbg_repl_commands = null_commands;

    char *line, *stripped, *token;

    while (!ccndbg_repl_done) {
        line = readline(COCODBG_PROMPT);
        stripped = strip(line);

        if (stripped) {
            char* expansion;
            int hist_retcode = history_expand(stripped, &expansion);

            if (hist_retcode < 0 || hist_retcode == 2) {
                fprintf(stderr, "%s\n", expansion);
            } else {
                add_history(expansion);

                token = strtok(stripped, " ");
                command *comm = find_command(token);

                if (comm == NULL)
                    printf("Unknown command: %s\n", token);
                else
                    comm->func(strtok(NULL, ""));
            }
        }

        free(line);
    }

    return ccndbg_repl_done;
}
