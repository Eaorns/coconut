#define _GNU_SOURCE  // Required for REG_RIP
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <ucontext.h>
#include "ccngen/ast.h"
#include "palm/memory.h"
#include "palm/watchpoint.h"
#include "palm/watchpointalloc.h"
#include "ccn/phase_driver.h"
#define NODE_LIST_REALLOC_AMT 256
size_t node_id_ctr = 0;
node_st **node_tracker_list;
size_t node_tracker_list_size = 0;
node_st *NewNode() {
    node_st *node = MEMmalloc(sizeof(node_st));
    NODE_HIST(node) = MEMmalloc(sizeof(ccn_hist));
    NODE_TYPE(node) = NT_NULL;
    NODE_CHILDREN(node) = NULL;
    NODE_FILENAME(node) = NULL;
    NODE_NUMCHILDREN(node) = 0;
    NODE_BLINE(node) = 0;
    NODE_ELINE(node) = 0;
    NODE_BCOL(node) = 0;
    NODE_ECOL(node) = 0;
    NODE_ID(node) = node_id_ctr;
    NODE_PARENT(node) = NULL;
    NODE_ALLOCED_IN(node) = CCNgetCurrentActionId();
    if (node_tracker_list_size == node_id_ctr) {
        node_tracker_list_size += NODE_LIST_REALLOC_AMT;
        node_tracker_list = realloc(node_tracker_list, node_tracker_list_size * sizeof(node_st*));
    }

    node_tracker_list[node_id_ctr++] = node;
    return node;
}

size_t get_node_id_counter() {
    return node_id_ctr;
}

node_st **get_node_tracker_list() {
    return node_tracker_list;
}

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

