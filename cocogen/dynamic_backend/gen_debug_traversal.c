#include "assert.h"
#include <globals.h>
#include <stddef.h>
#include <stdio.h>

#include "gen_helpers/out_macros.h"
#include "palm/ctinfo.h"
#include "palm/str.h"
#include "ccn/dynamic_core.h"


static node_st *ast;
static node_st *curr_node;

node_st *DGDTast(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    GNopenSourceFile(ctx, "ccn_debug.c");
    OUT("#include \"ccngen/ast.h\"\n");
    OUT("#include \"ccn/dynamic_core.h\"\n");
    OUT("#include \"palm/memory.h\"\n");
    OUT("#include \"ccn/ccn_dbg.h\"\n");
    OUT("\n");
    OUT_FIELD("struct ccn_node *parent = NULL");
    OUT("\n");
    ast = node;
    TRAVopt(AST_INODES(node));
    return node;
}

node_st *DGDTiactions(node_st *node)
{
    return node;
}

node_st *DGDTiphase(node_st *node)
{
    return node;
}

node_st *DGDTitraversal(node_st *node)
{
    return node;
}

node_st *DGDTitravdata(node_st *node)
{
    return node;
}

node_st *DGDTipass(node_st *node)
{
    TRAVchildren(node);
    return node;
}

node_st *DGDTinode(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    curr_node = node;
    OUT_START_FUNC("struct ccn_node *DBG%s(struct ccn_node *arg_node)", ID_LWR(INODE_NAME(node)));
    {
        OUT_FIELD("arg_node->parent = parent");
        if (INODE_ICHILDREN(node)) {
            OUT_FIELD("struct ccn_node *curr_parent = parent");
            OUT_FIELD("parent = arg_node");
            OUT_FIELD("TRAVchildren(arg_node)");
            OUT_FIELD("parent = curr_parent");
        }
        OUT_FIELD("return arg_node");
    }
    OUT_END_FUNC();
    TRAVopt(INODE_NEXT(node));
    return node;
}

node_st *DGDTinodeset(node_st *node)
{
    TRAVchildren(node);
    return node;
}

node_st *DGDTchild(node_st *node)
{

    return node;
}

node_st *DGDTattribute(node_st *node)
{
    return node;
}

node_st *DGDTste(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGDTsetoperation(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGDTsetliteral(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGDTsetreference(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGDTienum(node_st *node)
{
    return node;
}

node_st *DGDTid(node_st *node)
{
    return node;
}

node_st *DGDTilifetime(node_st *node)
{
    return node;
}

node_st *DGDTlifetime_range(node_st *node)
{
    return node;
}
