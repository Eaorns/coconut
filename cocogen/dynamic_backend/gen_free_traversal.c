#include "assert.h"
#include <globals.h>
#include <stddef.h>
#include <stdio.h>

#include "commandline.h"
#include "gen_helpers/out_macros.h"
#include "palm/ctinfo.h"
#include "palm/str.h"
#include "ccn/dynamic_core.h"


static node_st *ast;
static node_st *curr_node;
bool generating_free_all = false;

node_st *DGFTast(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    GNopenSourceFile(ctx, "ccn_free.c");
    OUT("#include \"ccngen/ast.h\"\n");
    OUT("#include \"ccn/dynamic_core.h\"\n");
    OUT("#include \"palm/memory.h\"\n");
    if (global_command_line.include_debugger) {
        OUT("#ifdef INCLUDE_DEBUGGER\n");
        OUT("#include \"palm/watchpoint.h\"\n");
        OUT("#include \"palm/watchpointalloc.h\"\n");
        OUT("#endif\n");
    }
    ast = node;
    if (global_command_line.include_debugger) {
        OUT("#ifdef INCLUDE_DEBUGGER\n");
        OUT_STRUCT("item_free_queue");
        {
            OUT_FIELD("struct ccn_node *node");
            OUT_FIELD("struct item_free_queue *prev");
            OUT_FIELD("struct item_free_queue *next");
        }
        OUT_STRUCT_END();
        OUT_FIELD("struct item_free_queue *trash_can");
        OUT_START_FUNC("void mark_trashed(struct ccn_node *node)");
        OUT_FIELD("struct item_free_queue *q = MEMmalloc(sizeof(struct item_free_queue))");
        OUT_FIELD("q->node = node");
        OUT_BEGIN_IF("trash_can");
        OUT_FIELD("trash_can->prev = q");
        OUT_END_IF();
        OUT_FIELD("q->next = trash_can");
        OUT_FIELD("q->prev = NULL");
        OUT_FIELD("trash_can = q");
        OUT_FIELD("node->trashed = true");
        OUT_END_FUNC();
        OUT("#endif\n");
    }

    TRAVopt(AST_INODES(node));

    if (global_command_line.include_debugger) {
        OUT("#ifdef INCLUDE_DEBUGGER\n");
        OUT_START_FUNC("void free_bin()");
        OUT_FIELD("struct item_free_queue *next");
        OUT_BEGIN_WHILE("trash_can != NULL");
        OUT_BEGIN_SWITCH("NODE_TYPE(trash_can->node)");

        generating_free_all = true;
        TRAVopt(AST_INODES(node));
        generating_free_all = false;

        OUT_BEGIN_DEFAULT_CASE();
        OUT_END_CASE();

        OUT_END_SWITCH();
        OUT_FIELD("next = trash_can->next");
        OUT_FIELD("free(trash_can)");
        OUT_FIELD("trash_can = next");
        OUT_END_WHILE();
        OUT_END_FUNC();
        OUT("#endif\n");
    }

    return node;
}

node_st *DGFTiactions(node_st *node)
{
    return node;
}

node_st *DGFTiphase(node_st *node)
{
    return node;
}

node_st *DGFTitraversal(node_st *node)
{
    return node;
}

node_st *DGFTitravdata(node_st *node)
{
    return node;
}

node_st *DGFTipass(node_st *node)
{
    TRAVchildren(node);
    return node;
}

node_st *DGFTinode(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;

    if (generating_free_all) {
        OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
        OUT_FIELD("DEL%s_real(trash_can->node)", ID_LWR(INODE_NAME(node)));
        OUT_END_CASE();
    } else {
        curr_node = node;
        OUT_START_FUNC("struct ccn_node *DEL%s(struct ccn_node *arg_node)", ID_LWR(INODE_NAME(node)));
        if (INODE_ICHILDREN(node)) {
            OUT_FIELD("TRAVchildren(arg_node)");
        }
        if (global_command_line.include_debugger) {
            OUT("#ifdef INCLUDE_DEBUGGER\n");
            OUT_FIELD("mark_trashed(arg_node)");
            OUT("#else\n");
        }
        TRAVopt(INODE_IATTRIBUTES(node));
        OUT_FIELD("MEMfree(NODE_FILENAME(arg_node))");
        OUT_FIELD("MEMfree(arg_node->data.N_%s)", ID_LWR(INODE_NAME(node)));
        OUT_FIELD("MEMfree(arg_node)");
        if (global_command_line.include_debugger) {
            OUT("#endif\n");
        }
        OUT_FIELD("return NULL");
        OUT_END_FUNC();

        if (global_command_line.include_debugger) {
            OUT("#ifdef INCLUDE_DEBUGGER\n");
            OUT_START_FUNC("struct ccn_node *DEL%s_real(struct ccn_node *arg_node)", ID_LWR(INODE_NAME(node)));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_FIELD("MEMfree(NODE_FILENAME(arg_node))");
            OUT_FIELD("wpfree(arg_node->data.N_%s)", ID_LWR(INODE_NAME(node)));
            OUT_FIELD("MEMfree(arg_node)");
            OUT_FIELD("return NULL");
            OUT_END_FUNC();
            OUT("#endif\n");
        }
    }

    TRAVopt(INODE_NEXT(node));
    return node;
}

node_st *DGFTinodeset(node_st *node)
{
    TRAVchildren(node);
    return node;
}

node_st *DGFTchild(node_st *node)
{

    return node;
}

node_st *DGFTattribute(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (ATTRIBUTE_TYPE(node) == AT_string) {
        OUT_FIELD("MEMfree(arg_node->data.N_%s->%s)", ID_LWR(INODE_NAME(curr_node)), ID_LWR(ATTRIBUTE_NAME(node)));
    }
    TRAVopt(ATTRIBUTE_NEXT(node));
    return node;
}

node_st *DGFTste(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTsetoperation(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTsetliteral(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTsetreference(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTienum(node_st *node)
{
    return node;
}

node_st *DGFTid(node_st *node)
{
    return node;
}

node_st *DGFTilifetime(node_st *node)
{
    return node;
}

node_st *DGFTlifetime_range(node_st *node)
{
    return node;
}
