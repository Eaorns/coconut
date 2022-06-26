#define _GNU_SOURCE  // Required for REG_RIP
#include "ccngen/ast.h"
#ifdef INCLUDE_DEBUGGER
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <ucontext.h>
#include "palm/watchpoint.h"
#include "palm/watchpointalloc.h"
#include "ccn/phase_driver.h"
#endif
#include "palm/memory.h"
#ifdef INCLUDE_DEBUGGER
#define NODE_LIST_REALLOC_AMT 256
size_t node_id_ctr = 0;
node_st **node_tracker_list;
size_t node_tracker_list_size = 0;
#endif
node_st *NewNode() {
    node_st *node = MEMmalloc(sizeof(node_st));
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node) = MEMmalloc(sizeof(ccn_hist));
    #endif
    NODE_TYPE(node) = NT_NULL;
    NODE_CHILDREN(node) = NULL;
    NODE_FILENAME(node) = NULL;
    NODE_NUMCHILDREN(node) = 0;
    NODE_BLINE(node) = 0;
    NODE_ELINE(node) = 0;
    NODE_BCOL(node) = 0;
    NODE_ECOL(node) = 0;
    #ifdef INCLUDE_DEBUGGER
    NODE_ID(node) = node_id_ctr;
    NODE_PARENT(node) = NULL;
    NODE_ALLOCED_IN(node) = CCNgetCurrentActionId();
    if (node_tracker_list_size == node_id_ctr) {
        node_tracker_list_size += NODE_LIST_REALLOC_AMT;
        node_tracker_list = realloc(node_tracker_list, node_tracker_list_size * sizeof(node_st*));
    }

    node_tracker_list[node_id_ctr++] = node;
    #endif
    return node;
}

#ifdef INCLUDE_DEBUGGER
size_t get_node_id_counter() {
    return node_id_ctr;
}

node_st **get_node_tracker_list() {
    return node_tracker_list;
}

#endif
#ifdef INCLUDE_DEBUGGER
void wphandler(void *addr, void *old_val __attribute__((unused)), void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct hist_item *s = (struct hist_item *)malloc(sizeof(struct hist_item));
    s->val = (void*)(*(long*)addr);
    s->rip = rip;
    s->action = CCNgetCurrentActionCtr();
    s->next = *(void**)userdata;
    *(void**)userdata = s;
}

