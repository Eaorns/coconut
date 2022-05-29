#pragma once

#include "ccn/ccn_types.h"

typedef int comm_func_t(char*);

typedef struct argument {
    char *arg;
    char *desc;
    struct argument *subargs;
} argument;

typedef struct command {
    char *command;
    char *alt;
    comm_func_t *func;
    char *desc;
    argument *args;
} command;

int cocodbg_start(struct ccn_node *start_node);

int cocodbg_repl();
command *find_command(char *comm);
int parse_arg(argument args[], char *arg);

extern int ccndbg_repl_done;
extern command *ccndbg_repl_commands;

extern char *executable_name;
