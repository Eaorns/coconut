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
static long num_vals = 0;
static char *node_name_upr = NULL;

static bool gen_wphandlerdata = false;

node_st *DGNCast(node_st *node)
{
    dgif_print_semicolon = false;

    GeneratorContext *ctx = globals.gen_ctx;
    OUT_STRUCT("wp_handler_data");
    OUT_FIELD("size_t index");
    OUT_FIELD("size_t offset");
    OUT_FIELD("enum attribute_type datatype");
    OUT_STRUCT_END();

    OUT_START_FUNC("void handler(void *addr, long old_val, void *userdata)");
    OUT_END_FUNC();

    TRAVchildren(node);
    return node;
}

node_st *DGNCinode(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    num_children = 0;
    num_vals = 0;
    node_name_upr = ID_UPR(INODE_NAME(node));
    
    gen_wphandlerdata = true;
    OUT("struct wp_handler_data %s_data[] = {", node_name_upr);
    TRAVopt(INODE_ICHILDREN(node));
    TRAVopt(INODE_IATTRIBUTES(node));
    OUT("};\n");
    gen_wphandlerdata = false;
    
    num_vals = 0;
    node_st *next = INODE_NEXT(node);
    // Set next to NULL to prevent init funcs generating others after this node.
    INODE_NEXT(node) = NULL;
    TRAVstart(node, TRAV_DGIF);

    OUT_START_FUNC_FIELD();
    {
        OUT_FIELD("%s *node = NewNode()", basic_node_type);
        OUT_FIELD("node->data.N_%s = wpalloc(sizeof(struct NODE_DATA_%s))", ID_LWR(INODE_NAME(node)), ID_UPR(INODE_NAME(node)));
        OUT_FIELD("NODE_TYPE(node) = %s%s", "NT_", ID_UPR(INODE_NAME(node)));
        OUT_FIELD("node->data.N_%s->hist = MEMmalloc(sizeof(struct NODE_HIST_%s))", ID_LWR(INODE_NAME(node)), ID_UPR(INODE_NAME(node)));

        TRAVopt(INODE_ICHILDREN(node));
        TRAVopt(INODE_IATTRIBUTES(node));
        OUT_FIELD("NODE_NUMCHILDREN(node) = %ld", num_children);
        if (num_children) {
            char *name_lwr = ID_LWR(INODE_NAME(node));
            OUT_FIELD("NODE_CHILDREN(node) = node->data.N_%s->%s_children.%s_children_at", name_lwr, name_lwr, name_lwr);
        }
    }
    OUT("return node;");
    OUT_END_FUNC();

    INODE_NEXT(node) = next;
    assert(INODE_NEXT(node) == next);

    TRAVopt(INODE_NEXT(node));
    return node;
}

node_st *DGNCchild(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (gen_wphandlerdata) {
        OUT("{ .index = %i, .offset = offsetof(struct NODE_DATA_%s, hist) - %i, .datatype = %i}, ",
            num_vals, node_name_upr, (sizeof(void *) * num_vals), AT_link);
            num_vals++;
    } else {
        num_children++;
        if (CHILD_IN_CONSTRUCTOR(node)) {
            OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(CHILD_NAME(node)), ID_LWR(CHILD_NAME(node)));
        } else {
            OUT_FIELD("%s_%s(node) = NULL", node_name_upr, ID_UPR(CHILD_NAME(node)));
        }
        OUT_FIELD("watchpoint_add(&(%s_%s(node)), &handler, &(%s_data[%i]))", node_name_upr, ID_UPR(CHILD_NAME(node)), node_name_upr, num_vals++);
    }

    TRAVchildren(node);
    return node;
}

node_st *DGNCattribute(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (gen_wphandlerdata) {
        OUT("{ .index = %i, .offset = offsetof(struct NODE_DATA_%s, hist) - offsetof(struct NODE_DATA_%s, %s), .datatype = %i}, ",
            num_vals++, node_name_upr, node_name_upr, ID_LWR(ATTRIBUTE_NAME(node)), ATTRIBUTE_TYPE(node));
    } else {
        if (ATTRIBUTE_IN_CONSTRUCTOR(node)) {
            OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), DGHattributeField(node));
        } else {
            OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), FMTattributeDefaultVal(ATTRIBUTE_TYPE(node)));
        }
        OUT_FIELD("watchpoint_add(&(%s_%s(node)), &handler, &(%s_data[%i]))", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), node_name_upr, num_vals++);
    }

    TRAVchildren(node);
    return node;
}
