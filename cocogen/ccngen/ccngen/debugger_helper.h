#pragma once
#include "ccngen/ast.h"
#ifdef INCLUDE_DEBUGGER
int DBGHelper_ntoi(enum ccn_nodetype type, char *name);
char *DBGHelper_iton(enum ccn_nodetype type, int idx);
enum H_DATTYPES DBGHelper_gettype(enum ccn_nodetype type, int idx);
void *DBGHelper_getptr(node_st *node, int idx);
void DBGHelper_setval(node_st *node, int idx, void *val);
int DBGHelper_ischild(enum ccn_nodetype type, int idx);
char *DBGHelper_nodename(enum ccn_nodetype type);
hist_item **DBGHelper_nodehist(enum ccn_nodetype type, ccn_hist *hist, int idx);
int DBGHelper_node_numvals(enum ccn_nodetype type);
#endif
