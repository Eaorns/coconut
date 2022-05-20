#include "ccngen/ast.h"
#include "ccn/dynamic_core.h"
#include "palm/watchpoint.h"
#include "palm/watchpointalloc.h"
#include "palm/memory.h"
struct item_free_queue {
    struct ccn_node *node;
    struct item_free_queue *prev;
    struct item_free_queue *next;
};

struct item_free_queue *trash_can;
void throw_in_the_trash(struct ccn_node *node) {
    struct item_free_queue *q = MEMmalloc(sizeof(struct item_free_queue));
    q->node = node;
    if (trash_can) {
        trash_can->prev = q;
    }

    q->next = trash_can;
    q->prev = NULL;
    trash_can = q;
    node->trashed = true;
}

struct ccn_node *DELid(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELid_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_id->orig);
    MEMfree(arg_node->data.N_id->lwr);
    MEMfree(arg_node->data.N_id->upr);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_id);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELienum(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELienum_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_ienum->iinfo);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_ienum);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELattribute(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELattribute_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_attribute);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELitravdata(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELitravdata_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_itravdata->include_file);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_itravdata);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELsetoperation(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELsetoperation_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_setoperation);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELsetliteral(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELsetliteral_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_setliteral);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELsetreference(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELsetreference_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_setreference);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELste(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELste_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_ste);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELchild(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELchild_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_child);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELlifetime_range(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELlifetime_range_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_lifetime_range);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELilifetime(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELilifetime_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_ilifetime);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELinodeset(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELinodeset_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_inodeset->iinfo);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_inodeset);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELinode(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELinode_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_inode->iifno);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_inode);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELipass(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELipass_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_ipass->iifno);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_ipass);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELitraversal(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELitraversal_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_itraversal->iinfo);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_itraversal);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELiphase(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELiphase_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_iphase->iinfo);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_iphase);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELiactions(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELiactions_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_iactions);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELast(struct ccn_node *arg_node) {
    throw_in_the_trash(arg_node);
    return NULL;
}

struct ccn_node *DELast_real(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    wpfree(arg_node->data.N_ast);
    MEMfree(arg_node);
    return NULL;
}