#endif
node_st *ASTid(char * orig, char * lwr, char * Upr) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_id = wpalloc(sizeof(struct NODE_DATA_ID));
    #else
    node->data.N_id = MEMmalloc(sizeof(struct NODE_DATA_ID));
    #endif
    NODE_TYPE(node) = NT_ID;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_id = MEMcalloc(sizeof(struct NODE_HIST_ID));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(ID_NEXT(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(ID_ORIG(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.orig));
    watchpoint_add(&(ID_LWR(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.lwr));
    watchpoint_add(&(ID_UPR(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.upr));
    watchpoint_add(&(ID_ROW(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.row));
    watchpoint_add(&(ID_COL_BEGIN(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.col_begin));
    watchpoint_add(&(ID_COL_END(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.col_end));
    #endif
    #endif
    ID_NEXT(node) = NULL;
    ID_ORIG(node) = orig;
    ID_LWR(node) = lwr;
    ID_UPR(node) = Upr;
    ID_ROW(node) = 0;
    ID_COL_BEGIN(node) = 0;
    ID_COL_END(node) = 0;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_id->id_children.id_children_at;
    return node;}

node_st *ASTienum(node_st *vals, node_st *name, node_st *iprefix, char * iinfo) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_ienum = wpalloc(sizeof(struct NODE_DATA_IENUM));
    #else
    node->data.N_ienum = MEMmalloc(sizeof(struct NODE_DATA_IENUM));
    #endif
    NODE_TYPE(node) = NT_IENUM;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_ienum = MEMcalloc(sizeof(struct NODE_HIST_IENUM));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(IENUM_VALS(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.vals));
    watchpoint_add(&(IENUM_NAME(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(IENUM_IPREFIX(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.iprefix));
    watchpoint_add(&(IENUM_NEXT(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(IENUM_IINFO(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.iinfo));
    #endif
    #endif
    IENUM_VALS(node) = vals;
    IENUM_NAME(node) = name;
    IENUM_IPREFIX(node) = iprefix;
    IENUM_NEXT(node) = NULL;
    IENUM_IINFO(node) = iinfo;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_ienum->ienum_children.ienum_children_at;
    return node;}

node_st *ASTattribute() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_attribute = wpalloc(sizeof(struct NODE_DATA_ATTRIBUTE));
    #else
    node->data.N_attribute = MEMmalloc(sizeof(struct NODE_DATA_ATTRIBUTE));
    #endif
    NODE_TYPE(node) = NT_ATTRIBUTE;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_attribute = MEMcalloc(sizeof(struct NODE_HIST_ATTRIBUTE));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(ATTRIBUTE_NAME(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(ATTRIBUTE_TYPE_REFERENCE(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.type_reference));
    watchpoint_add(&(ATTRIBUTE_LIFETIMES(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.lifetimes));
    watchpoint_add(&(ATTRIBUTE_NEXT(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(ATTRIBUTE_TYPE(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.type));
    watchpoint_add(&(ATTRIBUTE_IN_CONSTRUCTOR(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.in_constructor));
    #endif
    #endif
    ATTRIBUTE_NAME(node) = NULL;
    ATTRIBUTE_TYPE_REFERENCE(node) = NULL;
    ATTRIBUTE_LIFETIMES(node) = NULL;
    ATTRIBUTE_NEXT(node) = NULL;
    ATTRIBUTE_TYPE(node) = 0;
    ATTRIBUTE_IN_CONSTRUCTOR(node) = 0;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_attribute->attribute_children.attribute_children_at;
    return node;}

node_st *ASTitravdata(node_st *name) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_itravdata = wpalloc(sizeof(struct NODE_DATA_ITRAVDATA));
    #else
    node->data.N_itravdata = MEMmalloc(sizeof(struct NODE_DATA_ITRAVDATA));
    #endif
    NODE_TYPE(node) = NT_ITRAVDATA;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_itravdata = MEMcalloc(sizeof(struct NODE_HIST_ITRAVDATA));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(ITRAVDATA_NAME(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(ITRAVDATA_TYPE_REFERENCE(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.type_reference));
    watchpoint_add(&(ITRAVDATA_NEXT(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(ITRAVDATA_TYPE(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.type));
    watchpoint_add(&(ITRAVDATA_INCLUDE_FILE(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.include_file));
    #endif
    #endif
    ITRAVDATA_NAME(node) = name;
    ITRAVDATA_TYPE_REFERENCE(node) = NULL;
    ITRAVDATA_NEXT(node) = NULL;
    ITRAVDATA_TYPE(node) = 0;
    ITRAVDATA_INCLUDE_FILE(node) = NULL;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_itravdata->itravdata_children.itravdata_children_at;
    return node;}

node_st *ASTsetoperation(node_st *left, node_st *right, enum setoperation_type type) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_setoperation = wpalloc(sizeof(struct NODE_DATA_SETOPERATION));
    #else
    node->data.N_setoperation = MEMmalloc(sizeof(struct NODE_DATA_SETOPERATION));
    #endif
    NODE_TYPE(node) = NT_SETOPERATION;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_setoperation = MEMcalloc(sizeof(struct NODE_HIST_SETOPERATION));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(SETOPERATION_LEFT(node)), &wphandler, &(HIST_SETOPERATION(NODE_HIST(node))->hist.hist_items.left));
    watchpoint_add(&(SETOPERATION_RIGHT(node)), &wphandler, &(HIST_SETOPERATION(NODE_HIST(node))->hist.hist_items.right));
    watchpoint_add(&(SETOPERATION_TYPE(node)), &wphandler, &(HIST_SETOPERATION(NODE_HIST(node))->hist.hist_items.type));
    #endif
    #endif
    SETOPERATION_LEFT(node) = left;
    SETOPERATION_RIGHT(node) = right;
    SETOPERATION_TYPE(node) = type;
    NODE_NUMCHILDREN(node) = 2;
    NODE_CHILDREN(node) = node->data.N_setoperation->setoperation_children.setoperation_children_at;
    return node;}

node_st *ASTsetliteral(node_st *reference) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_setliteral = wpalloc(sizeof(struct NODE_DATA_SETLITERAL));
    #else
    node->data.N_setliteral = MEMmalloc(sizeof(struct NODE_DATA_SETLITERAL));
    #endif
    NODE_TYPE(node) = NT_SETLITERAL;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_setliteral = MEMcalloc(sizeof(struct NODE_HIST_SETLITERAL));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(SETLITERAL_REFERENCE(node)), &wphandler, &(HIST_SETLITERAL(NODE_HIST(node))->hist.hist_items.reference));
    watchpoint_add(&(SETLITERAL_LEFT(node)), &wphandler, &(HIST_SETLITERAL(NODE_HIST(node))->hist.hist_items.left));
    watchpoint_add(&(SETLITERAL_RIGHT(node)), &wphandler, &(HIST_SETLITERAL(NODE_HIST(node))->hist.hist_items.right));
    #endif
    #endif
    SETLITERAL_REFERENCE(node) = reference;
    SETLITERAL_LEFT(node) = NULL;
    SETLITERAL_RIGHT(node) = NULL;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_setliteral->setliteral_children.setliteral_children_at;
    return node;}

node_st *ASTsetreference() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_setreference = wpalloc(sizeof(struct NODE_DATA_SETREFERENCE));
    #else
    node->data.N_setreference = MEMmalloc(sizeof(struct NODE_DATA_SETREFERENCE));
    #endif
    NODE_TYPE(node) = NT_SETREFERENCE;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_setreference = MEMcalloc(sizeof(struct NODE_HIST_SETREFERENCE));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(SETREFERENCE_REFERENCE(node)), &wphandler, &(HIST_SETREFERENCE(NODE_HIST(node))->hist.hist_items.reference));
    #endif
    #endif
    SETREFERENCE_REFERENCE(node) = NULL;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_setreference->setreference_children.setreference_children_at;
    return node;}

node_st *ASTste() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_ste = wpalloc(sizeof(struct NODE_DATA_STE));
    #else
    node->data.N_ste = MEMmalloc(sizeof(struct NODE_DATA_STE));
    #endif
    NODE_TYPE(node) = NT_STE;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_ste = MEMcalloc(sizeof(struct NODE_HIST_STE));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(STE_NEXT(node)), &wphandler, &(HIST_STE(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(STE_KEY(node)), &wphandler, &(HIST_STE(NODE_HIST(node))->hist.hist_items.key));
    watchpoint_add(&(STE_VALUE(node)), &wphandler, &(HIST_STE(NODE_HIST(node))->hist.hist_items.value));
    #endif
    #endif
    STE_NEXT(node) = NULL;
    STE_KEY(node) = NULL;
    STE_VALUE(node) = NULL;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_ste->ste_children.ste_children_at;
    return node;}

node_st *ASTchild(node_st *name) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_child = wpalloc(sizeof(struct NODE_DATA_CHILD));
    #else
    node->data.N_child = MEMmalloc(sizeof(struct NODE_DATA_CHILD));
    #endif
    NODE_TYPE(node) = NT_CHILD;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_child = MEMcalloc(sizeof(struct NODE_HIST_CHILD));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(CHILD_NAME(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(CHILD_LIFETIMES(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.lifetimes));
    watchpoint_add(&(CHILD_NEXT(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(CHILD_TYPE_REFERENCE(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.type_reference));
    watchpoint_add(&(CHILD_TYPE(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.type));
    watchpoint_add(&(CHILD_IN_CONSTRUCTOR(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.in_constructor));
    watchpoint_add(&(CHILD_IS_MANDATORY(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.is_mandatory));
    #endif
    #endif
    CHILD_NAME(node) = name;
    CHILD_LIFETIMES(node) = NULL;
    CHILD_NEXT(node) = NULL;
    CHILD_TYPE_REFERENCE(node) = NULL;
    CHILD_TYPE(node) = 0;
    CHILD_IN_CONSTRUCTOR(node) = 0;
    CHILD_IS_MANDATORY(node) = 0;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_child->child_children.child_children_at;
    return node;}

node_st *ASTlifetime_range() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_lifetime_range = wpalloc(sizeof(struct NODE_DATA_LIFETIME_RANGE));
    #else
    node->data.N_lifetime_range = MEMmalloc(sizeof(struct NODE_DATA_LIFETIME_RANGE));
    #endif
    NODE_TYPE(node) = NT_LIFETIME_RANGE;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_lifetime_range = MEMcalloc(sizeof(struct NODE_HIST_LIFETIME_RANGE));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(LIFETIME_RANGE_TARGET(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.target));
    watchpoint_add(&(LIFETIME_RANGE_INCLUSIVE(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.inclusive));
    watchpoint_add(&(LIFETIME_RANGE_ACTION_ID(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.action_id));
    watchpoint_add(&(LIFETIME_RANGE_NEXT_ACTION_ID(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.next_action_id));
    #endif
    #endif
    LIFETIME_RANGE_TARGET(node) = NULL;
    LIFETIME_RANGE_INCLUSIVE(node) = false;
    LIFETIME_RANGE_ACTION_ID(node) = 0;
    LIFETIME_RANGE_NEXT_ACTION_ID(node) = 0;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_lifetime_range->lifetime_range_children.lifetime_range_children_at;
    return node;}

node_st *ASTilifetime() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_ilifetime = wpalloc(sizeof(struct NODE_DATA_ILIFETIME));
    #else
    node->data.N_ilifetime = MEMmalloc(sizeof(struct NODE_DATA_ILIFETIME));
    #endif
    NODE_TYPE(node) = NT_ILIFETIME;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_ilifetime = MEMcalloc(sizeof(struct NODE_HIST_ILIFETIME));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(ILIFETIME_BEGIN(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.begin));
    watchpoint_add(&(ILIFETIME_END(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.end));
    watchpoint_add(&(ILIFETIME_NEXT(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(ILIFETIME_TYPE(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.type));
    #endif
    #endif
    ILIFETIME_BEGIN(node) = NULL;
    ILIFETIME_END(node) = NULL;
    ILIFETIME_NEXT(node) = NULL;
    ILIFETIME_TYPE(node) = 0;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_ilifetime->ilifetime_children.ilifetime_children_at;
    return node;}

node_st *ASTinodeset() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_inodeset = wpalloc(sizeof(struct NODE_DATA_INODESET));
    #else
    node->data.N_inodeset = MEMmalloc(sizeof(struct NODE_DATA_INODESET));
    #endif
    NODE_TYPE(node) = NT_INODESET;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_inodeset = MEMcalloc(sizeof(struct NODE_HIST_INODESET));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(INODESET_NAME(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(INODESET_EXPR(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.expr));
    watchpoint_add(&(INODESET_UNPACKED(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.unpacked));
    watchpoint_add(&(INODESET_NEXT(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(INODESET_IINFO(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.iinfo));
    #endif
    #endif
    INODESET_NAME(node) = NULL;
    INODESET_EXPR(node) = NULL;
    INODESET_UNPACKED(node) = NULL;
    INODESET_NEXT(node) = NULL;
    INODESET_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_inodeset->inodeset_children.inodeset_children_at;
    return node;}

node_st *ASTinode(node_st *name, char * iifno) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_inode = wpalloc(sizeof(struct NODE_DATA_INODE));
    #else
    node->data.N_inode = MEMmalloc(sizeof(struct NODE_DATA_INODE));
    #endif
    NODE_TYPE(node) = NT_INODE;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_inode = MEMcalloc(sizeof(struct NODE_HIST_INODE));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(INODE_NAME(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(INODE_NEXT(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(INODE_ICHILDREN(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.ichildren));
    watchpoint_add(&(INODE_IATTRIBUTES(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.iattributes));
    watchpoint_add(&(INODE_LIFETIMES(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.lifetimes));
    watchpoint_add(&(INODE_IIFNO(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.iifno));
    watchpoint_add(&(INODE_IS_ROOT(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.is_root));
    watchpoint_add(&(INODE_INDEX(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.index));
    #endif
    #endif
    INODE_NAME(node) = name;
    INODE_NEXT(node) = NULL;
    INODE_ICHILDREN(node) = NULL;
    INODE_IATTRIBUTES(node) = NULL;
    INODE_LIFETIMES(node) = NULL;
    INODE_IIFNO(node) = iifno;
    INODE_IS_ROOT(node) = 0;
    INODE_INDEX(node) = 0;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_inode->inode_children.inode_children_at;
    return node;}

node_st *ASTipass(node_st *name, char * iifno) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_ipass = wpalloc(sizeof(struct NODE_DATA_IPASS));
    #else
    node->data.N_ipass = MEMmalloc(sizeof(struct NODE_DATA_IPASS));
    #endif
    NODE_TYPE(node) = NT_IPASS;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_ipass = MEMcalloc(sizeof(struct NODE_HIST_IPASS));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(IPASS_NAME(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(IPASS_IPREFIX(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.iprefix));
    watchpoint_add(&(IPASS_TARGET_FUNC(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.target_func));
    watchpoint_add(&(IPASS_NEXT(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(IPASS_IIFNO(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.iifno));
    #endif
    #endif
    IPASS_NAME(node) = name;
    IPASS_IPREFIX(node) = NULL;
    IPASS_TARGET_FUNC(node) = NULL;
    IPASS_NEXT(node) = NULL;
    IPASS_IIFNO(node) = iifno;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_ipass->ipass_children.ipass_children_at;
    return node;}

node_st *ASTitraversal(node_st *name) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_itraversal = wpalloc(sizeof(struct NODE_DATA_ITRAVERSAL));
    #else
    node->data.N_itraversal = MEMmalloc(sizeof(struct NODE_DATA_ITRAVERSAL));
    #endif
    NODE_TYPE(node) = NT_ITRAVERSAL;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_itraversal = MEMcalloc(sizeof(struct NODE_HIST_ITRAVERSAL));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(ITRAVERSAL_NAME(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(ITRAVERSAL_IPREFIX(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.iprefix));
    watchpoint_add(&(ITRAVERSAL_INODES(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.inodes));
    watchpoint_add(&(ITRAVERSAL_DATA(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.data));
    watchpoint_add(&(ITRAVERSAL_NEXT(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(ITRAVERSAL_INDEX(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.index));
    watchpoint_add(&(ITRAVERSAL_IINFO(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.iinfo));
    #endif
    #endif
    ITRAVERSAL_NAME(node) = name;
    ITRAVERSAL_IPREFIX(node) = NULL;
    ITRAVERSAL_INODES(node) = NULL;
    ITRAVERSAL_DATA(node) = NULL;
    ITRAVERSAL_NEXT(node) = NULL;
    ITRAVERSAL_INDEX(node) = 0;
    ITRAVERSAL_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_itraversal->itraversal_children.itraversal_children_at;
    return node;}

node_st *ASTiphase(node_st *name, int is_start) {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_iphase = wpalloc(sizeof(struct NODE_DATA_IPHASE));
    #else
    node->data.N_iphase = MEMmalloc(sizeof(struct NODE_DATA_IPHASE));
    #endif
    NODE_TYPE(node) = NT_IPHASE;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_iphase = MEMcalloc(sizeof(struct NODE_HIST_IPHASE));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(IPHASE_NAME(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.name));
    watchpoint_add(&(IPHASE_IPREFIX(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.iprefix));
    watchpoint_add(&(IPHASE_GATE_FUNC(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.gate_func));
    watchpoint_add(&(IPHASE_IACTIONS(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.iactions));
    watchpoint_add(&(IPHASE_NEXT(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(IPHASE_IS_START(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.is_start));
    watchpoint_add(&(IPHASE_IS_CYCLE(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.is_cycle));
    watchpoint_add(&(IPHASE_IINFO(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.iinfo));
    #endif
    #endif
    IPHASE_NAME(node) = name;
    IPHASE_IPREFIX(node) = NULL;
    IPHASE_GATE_FUNC(node) = NULL;
    IPHASE_IACTIONS(node) = NULL;
    IPHASE_NEXT(node) = NULL;
    IPHASE_IS_START(node) = is_start;
    IPHASE_IS_CYCLE(node) = 0;
    IPHASE_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_iphase->iphase_children.iphase_children_at;
    return node;}

node_st *ASTiactions() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_iactions = wpalloc(sizeof(struct NODE_DATA_IACTIONS));
    #else
    node->data.N_iactions = MEMmalloc(sizeof(struct NODE_DATA_IACTIONS));
    #endif
    NODE_TYPE(node) = NT_IACTIONS;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_iactions = MEMcalloc(sizeof(struct NODE_HIST_IACTIONS));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(IACTIONS_REFERENCE(node)), &wphandler, &(HIST_IACTIONS(NODE_HIST(node))->hist.hist_items.reference));
    watchpoint_add(&(IACTIONS_NEXT(node)), &wphandler, &(HIST_IACTIONS(NODE_HIST(node))->hist.hist_items.next));
    watchpoint_add(&(IACTIONS_ACTION_ID(node)), &wphandler, &(HIST_IACTIONS(NODE_HIST(node))->hist.hist_items.action_id));
    #endif
    #endif
    IACTIONS_REFERENCE(node) = NULL;
    IACTIONS_NEXT(node) = NULL;
    IACTIONS_ACTION_ID(node) = 0;
    NODE_NUMCHILDREN(node) = 2;
    NODE_CHILDREN(node) = node->data.N_iactions->iactions_children.iactions_children_at;
    return node;}

node_st *ASTast() {
    node_st *node = NewNode();
    #ifdef INCLUDE_DEBUGGER
    node->data.N_ast = wpalloc(sizeof(struct NODE_DATA_AST));
    #else
    node->data.N_ast = MEMmalloc(sizeof(struct NODE_DATA_AST));
    #endif
    NODE_TYPE(node) = NT_AST;
    #ifdef INCLUDE_DEBUGGER
    NODE_HIST(node)->data.NH_ast = MEMcalloc(sizeof(struct NODE_HIST_AST));
    #ifdef INCLUDE_WATCHPOINTS
    watchpoint_add(&(AST_IPHASES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.iphases));
    watchpoint_add(&(AST_ITRAVERSALS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.itraversals));
    watchpoint_add(&(AST_IPASSES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.ipasses));
    watchpoint_add(&(AST_INODES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.inodes));
    watchpoint_add(&(AST_INODESETS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.inodesets));
    watchpoint_add(&(AST_ENUMS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.enums));
    watchpoint_add(&(AST_STABLE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.stable));
    watchpoint_add(&(AST_NUM_TRAVERSALS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.num_traversals));
    watchpoint_add(&(AST_NUM_NODES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.num_nodes));
    watchpoint_add(&(AST_ROOT_NODE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.root_node));
    watchpoint_add(&(AST_START_PHASE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.start_phase));
    watchpoint_add(&(AST_USES_UNSAFE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.uses_unsafe));
    #endif
    #endif
    AST_IPHASES(node) = NULL;
    AST_ITRAVERSALS(node) = NULL;
    AST_IPASSES(node) = NULL;
    AST_INODES(node) = NULL;
    AST_INODESETS(node) = NULL;
    AST_ENUMS(node) = NULL;
    AST_STABLE(node) = NULL;
    AST_NUM_TRAVERSALS(node) = 0;
    AST_NUM_NODES(node) = 0;
    AST_ROOT_NODE(node) = NULL;
    AST_START_PHASE(node) = NULL;
    AST_USES_UNSAFE(node) = false;
    NODE_NUMCHILDREN(node) = 7;
    NODE_CHILDREN(node) = node->data.N_ast->ast_children.ast_children_at;
    return node;}

