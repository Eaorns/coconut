#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include "assert.h"

#include "globals.h"
#include "commandline.h"
#include "gen_helpers/out_macros.h"
#include "palm/ctinfo.h"
#include "palm/str.h"
#include "ccn/dynamic_core.h"
#include "dynamic_backend/gen_helpers.h"

enum debug_gen_action {
    DGA_name_to_int,
    DGA_int_to_name,
    DGA_gettype,
    DGA_getptr,
    DGA_setval,
    DGA_ischild,
    DGA_nodename,
    DGA_nodehist,
    DGA_node_numvals,
};

enum debug_gen_action curr_gen_action;
int counter;
char *curr_node_name;

node_st *DGDFast(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;

    GNopenIncludeFile(ctx, "debugger_helper.h");
    OUT("#include \"ccngen/ast.h\"\n");
    if (global_command_line.include_debugger) {
        OUT("#ifdef INCLUDE_DEBUGGER\n");
        OUT_FIELD("int DBGHelper_ntoi(enum ccn_nodetype type, char *name)");
        OUT_FIELD("char *DBGHelper_iton(enum ccn_nodetype type, int idx)");
        OUT_FIELD("enum H_DATTYPES DBGHelper_gettype(enum ccn_nodetype type, int idx)");
        OUT_FIELD("void *DBGHelper_getptr(node_st *node, int idx)");
        OUT_FIELD("void DBGHelper_setval(node_st *node, int idx, void *val)");
        OUT_FIELD("int DBGHelper_ischild(enum ccn_nodetype type, int idx)");
        OUT_FIELD("char *DBGHelper_nodename(enum ccn_nodetype type)");
        OUT_FIELD("hist_item **DBGHelper_nodehist(enum ccn_nodetype type, ccn_hist *hist, int idx)");
        OUT_FIELD("int DBGHelper_node_numvals(enum ccn_nodetype type)");
        OUT("#endif\n");
    }

    GNopenSourceFile(ctx, "debugger_helper.c");
    OUT("#include \"ccngen/ast.h\"\n");
    OUT("#include \"ccngen/debugger_helper.h\"\n");

    if (!global_command_line.include_debugger) {
        return node;
    }

    OUT("#ifdef INCLUDE_DEBUGGER\n");
    OUT("#include <stddef.h>\n");
    OUT("#include \"palm/str.h\"\n");

    curr_gen_action = DGA_name_to_int;
    OUT_START_FUNC("int DBGHelper_ntoi(enum ccn_nodetype type, char *name)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return -1");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_int_to_name;
    OUT_START_FUNC("char *DBGHelper_iton(enum ccn_nodetype type, int idx)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return NULL");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_gettype;
    OUT_START_FUNC("enum H_DATTYPES DBGHelper_gettype(enum ccn_nodetype type, int idx)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return HDT_NULL");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_getptr;
    OUT_START_FUNC("void *DBGHelper_getptr(node_st *node, int idx)");
    OUT_BEGIN_SWITCH("NODE_TYPE(node)");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return NULL");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_setval;
    OUT_START_FUNC("void DBGHelper_setval(node_st *node, int idx, void *val)");
    OUT_FIELD("void **val_ref = &val");
    OUT_BEGIN_SWITCH("NODE_TYPE(node)");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_END_CASE();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_ischild;
    OUT_START_FUNC("int DBGHelper_ischild(enum ccn_nodetype type, int idx)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return -1");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_nodename;
    OUT_START_FUNC("char *DBGHelper_nodename(enum ccn_nodetype type)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return NULL");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_nodehist;
    OUT_START_FUNC("hist_item **DBGHelper_nodehist(enum ccn_nodetype type, ccn_hist *hist, int idx)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return NULL");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    curr_gen_action = DGA_node_numvals;
    OUT_START_FUNC("int DBGHelper_node_numvals(enum ccn_nodetype type)");
    OUT_BEGIN_SWITCH("type");
    TRAVchildren(node);
    OUT_BEGIN_DEFAULT_CASE();
    OUT_FIELD("return -1");
    OUT_END_CASE_NO_BREAK();
    OUT_END_SWITCH();
    OUT_END_FUNC();

    OUT("#endif\n");

    return node;
}

