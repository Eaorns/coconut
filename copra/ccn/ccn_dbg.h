#pragma once

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

void cocodbg_init();

int cocodbg_repl();
command *find_command(char *comm);
int parse_arg(argument args[], char *arg);


extern int ccndbg_repl_done;
extern command *ccndbg_repl_commands;

