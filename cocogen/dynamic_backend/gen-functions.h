#pragma once

#include "ast/ast.h"
#include <stdio.h>

void gen_actions_header(Config *, FILE *);
void gen_actions_src(Config *, FILE *);
void gen_ast_header(Config *, FILE *);
void gen_ast_src(Config *, FILE *);
void gen_header_cmakelists(Config *, FILE *);
void gen_source_cmakelists(Config *, FILE *);
void gen_copy_header(Config *, FILE *);
void gen_copy_src(Config *, FILE *);
void gen_enum_header(Config *, FILE *);
void gen_enum_src(Config *, FILE *);
void gen_free_header(Config *, FILE *);
void gen_free_src(Config *, FILE *);
void gen_trav_user_header(Config *, FILE *, Traversal *);
void gen_trav_user_src(Config *, FILE *, Traversal *);
void gen_trav_header(Config *, FILE *);
void gen_trav_src(Config *, FILE *);
void gen_vtables_src(Config *, FILE *);