node_st *DGDFinode(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;

    switch (curr_gen_action) {
        case DGA_name_to_int:
            counter = 0;
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_FIELD("return -1");
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_int_to_name:
            counter = 0;
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_BEGIN_SWITCH("idx");
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_BEGIN_DEFAULT_CASE();
            OUT_FIELD("return NULL");
            OUT_END_CASE_NO_BREAK();
            OUT_END_SWITCH();
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_gettype:
            counter = 0;
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_BEGIN_SWITCH("idx");
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_BEGIN_DEFAULT_CASE();
            OUT_FIELD("return HDT_NULL");
            OUT_END_CASE_NO_BREAK();
            OUT_END_SWITCH();
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_getptr:
            counter = 0;
            curr_node_name = ID_UPR(INODE_NAME(node));
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_BEGIN_SWITCH("idx");
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_BEGIN_DEFAULT_CASE();
            OUT_FIELD("return NULL");
            OUT_END_CASE_NO_BREAK();
            OUT_END_SWITCH();
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_setval:
            counter = 0;
            curr_node_name = ID_UPR(INODE_NAME(node));
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_BEGIN_SWITCH("idx");
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_BEGIN_DEFAULT_CASE();
            OUT_END_CASE();
            OUT_END_SWITCH();
            OUT_END_CASE();
            break;

        case DGA_ischild:
            counter = 0;
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_BEGIN_SWITCH("idx");
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_BEGIN_DEFAULT_CASE();
            OUT_FIELD("return -1");
            OUT_END_CASE_NO_BREAK();
            OUT_END_SWITCH();
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_nodename:
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_FIELD("return \"%s\"", ID_LWR(INODE_NAME(node)));
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_nodehist:
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            OUT_FIELD("return (hist_item**)&(HIST_%s(hist)->hist.hist_list[idx])", ID_UPR(INODE_NAME(node)));
            OUT_END_CASE_NO_BREAK();
            break;

        case DGA_node_numvals:
            counter = 0;
            OUT_BEGIN_CASE("NT_%s", ID_UPR(INODE_NAME(node)));
            TRAVopt(INODE_ICHILDREN(node));
            TRAVopt(INODE_IATTRIBUTES(node));
            OUT_FIELD("return %i", counter);
            OUT_END_CASE_NO_BREAK();
        default:
            break;
    }

    TRAVopt(INODE_NEXT(node));
    return node;
}


node_st *DGDFchild(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;

    switch (curr_gen_action) {
        case DGA_name_to_int:
            OUT_FIELD("if (STReq(name, \"%s\")) return %i", ID_LWR(CHILD_NAME(node)), counter++);
            break;
        case DGA_int_to_name:
            OUT_FIELD("case %i: return \"%s\"", counter++, ID_LWR(CHILD_NAME(node)));
            break;
        case DGA_gettype:
            OUT_FIELD("case %i: return HDT_link", counter++);
            break;
        case DGA_getptr:
            OUT_FIELD("case %i: return (void*)&(%s_%s(node))", counter++, curr_node_name, ID_UPR(CHILD_NAME(node)));
            break;
        case DGA_setval:
            OUT_FIELD("case %i: %s_%s(node) = (node_st*)val; break", counter++, curr_node_name, ID_UPR(CHILD_NAME(node)));
            break;
        case DGA_ischild:
            OUT_FIELD("case %i: return 1", counter++);
            break;
        case DGA_node_numvals:
            counter++;
            break;
        default:
            break;
    }

    TRAVchildren(node);
    return node;
}

node_st *DGDFattribute(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;

    switch (curr_gen_action) {
        case DGA_name_to_int:
            OUT_FIELD("if (STReq(name, \"%s\")) return %i", ID_LWR(ATTRIBUTE_NAME(node)), counter++);
            break;
        case DGA_int_to_name:
            OUT_FIELD("case %i: return \"%s\"", counter++, ID_LWR(ATTRIBUTE_NAME(node)));
            break;
        case DGA_gettype:
            OUT_FIELD("case %i: return HDT_%s", counter++, FMTattributeTypeName(ATTRIBUTE_TYPE(node)));
            break;
        case DGA_getptr:
            OUT_FIELD("case %i: return (void*)&(%s_%s(node))", counter++, curr_node_name, ID_UPR(ATTRIBUTE_NAME(node)));
            break;
        case DGA_setval:
            switch (ATTRIBUTE_TYPE(node)) {
                case AT_link:
                    OUT_FIELD("case %i: %s_%s(node) = (node_st*)val; break", counter++, curr_node_name, ID_UPR(ATTRIBUTE_NAME(node)));
                    break;
                case AT_link_or_enum:
                    OUT_FIELD("case %i: %s_%s(node) = *(int*)val_ref; break", counter++, curr_node_name, ID_UPR(ATTRIBUTE_NAME(node)));
                    break;
                case AT_user:
                    OUT_FIELD("case %i: %s_%s(node) = val; break", counter++, curr_node_name, ID_UPR(ATTRIBUTE_NAME(node)));
                    break;
                default:
                    OUT_FIELD("case %i: %s_%s(node) = *(%s*)val_ref; break", counter++, curr_node_name, ID_UPR(ATTRIBUTE_NAME(node)),
                              FMTattributeTypeToString(ATTRIBUTE_TYPE(node)));
            }
            break;
        case DGA_ischild:
            OUT_FIELD("case %i: return 0", counter++);
            return node;
        case DGA_node_numvals:
            counter++;
            break;
        default:
            break;
    }

    TRAVchildren(node);
    return node;
}
