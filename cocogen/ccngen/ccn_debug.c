#include "ccngen/ast.h"
#include "ccn/dynamic_core.h"
#include "palm/memory.h"
#include "ccn/ccn_dbg.h"
#include <stdio.h>

struct ccn_node *parent = NULL;

struct ccn_node *DBGid(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGienum(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGattribute(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGitravdata(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGsetoperation(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGsetliteral(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGsetreference(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGste(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGchild(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGlifetime_range(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGilifetime(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGinodeset(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGinode(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGipass(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGitraversal(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGiphase(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGiactions(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

struct ccn_node *DBGast(struct ccn_node *arg_node) {
    #ifdef INCLUDE_DEBUGGER
    arg_node->parent = parent;
    struct ccn_node *curr_parent = parent;
    parent = arg_node;
    TRAVchildren(arg_node);
    parent = curr_parent;
    #endif
    return arg_node;
}

