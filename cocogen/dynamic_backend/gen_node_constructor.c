#include <stddef.h>
#include <stdio.h>
#include "assert.h"

#include "globals.h"
#include "gen_helpers/out_macros.h"
#include "dynamic_backend/gen_helpers.h"
#include "palm/str.h"
#include "ccn/dynamic_core.h"


extern bool dgif_print_semicolon;
static char *basic_node_type = "node_st";
static long num_children = 0;
static char *node_name_upr = NULL;

node_st *DGNCast(node_st *node)
{
    dgif_print_semicolon = false;

    GeneratorContext *ctx = globals.gen_ctx;
    OUT_START_FUNC("void wphandler(void *addr __attribute__((unused)), void *old_val, void *ucontext, void *userdata)");
    {
        OUT_FIELD("ucontext_t *context = (ucontext_t *)ucontext");
        OUT_FIELD("void *rip = (void *)context->uc_mcontext.gregs[REG_RIP]");
        OUT_FIELD("struct hist_item *s = (struct hist_item *)malloc(sizeof(struct hist_item))");
        OUT_FIELD("s->val = (void *)old_val");
        OUT_FIELD("s->rip = rip");
        OUT_FIELD("s->next = *(void**)userdata");
        OUT_FIELD("*(void**)userdata = s");
    }
    OUT_END_FUNC();

    TRAVchildren(node);
    return node;
}

node_st *DGNCinode(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    num_children = 0;
    node_st *next = INODE_NEXT(node);
    // Set next to NULL to prevent init funcs generating others after this node.
    INODE_NEXT(node) = NULL;
    TRAVstart(node, TRAV_DGIF);

    node_name_upr = ID_UPR(INODE_NAME(node));
    OUT_START_FUNC_FIELD();
    {
        OUT_FIELD("%s *node = NewNode()", basic_node_type);
        OUT_FIELD("node->data.N_%s = wpalloc(sizeof(struct NODE_DATA_%s))", ID_LWR(INODE_NAME(node)), ID_UPR(INODE_NAME(node)));
        OUT_FIELD("NODE_TYPE(node) = %s%s", "NT_", ID_UPR(INODE_NAME(node)));
        OUT_FIELD("NODE_HIST(node)->data.NH_%s = MEMmalloc(sizeof(struct NODE_HIST_%s))", ID_LWR(INODE_NAME(node)), ID_UPR(INODE_NAME(node)));

        TRAVopt(INODE_ICHILDREN(node));
        TRAVopt(INODE_IATTRIBUTES(node));
        OUT_FIELD("NODE_NUMCHILDREN(node) = %ld", num_children);
        if (num_children) {
            char *name_lwr = ID_LWR(INODE_NAME(node));
            OUT_FIELD("NODE_CHILDREN(node) = node->data.N_%s->%s_children.%s_children_at", name_lwr, name_lwr, name_lwr);
        }
        OUT("return node;");
    }
    OUT_END_FUNC();

    INODE_NEXT(node) = next;
    assert(INODE_NEXT(node) == next);

    TRAVopt(INODE_NEXT(node));
    return node;
}

node_st *DGNCchild(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    num_children++;
    if (CHILD_IN_CONSTRUCTOR(node)) {
        OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(CHILD_NAME(node)), ID_LWR(CHILD_NAME(node)));
    } else {
        OUT_FIELD("%s_%s(node) = NULL", node_name_upr, ID_UPR(CHILD_NAME(node)));
    }
    OUT_FIELD("watchpoint_add(&(%s_%s(node)), &wphandler, &(HIST_%s(NODE_HIST(node))->hist.hist_items.%s))",
              node_name_upr, ID_UPR(CHILD_NAME(node)), node_name_upr, ID_LWR(CHILD_NAME(node)));
    TRAVchildren(node);
    return node;
}

node_st *DGNCattribute(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (ATTRIBUTE_IN_CONSTRUCTOR(node)) {
        OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), DGHattributeField(node));
    } else {
        OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), FMTattributeDefaultVal(ATTRIBUTE_TYPE(node)));
    }
    OUT_FIELD("watchpoint_add(&(%s_%s(node)), &wphandler, &(HIST_%s(NODE_HIST(node))->hist.hist_items.%s))",
              node_name_upr, ID_UPR(CHILD_NAME(node)), node_name_upr, ID_LWR(ATTRIBUTE_NAME(node)));
    TRAVchildren(node);
    return node;
}
