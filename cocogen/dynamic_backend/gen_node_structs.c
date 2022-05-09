#include <assert.h>
#include <stdio.h>

#include "ccn/dynamic_core.h"
#include "frontend/symboltable.h"
#include "gen_helpers/out_macros.h"
#include "globals.h"
#include "palm/ctinfo.h"
#include "generator/generator.h"

static char *basic_node_type = "node_st";
static int child_num = 0;
static int val_num = 0;
static node_st *ste = NULL;
static bool gen_hist_struct = false;

// TODO move this to a traversal?
void hist_item_structs()
{
    GeneratorContext *ctx = globals.gen_ctx;

    OUT_ENUM("H_DATTYPES");
    {
        for (int i = 1; i <= AT_uint64; i++) {
            OUT_ENUM_FIELD("HDT_%s", FMTattributeTypeName(i));
        }
    }
    OUT_ENUM_END();

    OUT_STRUCT("hist_item_user");
    {
        OUT_FIELD("void *val");
        OUT_FIELD("void *rip");
        OUT_FIELD("%s *prev_parent", basic_node_type);
        OUT_FIELD("struct hist_item_user *next");
    }
    OUT_STRUCT_END();

    OUT_STRUCT("hist_item_link");
    {
        OUT_FIELD("%s *val", basic_node_type);
        OUT_FIELD("void *rip");
        OUT_FIELD("struct hist_item_link *next");
    }
    OUT_STRUCT_END();

    OUT_STRUCT("hist_item_link_or_enum");
    {
        OUT_FIELD("int val");
        OUT_FIELD("void *rip");
        OUT_FIELD("struct hist_item_link_or_enum *next");
    }
    OUT_STRUCT_END();

    // TODO need a better way to loop through enum
    for (int i = 4; i <= AT_uint64; i++) {
        OUT_STRUCT("hist_item_%s", FMTattributeTypeName(i));
        {
            OUT_FIELD("%s val", FMTattributeTypeToString(i));
            OUT_FIELD("void *rip");
            OUT_FIELD("struct hist_item_%s *next", FMTattributeTypeName(i));
        }
        OUT_STRUCT_END();
    }
}

node_st *DGNSast(node_st *node)
{
    ste = AST_STABLE(node);
    hist_item_structs();
    TRAVchildren(node);
    return node;
}

node_st *DGNSinode(node_st *node)
{
    char *name_upr = ID_UPR(INODE_NAME(node));
    char *name_lwr = ID_LWR(INODE_NAME(node));
    GeneratorContext *ctx = globals.gen_ctx;

    OUT_STRUCT("NODE_DATA_%s", name_upr);
    {
        if (INODE_ICHILDREN(node)) {
            OUT_UNION("NODE_CHILDREN_%s", name_upr);
            OUT_STRUCT("NODE_CHILDREN_%s_STRUCT", name_upr);
            child_num = 0;
            TRAVdo(INODE_ICHILDREN(node));
            OUT_TYPEDEF_STRUCT_END("%s_children_st", name_lwr);
            OUT_FIELD("%s *%s_children_at[%d]", basic_node_type, name_lwr, child_num);
            OUT_TYPEDEF_STRUCT_END("%s_children", name_lwr);
        }

        TRAVopt(INODE_IATTRIBUTES(node));
    }
    OUT_FIELD("\n    struct NODE_HIST_%s *hist", name_upr);
    OUT_STRUCT_END();

    gen_hist_struct = true;
    OUT_STRUCT("NODE_HIST_%s", name_upr);
    {
        OUT_UNION("HIST_%s", name_upr);
        OUT_STRUCT("HIST_ITEMS_%s", name_upr);
        val_num = 0;
        TRAVopt(INODE_ICHILDREN(node));
        TRAVopt(INODE_IATTRIBUTES(node));
        OUT_TYPEDEF_STRUCT_END("hist_items");
        OUT_FIELD("void *hist_list[%i]", val_num);
        OUT_TYPEDEF_STRUCT_END("hist");

        OUT_FIELD("enum ccn_traversal_type trav");
        OUT_FIELD("struct NODE_HIST_%s *next", name_upr);
    }
    OUT_STRUCT_END();
    gen_hist_struct = false;

    TRAVopt(INODE_NEXT(node));
    return node;
}

node_st *DGNSchild(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (!gen_hist_struct) {
        child_num++;
        OUT_FIELD("%s *%s", basic_node_type, ID_LWR(CHILD_NAME(node)));
    } else {
        val_num++;
        OUT_FIELD("struct hist_item_link *%s", ID_LWR(CHILD_NAME(node)));
    }

    TRAVchildren(node);
    return node;
}

node_st *DGNSattribute(node_st *node)
{
    GeneratorContext *ctx = globals.gen_ctx;
    if (ATTRIBUTE_TYPE(node) == AT_link) {
        if (!gen_hist_struct)
            OUT_FIELD("%s *%s", basic_node_type, ID_LWR(ATTRIBUTE_NAME(node)));
        else
            OUT_FIELD("struct hist_item_link *%s", ID_LWR(ATTRIBUTE_NAME(node)));
    } else if (ATTRIBUTE_TYPE(node) == AT_link_or_enum) {
        if (!gen_hist_struct) {
            node_st *ref = STlookup(ste, ATTRIBUTE_TYPE_REFERENCE(node));
            // Should be handled by check_existence.
            assert(ref);
            assert(NODE_TYPE(ref) == NT_IENUM);
            OUT_FIELD("enum %s %s", ID_ORIG(IENUM_NAME(ref)), ID_LWR(ATTRIBUTE_NAME(node)));
        } else {
            OUT_FIELD("struct hist_item_link_or_enum *%s", ID_LWR(ATTRIBUTE_NAME(node)));
        }
    } else {
        if (!gen_hist_struct)
            OUT_FIELD("%s %s", FMTattributeTypeToString(ATTRIBUTE_TYPE(node)), ID_LWR(ATTRIBUTE_NAME(node)));
        else
            OUT_FIELD("struct hist_item_%s *%s", FMTattributeTypeName(ATTRIBUTE_TYPE(node)), ID_LWR(ATTRIBUTE_NAME(node)));
    }
    val_num++;
    TRAVchildren(node);
    return node;
}
