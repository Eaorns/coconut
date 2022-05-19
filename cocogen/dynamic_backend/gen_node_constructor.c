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
static char *node_name_lwr = NULL;
static char *node_name_upr = NULL;

static bool gen_wphandlerfunc = false;
static bool gen_wphandlerdata = false;

node_st *DGNCast(node_st *node)
{
    dgif_print_semicolon = false;

    GeneratorContext *ctx = globals.gen_ctx;
    OUT_STRUCT("wp_handler_data");
    {
        OUT_FIELD("size_t index");
        OUT_FIELD("size_t offset");
        OUT_FIELD("enum H_DATTYPES datatype");
        OUT_FIELD("bool is_child");
    }
    OUT_STRUCT_END();

    TRAVchildren(node);
    return node;
}

node_st *DGNCinode(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    num_children = 0;
    num_vals = 0;
    node_name_lwr = ID_LWR(INODE_NAME(node));
    node_name_upr = ID_UPR(INODE_NAME(node));

    gen_wphandlerdata = true;
    OUT("struct wp_handler_data %s_data[] = {", node_name_upr);
    TRAVopt(INODE_ICHILDREN(node));
    TRAVopt(INODE_IATTRIBUTES(node));
    OUT("};\n");
    gen_wphandlerdata = false;

    num_vals = 0;
    gen_wphandlerfunc = true;
    OUT_START_FUNC("void wphandler_%s(void *addr, void *old_val, void *ucontext, void *userdata)",
                   node_name_lwr);
    {
        OUT_FIELD("ucontext_t *context = (ucontext_t *)ucontext");
        OUT_FIELD("struct wp_handler_data *data = (struct wp_handler_data *)userdata");
        OUT_FIELD("void *rip = (void *)context->uc_mcontext.gregs[REG_RIP]");

        OUT_FIELD("struct NODE_HIST_%s *hist = (struct NODE_HIST_%s *)(&addr + data->offset)",
                  node_name_upr, node_name_upr);

        OUT_BEGIN_SWITCH("data->index");
        {
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
        }
        OUT_END_SWITCH();
    }
    OUT_END_FUNC();
    gen_wphandlerfunc = false;

    num_vals = 0;
    node_st *next = INODE_NEXT(node);
    // Set next to NULL to prevent init funcs generating others after this node.
    INODE_NEXT(node) = NULL;
    TRAVstart(node, TRAV_DGIF);

    OUT_START_FUNC_FIELD();
    {
        OUT_FIELD("%s *node = NewNode()", basic_node_type);
        OUT_FIELD("node->data.N_%s = MEMmalloc(sizeof(struct NODE_DATA_%s))", ID_LWR(INODE_NAME(node)), ID_UPR(INODE_NAME(node)));
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
        OUT("{ .index = %i, .offset = offsetof(struct NODE_DATA_%s, hist) - %i, .datatype = HDT_link, .is_child = true }, ",
            num_vals, node_name_upr, (sizeof(void *) * num_vals));
            num_vals++;
        num_children++;
    } else if (gen_wphandlerfunc) {
        OUT_BEGIN_CASE_SEMI("%i", num_vals);
        if (num_vals < num_children - 1) {
            OUT_END_CASE_NO_BREAK();
            OUT("\n");
        } else {
            OUT_FIELD("struct hist_item_link *s%i = (struct hist_item_link *)malloc(sizeof(struct hist_item_link))",
                      num_vals);
            OUT_FIELD("s%i->val = old_val", num_vals);
            OUT_FIELD("s%i->rip = rip", num_vals);
            OUT_FIELD("s%i->next = hist->hist.hist_list[data->index]", num_vals);
            OUT_FIELD("hist->hist.hist_list[data->index] = s%i", num_vals, num_vals);
            OUT_END_CASE();
        }
        num_vals++;
    } else {
        if (CHILD_IN_CONSTRUCTOR(node)) {
            OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(CHILD_NAME(node)), ID_LWR(CHILD_NAME(node)));
        } else {
            OUT_FIELD("%s_%s(node) = NULL", node_name_upr, ID_UPR(CHILD_NAME(node)));
        }
        OUT_FIELD("watchpoint_add(&(%s_%s(node)), &wphandler_%s, &(%s_data[%i]))",
                  node_name_upr, ID_UPR(CHILD_NAME(node)), node_name_lwr, node_name_upr, num_vals++);
    }

    TRAVchildren(node);
    return node;
}

node_st *DGNCattribute(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (gen_wphandlerdata) {
        OUT("{ .index = %i, .offset = offsetof(struct NODE_DATA_%s, hist) - offsetof(struct NODE_DATA_%s, %s), .datatype = HDT_%s, .is_child = false }, ",
            num_vals++, node_name_upr, node_name_upr, ID_LWR(ATTRIBUTE_NAME(node)), FMTattributeTypeName(ATTRIBUTE_TYPE(node)));
    } else if (gen_wphandlerfunc) {
        OUT_BEGIN_CASE_SEMI("%i", num_vals);
        OUT_FIELD("struct hist_item_%s *s%i = (struct hist_item_%s *)malloc(sizeof(struct hist_item_%s))",
                  FMTattributeTypeName(ATTRIBUTE_TYPE(node)), num_vals,
                  FMTattributeTypeName(ATTRIBUTE_TYPE(node)), FMTattributeTypeName(ATTRIBUTE_TYPE(node)));
        switch (ATTRIBUTE_TYPE(node)) {
        case AT_link:
        case AT_user:
            OUT_FIELD("s%i->val = old_val", num_vals);
            break;
        case AT_link_or_enum:
            OUT_FIELD("s%i->val = *(int*)(&old_val)", num_vals);
            break;
        case AT_string:
            OUT_FIELD("s%i->val = (char*)old_val", num_vals);
            break;
        default:
            OUT_FIELD("s%i->val = *(%s*)(&old_val)", num_vals, FMTattributeTypeToString(ATTRIBUTE_TYPE(node)));
        }
        OUT_FIELD("s%i->rip = rip", num_vals);
        OUT_FIELD("s%i->next = hist->hist.hist_list[%i]", num_vals);
        OUT_FIELD("hist->hist.hist_list[%i] = s%i", num_vals, num_vals);
        num_vals++;

        OUT_END_CASE();
    } else {
        if (ATTRIBUTE_IN_CONSTRUCTOR(node)) {
            OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), DGHattributeField(node));
        } else {
            OUT_FIELD("%s_%s(node) = %s", node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), FMTattributeDefaultVal(ATTRIBUTE_TYPE(node)));
        }
        OUT_FIELD("watchpoint_add(&(%s_%s(node)), &wphandler_%s, &(%s_data[%i]))",
                  node_name_upr, ID_UPR(ATTRIBUTE_NAME(node)), node_name_lwr, node_name_upr, num_vals++);
    }

    TRAVchildren(node);
    return node;
}