node_st *ASTid(char * orig, char * lwr, char * Upr) {
    node_st *node = NewNode();
    node->data.N_id = wpalloc(sizeof(struct NODE_DATA_ID));
    NODE_TYPE(node) = NT_ID;
    NODE_HIST(node)->data.NH_id = MEMcalloc(sizeof(struct NODE_HIST_ID));
    watchpoint_add(&(ID_NEXT(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.next));
    ID_NEXT(node) = NULL;
    watchpoint_add(&(ID_ORIG(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.orig));
    ID_ORIG(node) = orig;
    watchpoint_add(&(ID_LWR(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.lwr));
    ID_LWR(node) = lwr;
    watchpoint_add(&(ID_UPR(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.upr));
    ID_UPR(node) = Upr;
    watchpoint_add(&(ID_ROW(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.row));
    ID_ROW(node) = 0;
    watchpoint_add(&(ID_COL_BEGIN(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.col_begin));
    ID_COL_BEGIN(node) = 0;
    watchpoint_add(&(ID_COL_END(node)), &wphandler, &(HIST_ID(NODE_HIST(node))->hist.hist_items.col_end));
    ID_COL_END(node) = 0;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_id->id_children.id_children_at;
    return node;}

node_st *ASTienum(node_st *vals, node_st *name, node_st *iprefix, char * iinfo) {
    node_st *node = NewNode();
    node->data.N_ienum = wpalloc(sizeof(struct NODE_DATA_IENUM));
    NODE_TYPE(node) = NT_IENUM;
    NODE_HIST(node)->data.NH_ienum = MEMcalloc(sizeof(struct NODE_HIST_IENUM));
    watchpoint_add(&(IENUM_VALS(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.vals));
    IENUM_VALS(node) = vals;
    watchpoint_add(&(IENUM_NAME(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.name));
    IENUM_NAME(node) = name;
    watchpoint_add(&(IENUM_IPREFIX(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.iprefix));
    IENUM_IPREFIX(node) = iprefix;
    watchpoint_add(&(IENUM_NEXT(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.next));
    IENUM_NEXT(node) = NULL;
    watchpoint_add(&(IENUM_IINFO(node)), &wphandler, &(HIST_IENUM(NODE_HIST(node))->hist.hist_items.iinfo));
    IENUM_IINFO(node) = iinfo;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_ienum->ienum_children.ienum_children_at;
    return node;}

node_st *ASTattribute() {
    node_st *node = NewNode();
    node->data.N_attribute = wpalloc(sizeof(struct NODE_DATA_ATTRIBUTE));
    NODE_TYPE(node) = NT_ATTRIBUTE;
    NODE_HIST(node)->data.NH_attribute = MEMcalloc(sizeof(struct NODE_HIST_ATTRIBUTE));
    watchpoint_add(&(ATTRIBUTE_NAME(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.name));
    ATTRIBUTE_NAME(node) = NULL;
    watchpoint_add(&(ATTRIBUTE_TYPE_REFERENCE(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.type_reference));
    ATTRIBUTE_TYPE_REFERENCE(node) = NULL;
    watchpoint_add(&(ATTRIBUTE_LIFETIMES(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.lifetimes));
    ATTRIBUTE_LIFETIMES(node) = NULL;
    watchpoint_add(&(ATTRIBUTE_NEXT(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.next));
    ATTRIBUTE_NEXT(node) = NULL;
    watchpoint_add(&(ATTRIBUTE_TYPE(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.type));
    ATTRIBUTE_TYPE(node) = 0;
    watchpoint_add(&(ATTRIBUTE_IN_CONSTRUCTOR(node)), &wphandler, &(HIST_ATTRIBUTE(NODE_HIST(node))->hist.hist_items.in_constructor));
    ATTRIBUTE_IN_CONSTRUCTOR(node) = 0;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_attribute->attribute_children.attribute_children_at;
    return node;}

node_st *ASTitravdata(node_st *name) {
    node_st *node = NewNode();
    node->data.N_itravdata = wpalloc(sizeof(struct NODE_DATA_ITRAVDATA));
    NODE_TYPE(node) = NT_ITRAVDATA;
    NODE_HIST(node)->data.NH_itravdata = MEMcalloc(sizeof(struct NODE_HIST_ITRAVDATA));
    watchpoint_add(&(ITRAVDATA_NAME(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.name));
    ITRAVDATA_NAME(node) = name;
    watchpoint_add(&(ITRAVDATA_TYPE_REFERENCE(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.type_reference));
    ITRAVDATA_TYPE_REFERENCE(node) = NULL;
    watchpoint_add(&(ITRAVDATA_NEXT(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.next));
    ITRAVDATA_NEXT(node) = NULL;
    watchpoint_add(&(ITRAVDATA_TYPE(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.type));
    ITRAVDATA_TYPE(node) = 0;
    watchpoint_add(&(ITRAVDATA_INCLUDE_FILE(node)), &wphandler, &(HIST_ITRAVDATA(NODE_HIST(node))->hist.hist_items.include_file));
    ITRAVDATA_INCLUDE_FILE(node) = NULL;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_itravdata->itravdata_children.itravdata_children_at;
    return node;}

node_st *ASTsetoperation(node_st *left, node_st *right, enum setoperation_type type) {
    node_st *node = NewNode();
    node->data.N_setoperation = wpalloc(sizeof(struct NODE_DATA_SETOPERATION));
    NODE_TYPE(node) = NT_SETOPERATION;
    NODE_HIST(node)->data.NH_setoperation = MEMcalloc(sizeof(struct NODE_HIST_SETOPERATION));
    watchpoint_add(&(SETOPERATION_LEFT(node)), &wphandler, &(HIST_SETOPERATION(NODE_HIST(node))->hist.hist_items.left));
    SETOPERATION_LEFT(node) = left;
    watchpoint_add(&(SETOPERATION_RIGHT(node)), &wphandler, &(HIST_SETOPERATION(NODE_HIST(node))->hist.hist_items.right));
    SETOPERATION_RIGHT(node) = right;
    watchpoint_add(&(SETOPERATION_TYPE(node)), &wphandler, &(HIST_SETOPERATION(NODE_HIST(node))->hist.hist_items.type));
    SETOPERATION_TYPE(node) = type;
    NODE_NUMCHILDREN(node) = 2;
    NODE_CHILDREN(node) = node->data.N_setoperation->setoperation_children.setoperation_children_at;
    return node;}

node_st *ASTsetliteral(node_st *reference) {
    node_st *node = NewNode();
    node->data.N_setliteral = wpalloc(sizeof(struct NODE_DATA_SETLITERAL));
    NODE_TYPE(node) = NT_SETLITERAL;
    NODE_HIST(node)->data.NH_setliteral = MEMcalloc(sizeof(struct NODE_HIST_SETLITERAL));
    watchpoint_add(&(SETLITERAL_REFERENCE(node)), &wphandler, &(HIST_SETLITERAL(NODE_HIST(node))->hist.hist_items.reference));
    SETLITERAL_REFERENCE(node) = reference;
    watchpoint_add(&(SETLITERAL_LEFT(node)), &wphandler, &(HIST_SETLITERAL(NODE_HIST(node))->hist.hist_items.left));
    SETLITERAL_LEFT(node) = NULL;
    watchpoint_add(&(SETLITERAL_RIGHT(node)), &wphandler, &(HIST_SETLITERAL(NODE_HIST(node))->hist.hist_items.right));
    SETLITERAL_RIGHT(node) = NULL;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_setliteral->setliteral_children.setliteral_children_at;
    return node;}

node_st *ASTsetreference() {
    node_st *node = NewNode();
    node->data.N_setreference = wpalloc(sizeof(struct NODE_DATA_SETREFERENCE));
    NODE_TYPE(node) = NT_SETREFERENCE;
    NODE_HIST(node)->data.NH_setreference = MEMcalloc(sizeof(struct NODE_HIST_SETREFERENCE));
    watchpoint_add(&(SETREFERENCE_REFERENCE(node)), &wphandler, &(HIST_SETREFERENCE(NODE_HIST(node))->hist.hist_items.reference));
    SETREFERENCE_REFERENCE(node) = NULL;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_setreference->setreference_children.setreference_children_at;
    return node;}

node_st *ASTste() {
    node_st *node = NewNode();
    node->data.N_ste = wpalloc(sizeof(struct NODE_DATA_STE));
    NODE_TYPE(node) = NT_STE;
    NODE_HIST(node)->data.NH_ste = MEMcalloc(sizeof(struct NODE_HIST_STE));
    watchpoint_add(&(STE_NEXT(node)), &wphandler, &(HIST_STE(NODE_HIST(node))->hist.hist_items.next));
    STE_NEXT(node) = NULL;
    watchpoint_add(&(STE_KEY(node)), &wphandler, &(HIST_STE(NODE_HIST(node))->hist.hist_items.key));
    STE_KEY(node) = NULL;
    watchpoint_add(&(STE_VALUE(node)), &wphandler, &(HIST_STE(NODE_HIST(node))->hist.hist_items.value));
    STE_VALUE(node) = NULL;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_ste->ste_children.ste_children_at;
    return node;}

node_st *ASTchild(node_st *name) {
    node_st *node = NewNode();
    node->data.N_child = wpalloc(sizeof(struct NODE_DATA_CHILD));
    NODE_TYPE(node) = NT_CHILD;
    NODE_HIST(node)->data.NH_child = MEMcalloc(sizeof(struct NODE_HIST_CHILD));
    watchpoint_add(&(CHILD_NAME(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.name));
    CHILD_NAME(node) = name;
    watchpoint_add(&(CHILD_LIFETIMES(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.lifetimes));
    CHILD_LIFETIMES(node) = NULL;
    watchpoint_add(&(CHILD_NEXT(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.next));
    CHILD_NEXT(node) = NULL;
    watchpoint_add(&(CHILD_TYPE_REFERENCE(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.type_reference));
    CHILD_TYPE_REFERENCE(node) = NULL;
    watchpoint_add(&(CHILD_TYPE(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.type));
    CHILD_TYPE(node) = 0;
    watchpoint_add(&(CHILD_IN_CONSTRUCTOR(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.in_constructor));
    CHILD_IN_CONSTRUCTOR(node) = 0;
    watchpoint_add(&(CHILD_IS_MANDATORY(node)), &wphandler, &(HIST_CHILD(NODE_HIST(node))->hist.hist_items.is_mandatory));
    CHILD_IS_MANDATORY(node) = 0;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_child->child_children.child_children_at;
    return node;}

node_st *ASTlifetime_range() {
    node_st *node = NewNode();
    node->data.N_lifetime_range = wpalloc(sizeof(struct NODE_DATA_LIFETIME_RANGE));
    NODE_TYPE(node) = NT_LIFETIME_RANGE;
    NODE_HIST(node)->data.NH_lifetime_range = MEMcalloc(sizeof(struct NODE_HIST_LIFETIME_RANGE));
    watchpoint_add(&(LIFETIME_RANGE_TARGET(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.target));
    LIFETIME_RANGE_TARGET(node) = NULL;
    watchpoint_add(&(LIFETIME_RANGE_INCLUSIVE(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.inclusive));
    LIFETIME_RANGE_INCLUSIVE(node) = false;
    watchpoint_add(&(LIFETIME_RANGE_ACTION_ID(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.action_id));
    LIFETIME_RANGE_ACTION_ID(node) = 0;
    watchpoint_add(&(LIFETIME_RANGE_NEXT_ACTION_ID(node)), &wphandler, &(HIST_LIFETIME_RANGE(NODE_HIST(node))->hist.hist_items.next_action_id));
    LIFETIME_RANGE_NEXT_ACTION_ID(node) = 0;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_lifetime_range->lifetime_range_children.lifetime_range_children_at;
    return node;}

node_st *ASTilifetime() {
    node_st *node = NewNode();
    node->data.N_ilifetime = wpalloc(sizeof(struct NODE_DATA_ILIFETIME));
    NODE_TYPE(node) = NT_ILIFETIME;
    NODE_HIST(node)->data.NH_ilifetime = MEMcalloc(sizeof(struct NODE_HIST_ILIFETIME));
    watchpoint_add(&(ILIFETIME_BEGIN(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.begin));
    ILIFETIME_BEGIN(node) = NULL;
    watchpoint_add(&(ILIFETIME_END(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.end));
    ILIFETIME_END(node) = NULL;
    watchpoint_add(&(ILIFETIME_NEXT(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.next));
    ILIFETIME_NEXT(node) = NULL;
    watchpoint_add(&(ILIFETIME_TYPE(node)), &wphandler, &(HIST_ILIFETIME(NODE_HIST(node))->hist.hist_items.type));
    ILIFETIME_TYPE(node) = 0;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_ilifetime->ilifetime_children.ilifetime_children_at;
    return node;}

node_st *ASTinodeset() {
    node_st *node = NewNode();
    node->data.N_inodeset = wpalloc(sizeof(struct NODE_DATA_INODESET));
    NODE_TYPE(node) = NT_INODESET;
    NODE_HIST(node)->data.NH_inodeset = MEMcalloc(sizeof(struct NODE_HIST_INODESET));
    watchpoint_add(&(INODESET_NAME(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.name));
    INODESET_NAME(node) = NULL;
    watchpoint_add(&(INODESET_EXPR(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.expr));
    INODESET_EXPR(node) = NULL;
    watchpoint_add(&(INODESET_UNPACKED(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.unpacked));
    INODESET_UNPACKED(node) = NULL;
    watchpoint_add(&(INODESET_NEXT(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.next));
    INODESET_NEXT(node) = NULL;
    watchpoint_add(&(INODESET_IINFO(node)), &wphandler, &(HIST_INODESET(NODE_HIST(node))->hist.hist_items.iinfo));
    INODESET_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_inodeset->inodeset_children.inodeset_children_at;
    return node;}

node_st *ASTinode(node_st *name, char * iifno) {
    node_st *node = NewNode();
    node->data.N_inode = wpalloc(sizeof(struct NODE_DATA_INODE));
    NODE_TYPE(node) = NT_INODE;
    NODE_HIST(node)->data.NH_inode = MEMcalloc(sizeof(struct NODE_HIST_INODE));
    watchpoint_add(&(INODE_NAME(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.name));
    INODE_NAME(node) = name;
    watchpoint_add(&(INODE_NEXT(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.next));
    INODE_NEXT(node) = NULL;
    watchpoint_add(&(INODE_ICHILDREN(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.ichildren));
    INODE_ICHILDREN(node) = NULL;
    watchpoint_add(&(INODE_IATTRIBUTES(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.iattributes));
    INODE_IATTRIBUTES(node) = NULL;
    watchpoint_add(&(INODE_LIFETIMES(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.lifetimes));
    INODE_LIFETIMES(node) = NULL;
    watchpoint_add(&(INODE_IIFNO(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.iifno));
    INODE_IIFNO(node) = iifno;
    watchpoint_add(&(INODE_IS_ROOT(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.is_root));
    INODE_IS_ROOT(node) = 0;
    watchpoint_add(&(INODE_INDEX(node)), &wphandler, &(HIST_INODE(NODE_HIST(node))->hist.hist_items.index));
    INODE_INDEX(node) = 0;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_inode->inode_children.inode_children_at;
    return node;}

node_st *ASTipass(node_st *name, char * iifno) {
    node_st *node = NewNode();
    node->data.N_ipass = wpalloc(sizeof(struct NODE_DATA_IPASS));
    NODE_TYPE(node) = NT_IPASS;
    NODE_HIST(node)->data.NH_ipass = MEMcalloc(sizeof(struct NODE_HIST_IPASS));
    watchpoint_add(&(IPASS_NAME(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.name));
    IPASS_NAME(node) = name;
    watchpoint_add(&(IPASS_IPREFIX(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.iprefix));
    IPASS_IPREFIX(node) = NULL;
    watchpoint_add(&(IPASS_TARGET_FUNC(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.target_func));
    IPASS_TARGET_FUNC(node) = NULL;
    watchpoint_add(&(IPASS_NEXT(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.next));
    IPASS_NEXT(node) = NULL;
    watchpoint_add(&(IPASS_IIFNO(node)), &wphandler, &(HIST_IPASS(NODE_HIST(node))->hist.hist_items.iifno));
    IPASS_IIFNO(node) = iifno;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_ipass->ipass_children.ipass_children_at;
    return node;}

node_st *ASTitraversal(node_st *name) {
    node_st *node = NewNode();
    node->data.N_itraversal = wpalloc(sizeof(struct NODE_DATA_ITRAVERSAL));
    NODE_TYPE(node) = NT_ITRAVERSAL;
    NODE_HIST(node)->data.NH_itraversal = MEMcalloc(sizeof(struct NODE_HIST_ITRAVERSAL));
    watchpoint_add(&(ITRAVERSAL_NAME(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.name));
    ITRAVERSAL_NAME(node) = name;
    watchpoint_add(&(ITRAVERSAL_IPREFIX(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.iprefix));
    ITRAVERSAL_IPREFIX(node) = NULL;
    watchpoint_add(&(ITRAVERSAL_INODES(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.inodes));
    ITRAVERSAL_INODES(node) = NULL;
    watchpoint_add(&(ITRAVERSAL_DATA(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.data));
    ITRAVERSAL_DATA(node) = NULL;
    watchpoint_add(&(ITRAVERSAL_NEXT(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.next));
    ITRAVERSAL_NEXT(node) = NULL;
    watchpoint_add(&(ITRAVERSAL_INDEX(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.index));
    ITRAVERSAL_INDEX(node) = 0;
    watchpoint_add(&(ITRAVERSAL_IINFO(node)), &wphandler, &(HIST_ITRAVERSAL(NODE_HIST(node))->hist.hist_items.iinfo));
    ITRAVERSAL_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_itraversal->itraversal_children.itraversal_children_at;
    return node;}

node_st *ASTiphase(node_st *name, int is_start) {
    node_st *node = NewNode();
    node->data.N_iphase = wpalloc(sizeof(struct NODE_DATA_IPHASE));
    NODE_TYPE(node) = NT_IPHASE;
    NODE_HIST(node)->data.NH_iphase = MEMcalloc(sizeof(struct NODE_HIST_IPHASE));
    watchpoint_add(&(IPHASE_NAME(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.name));
    IPHASE_NAME(node) = name;
    watchpoint_add(&(IPHASE_IPREFIX(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.iprefix));
    IPHASE_IPREFIX(node) = NULL;
    watchpoint_add(&(IPHASE_GATE_FUNC(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.gate_func));
    IPHASE_GATE_FUNC(node) = NULL;
    watchpoint_add(&(IPHASE_IACTIONS(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.iactions));
    IPHASE_IACTIONS(node) = NULL;
    watchpoint_add(&(IPHASE_NEXT(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.next));
    IPHASE_NEXT(node) = NULL;
    watchpoint_add(&(IPHASE_IS_START(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.is_start));
    IPHASE_IS_START(node) = is_start;
    watchpoint_add(&(IPHASE_IS_CYCLE(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.is_cycle));
    IPHASE_IS_CYCLE(node) = 0;
    watchpoint_add(&(IPHASE_IINFO(node)), &wphandler, &(HIST_IPHASE(NODE_HIST(node))->hist.hist_items.iinfo));
    IPHASE_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_iphase->iphase_children.iphase_children_at;
    return node;}

node_st *ASTiactions() {
    node_st *node = NewNode();
    node->data.N_iactions = wpalloc(sizeof(struct NODE_DATA_IACTIONS));
    NODE_TYPE(node) = NT_IACTIONS;
    NODE_HIST(node)->data.NH_iactions = MEMcalloc(sizeof(struct NODE_HIST_IACTIONS));
    watchpoint_add(&(IACTIONS_REFERENCE(node)), &wphandler, &(HIST_IACTIONS(NODE_HIST(node))->hist.hist_items.reference));
    IACTIONS_REFERENCE(node) = NULL;
    watchpoint_add(&(IACTIONS_NEXT(node)), &wphandler, &(HIST_IACTIONS(NODE_HIST(node))->hist.hist_items.next));
    IACTIONS_NEXT(node) = NULL;
    watchpoint_add(&(IACTIONS_ACTION_ID(node)), &wphandler, &(HIST_IACTIONS(NODE_HIST(node))->hist.hist_items.action_id));
    IACTIONS_ACTION_ID(node) = 0;
    NODE_NUMCHILDREN(node) = 2;
    NODE_CHILDREN(node) = node->data.N_iactions->iactions_children.iactions_children_at;
    return node;}

node_st *ASTast() {
    node_st *node = NewNode();
    node->data.N_ast = wpalloc(sizeof(struct NODE_DATA_AST));
    NODE_TYPE(node) = NT_AST;
    NODE_HIST(node)->data.NH_ast = MEMcalloc(sizeof(struct NODE_HIST_AST));
    watchpoint_add(&(AST_IPHASES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.iphases));
    AST_IPHASES(node) = NULL;
    watchpoint_add(&(AST_ITRAVERSALS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.itraversals));
    AST_ITRAVERSALS(node) = NULL;
    watchpoint_add(&(AST_IPASSES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.ipasses));
    AST_IPASSES(node) = NULL;
    watchpoint_add(&(AST_INODES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.inodes));
    AST_INODES(node) = NULL;
    watchpoint_add(&(AST_INODESETS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.inodesets));
    AST_INODESETS(node) = NULL;
    watchpoint_add(&(AST_ENUMS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.enums));
    AST_ENUMS(node) = NULL;
    watchpoint_add(&(AST_STABLE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.stable));
    AST_STABLE(node) = NULL;
    watchpoint_add(&(AST_NUM_TRAVERSALS(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.num_traversals));
    AST_NUM_TRAVERSALS(node) = 0;
    watchpoint_add(&(AST_NUM_NODES(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.num_nodes));
    AST_NUM_NODES(node) = 0;
    watchpoint_add(&(AST_ROOT_NODE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.root_node));
    AST_ROOT_NODE(node) = NULL;
    watchpoint_add(&(AST_START_PHASE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.start_phase));
    AST_START_PHASE(node) = NULL;
    watchpoint_add(&(AST_USES_UNSAFE(node)), &wphandler, &(HIST_AST(NODE_HIST(node))->hist.hist_items.uses_unsafe));
    AST_USES_UNSAFE(node) = false;
    NODE_NUMCHILDREN(node) = 7;
    NODE_CHILDREN(node) = node->data.N_ast->ast_children.ast_children_at;
    return node;}

