#pragma once
#pragma once
#include "ccn/ccn_types.h"
#include "ccngen/enum.h"
typedef struct ccn_node node_st;
enum H_DATTYPES {
    HDT_NULL,
    HDT_user,
    HDT_link,
    HDT_link_or_enum,
    HDT_int,
    HDT_string,
    HDT_bool,
    HDT_int8,
    HDT_int16,
    HDT_int32,
    HDT_int64,
    HDT_float,
    HDT_double,
    HDT_uint,
    HDT_uint8,
    HDT_uint16,
    HDT_uint32,
    HDT_uint64,
};

typedef struct hist_item {
    void *val;
    void *rip;
    struct hist_item *next;
} hist_item;

struct NODE_DATA_ID {
    union NODE_CHILDREN_ID {
        struct NODE_CHILDREN_ID_STRUCT {
            node_st *next;
        } id_children_st;

        node_st *id_children_at[1];
    } id_children;

    char * orig;
    char * lwr;
    char * upr;
    int row;
    int col_begin;
    int col_end;
};

struct NODE_HIST_ID {
    union HIST_ID {
        struct HIST_ITEMS_ID {
            hist_item *next;
            hist_item *orig;
            hist_item *lwr;
            hist_item *upr;
            hist_item *row;
            hist_item *col_begin;
            hist_item *col_end;
        } hist_items;

        void *hist_list[7];
    } hist;

};

struct NODE_DATA_IENUM {
    union NODE_CHILDREN_IENUM {
        struct NODE_CHILDREN_IENUM_STRUCT {
            node_st *vals;
            node_st *name;
            node_st *iprefix;
            node_st *next;
        } ienum_children_st;

        node_st *ienum_children_at[4];
    } ienum_children;

    char * iinfo;
};

struct NODE_HIST_IENUM {
    union HIST_IENUM {
        struct HIST_ITEMS_IENUM {
            hist_item *vals;
            hist_item *name;
            hist_item *iprefix;
            hist_item *next;
            hist_item *iinfo;
        } hist_items;

        void *hist_list[5];
    } hist;

};

struct NODE_DATA_ATTRIBUTE {
    union NODE_CHILDREN_ATTRIBUTE {
        struct NODE_CHILDREN_ATTRIBUTE_STRUCT {
            node_st *name;
            node_st *type_reference;
            node_st *lifetimes;
            node_st *next;
        } attribute_children_st;

        node_st *attribute_children_at[4];
    } attribute_children;

    enum attribute_type type;
    int in_constructor;
};

struct NODE_HIST_ATTRIBUTE {
    union HIST_ATTRIBUTE {
        struct HIST_ITEMS_ATTRIBUTE {
            hist_item *name;
            hist_item *type_reference;
            hist_item *lifetimes;
            hist_item *next;
            hist_item *type;
            hist_item *in_constructor;
        } hist_items;

        void *hist_list[6];
    } hist;

};

struct NODE_DATA_ITRAVDATA {
    union NODE_CHILDREN_ITRAVDATA {
        struct NODE_CHILDREN_ITRAVDATA_STRUCT {
            node_st *name;
            node_st *type_reference;
            node_st *next;
        } itravdata_children_st;

        node_st *itravdata_children_at[3];
    } itravdata_children;

    enum attribute_type type;
    char * include_file;
};

struct NODE_HIST_ITRAVDATA {
    union HIST_ITRAVDATA {
        struct HIST_ITEMS_ITRAVDATA {
            hist_item *name;
            hist_item *type_reference;
            hist_item *next;
            hist_item *type;
            hist_item *include_file;
        } hist_items;

        void *hist_list[5];
    } hist;

};

struct NODE_DATA_SETOPERATION {
    union NODE_CHILDREN_SETOPERATION {
        struct NODE_CHILDREN_SETOPERATION_STRUCT {
            node_st *left;
            node_st *right;
        } setoperation_children_st;

        node_st *setoperation_children_at[2];
    } setoperation_children;

    enum setoperation_type type;
};

struct NODE_HIST_SETOPERATION {
    union HIST_SETOPERATION {
        struct HIST_ITEMS_SETOPERATION {
            hist_item *left;
            hist_item *right;
            hist_item *type;
        } hist_items;

        void *hist_list[3];
    } hist;

};

struct NODE_DATA_SETLITERAL {
    union NODE_CHILDREN_SETLITERAL {
        struct NODE_CHILDREN_SETLITERAL_STRUCT {
            node_st *reference;
            node_st *left;
            node_st *right;
        } setliteral_children_st;

        node_st *setliteral_children_at[3];
    } setliteral_children;

};

struct NODE_HIST_SETLITERAL {
    union HIST_SETLITERAL {
        struct HIST_ITEMS_SETLITERAL {
            hist_item *reference;
            hist_item *left;
            hist_item *right;
        } hist_items;

        void *hist_list[3];
    } hist;

};

struct NODE_DATA_SETREFERENCE {
    union NODE_CHILDREN_SETREFERENCE {
        struct NODE_CHILDREN_SETREFERENCE_STRUCT {
            node_st *reference;
        } setreference_children_st;

        node_st *setreference_children_at[1];
    } setreference_children;

};

struct NODE_HIST_SETREFERENCE {
    union HIST_SETREFERENCE {
        struct HIST_ITEMS_SETREFERENCE {
            hist_item *reference;
        } hist_items;

        void *hist_list[1];
    } hist;

};

struct NODE_DATA_STE {
    union NODE_CHILDREN_STE {
        struct NODE_CHILDREN_STE_STRUCT {
            node_st *next;
        } ste_children_st;

        node_st *ste_children_at[1];
    } ste_children;

    node_st *key;
    node_st *value;
};

struct NODE_HIST_STE {
    union HIST_STE {
        struct HIST_ITEMS_STE {
            hist_item *next;
            hist_item *key;
            hist_item *value;
        } hist_items;

        void *hist_list[3];
    } hist;

};

struct NODE_DATA_CHILD {
    union NODE_CHILDREN_CHILD {
        struct NODE_CHILDREN_CHILD_STRUCT {
            node_st *name;
            node_st *lifetimes;
            node_st *next;
            node_st *type_reference;
        } child_children_st;

        node_st *child_children_at[4];
    } child_children;

    enum child_type type;
    int in_constructor;
    int is_mandatory;
};

struct NODE_HIST_CHILD {
    union HIST_CHILD {
        struct HIST_ITEMS_CHILD {
            hist_item *name;
            hist_item *lifetimes;
            hist_item *next;
            hist_item *type_reference;
            hist_item *type;
            hist_item *in_constructor;
            hist_item *is_mandatory;
        } hist_items;

        void *hist_list[7];
    } hist;

};

struct NODE_DATA_LIFETIME_RANGE {
    union NODE_CHILDREN_LIFETIME_RANGE {
        struct NODE_CHILDREN_LIFETIME_RANGE_STRUCT {
            node_st *target;
        } lifetime_range_children_st;

        node_st *lifetime_range_children_at[1];
    } lifetime_range_children;

    bool inclusive;
    int action_id;
    int next_action_id;
};

struct NODE_HIST_LIFETIME_RANGE {
    union HIST_LIFETIME_RANGE {
        struct HIST_ITEMS_LIFETIME_RANGE {
            hist_item *target;
            hist_item *inclusive;
            hist_item *action_id;
            hist_item *next_action_id;
        } hist_items;

        void *hist_list[4];
    } hist;

};

struct NODE_DATA_ILIFETIME {
    union NODE_CHILDREN_ILIFETIME {
        struct NODE_CHILDREN_ILIFETIME_STRUCT {
            node_st *begin;
            node_st *end;
            node_st *next;
        } ilifetime_children_st;

        node_st *ilifetime_children_at[3];
    } ilifetime_children;

    enum lifetime_type type;
};

struct NODE_HIST_ILIFETIME {
    union HIST_ILIFETIME {
        struct HIST_ITEMS_ILIFETIME {
            hist_item *begin;
            hist_item *end;
            hist_item *next;
            hist_item *type;
        } hist_items;

        void *hist_list[4];
    } hist;

};

struct NODE_DATA_INODESET {
    union NODE_CHILDREN_INODESET {
        struct NODE_CHILDREN_INODESET_STRUCT {
            node_st *name;
            node_st *expr;
            node_st *unpacked;
            node_st *next;
        } inodeset_children_st;

        node_st *inodeset_children_at[4];
    } inodeset_children;

    char * iinfo;
};

struct NODE_HIST_INODESET {
    union HIST_INODESET {
        struct HIST_ITEMS_INODESET {
            hist_item *name;
            hist_item *expr;
            hist_item *unpacked;
            hist_item *next;
            hist_item *iinfo;
        } hist_items;

        void *hist_list[5];
    } hist;

};

struct NODE_DATA_INODE {
    union NODE_CHILDREN_INODE {
        struct NODE_CHILDREN_INODE_STRUCT {
            node_st *name;
            node_st *next;
            node_st *ichildren;
            node_st *iattributes;
            node_st *lifetimes;
        } inode_children_st;

        node_st *inode_children_at[5];
    } inode_children;

    char * iifno;
    int is_root;
    int index;
};

struct NODE_HIST_INODE {
    union HIST_INODE {
        struct HIST_ITEMS_INODE {
            hist_item *name;
            hist_item *next;
            hist_item *ichildren;
            hist_item *iattributes;
            hist_item *lifetimes;
            hist_item *iifno;
            hist_item *is_root;
            hist_item *index;
        } hist_items;

        void *hist_list[8];
    } hist;

};

struct NODE_DATA_IPASS {
    union NODE_CHILDREN_IPASS {
        struct NODE_CHILDREN_IPASS_STRUCT {
            node_st *name;
            node_st *iprefix;
            node_st *target_func;
            node_st *next;
        } ipass_children_st;

        node_st *ipass_children_at[4];
    } ipass_children;

    char * iifno;
};

struct NODE_HIST_IPASS {
    union HIST_IPASS {
        struct HIST_ITEMS_IPASS {
            hist_item *name;
            hist_item *iprefix;
            hist_item *target_func;
            hist_item *next;
            hist_item *iifno;
        } hist_items;

        void *hist_list[5];
    } hist;

};

struct NODE_DATA_ITRAVERSAL {
    union NODE_CHILDREN_ITRAVERSAL {
        struct NODE_CHILDREN_ITRAVERSAL_STRUCT {
            node_st *name;
            node_st *iprefix;
            node_st *inodes;
            node_st *data;
            node_st *next;
        } itraversal_children_st;

        node_st *itraversal_children_at[5];
    } itraversal_children;

    int index;
    char * iinfo;
};

struct NODE_HIST_ITRAVERSAL {
    union HIST_ITRAVERSAL {
        struct HIST_ITEMS_ITRAVERSAL {
            hist_item *name;
            hist_item *iprefix;
            hist_item *inodes;
            hist_item *data;
            hist_item *next;
            hist_item *index;
            hist_item *iinfo;
        } hist_items;

        void *hist_list[7];
    } hist;

};

struct NODE_DATA_IPHASE {
    union NODE_CHILDREN_IPHASE {
        struct NODE_CHILDREN_IPHASE_STRUCT {
            node_st *name;
            node_st *iprefix;
            node_st *gate_func;
            node_st *iactions;
            node_st *next;
        } iphase_children_st;

        node_st *iphase_children_at[5];
    } iphase_children;

    int is_start;
    int is_cycle;
    char * iinfo;
};

struct NODE_HIST_IPHASE {
    union HIST_IPHASE {
        struct HIST_ITEMS_IPHASE {
            hist_item *name;
            hist_item *iprefix;
            hist_item *gate_func;
            hist_item *iactions;
            hist_item *next;
            hist_item *is_start;
            hist_item *is_cycle;
            hist_item *iinfo;
        } hist_items;

        void *hist_list[8];
    } hist;

};

struct NODE_DATA_IACTIONS {
    union NODE_CHILDREN_IACTIONS {
        struct NODE_CHILDREN_IACTIONS_STRUCT {
            node_st *reference;
            node_st *next;
        } iactions_children_st;

        node_st *iactions_children_at[2];
    } iactions_children;

    int action_id;
};

struct NODE_HIST_IACTIONS {
    union HIST_IACTIONS {
        struct HIST_ITEMS_IACTIONS {
            hist_item *reference;
            hist_item *next;
            hist_item *action_id;
        } hist_items;

        void *hist_list[3];
    } hist;

};

struct NODE_DATA_AST {
    union NODE_CHILDREN_AST {
        struct NODE_CHILDREN_AST_STRUCT {
            node_st *iphases;
            node_st *itraversals;
            node_st *ipasses;
            node_st *inodes;
            node_st *inodesets;
            node_st *enums;
            node_st *stable;
        } ast_children_st;

        node_st *ast_children_at[7];
    } ast_children;

    int num_traversals;
    int num_nodes;
    node_st *root_node;
    node_st *start_phase;
    bool uses_unsafe;
};

struct NODE_HIST_AST {
    union HIST_AST {
        struct HIST_ITEMS_AST {
            hist_item *iphases;
            hist_item *itraversals;
            hist_item *ipasses;
            hist_item *inodes;
            hist_item *inodesets;
            hist_item *enums;
            hist_item *stable;
            hist_item *num_traversals;
            hist_item *num_nodes;
            hist_item *root_node;
            hist_item *start_phase;
            hist_item *uses_unsafe;
        } hist_items;

        void *hist_list[12];
    } hist;

};

#define ID_NEXT(n) ((n)->data.N_id->id_children.id_children_st.next)
#define ID_ORIG(n) ((n)->data.N_id->orig)
#define ID_LWR(n) ((n)->data.N_id->lwr)
#define ID_UPR(n) ((n)->data.N_id->upr)
#define ID_ROW(n) ((n)->data.N_id->row)
#define ID_COL_BEGIN(n) ((n)->data.N_id->col_begin)
#define ID_COL_END(n) ((n)->data.N_id->col_end)
#define HIST_ID(n) (((ccn_hist*)n)->data.NH_id)
#define IENUM_VALS(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.vals)
#define IENUM_NAME(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.name)
#define IENUM_IPREFIX(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.iprefix)
#define IENUM_NEXT(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.next)
#define IENUM_IINFO(n) ((n)->data.N_ienum->iinfo)
#define HIST_IENUM(n) (((ccn_hist*)n)->data.NH_ienum)
#define ATTRIBUTE_NAME(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.name)
#define ATTRIBUTE_TYPE_REFERENCE(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.type_reference)
#define ATTRIBUTE_LIFETIMES(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.lifetimes)
#define ATTRIBUTE_NEXT(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.next)
#define ATTRIBUTE_TYPE(n) ((n)->data.N_attribute->type)
#define ATTRIBUTE_IN_CONSTRUCTOR(n) ((n)->data.N_attribute->in_constructor)
#define HIST_ATTRIBUTE(n) (((ccn_hist*)n)->data.NH_attribute)
#define ITRAVDATA_NAME(n) ((n)->data.N_itravdata->itravdata_children.itravdata_children_st.name)
#define ITRAVDATA_TYPE_REFERENCE(n) ((n)->data.N_itravdata->itravdata_children.itravdata_children_st.type_reference)
#define ITRAVDATA_NEXT(n) ((n)->data.N_itravdata->itravdata_children.itravdata_children_st.next)
#define ITRAVDATA_TYPE(n) ((n)->data.N_itravdata->type)
#define ITRAVDATA_INCLUDE_FILE(n) ((n)->data.N_itravdata->include_file)
#define HIST_ITRAVDATA(n) (((ccn_hist*)n)->data.NH_itravdata)
#define SETOPERATION_LEFT(n) ((n)->data.N_setoperation->setoperation_children.setoperation_children_st.left)
#define SETOPERATION_RIGHT(n) ((n)->data.N_setoperation->setoperation_children.setoperation_children_st.right)
#define SETOPERATION_TYPE(n) ((n)->data.N_setoperation->type)
#define HIST_SETOPERATION(n) (((ccn_hist*)n)->data.NH_setoperation)
#define SETLITERAL_REFERENCE(n) ((n)->data.N_setliteral->setliteral_children.setliteral_children_st.reference)
#define SETLITERAL_LEFT(n) ((n)->data.N_setliteral->setliteral_children.setliteral_children_st.left)
#define SETLITERAL_RIGHT(n) ((n)->data.N_setliteral->setliteral_children.setliteral_children_st.right)
#define HIST_SETLITERAL(n) (((ccn_hist*)n)->data.NH_setliteral)
#define SETREFERENCE_REFERENCE(n) ((n)->data.N_setreference->setreference_children.setreference_children_st.reference)
#define HIST_SETREFERENCE(n) (((ccn_hist*)n)->data.NH_setreference)
#define STE_NEXT(n) ((n)->data.N_ste->ste_children.ste_children_st.next)
#define STE_KEY(n) ((n)->data.N_ste->key)
#define STE_VALUE(n) ((n)->data.N_ste->value)
#define HIST_STE(n) (((ccn_hist*)n)->data.NH_ste)
#define CHILD_NAME(n) ((n)->data.N_child->child_children.child_children_st.name)
#define CHILD_LIFETIMES(n) ((n)->data.N_child->child_children.child_children_st.lifetimes)
#define CHILD_NEXT(n) ((n)->data.N_child->child_children.child_children_st.next)
#define CHILD_TYPE_REFERENCE(n) ((n)->data.N_child->child_children.child_children_st.type_reference)
#define CHILD_TYPE(n) ((n)->data.N_child->type)
#define CHILD_IN_CONSTRUCTOR(n) ((n)->data.N_child->in_constructor)
#define CHILD_IS_MANDATORY(n) ((n)->data.N_child->is_mandatory)
#define HIST_CHILD(n) (((ccn_hist*)n)->data.NH_child)
#define LIFETIME_RANGE_TARGET(n) ((n)->data.N_lifetime_range->lifetime_range_children.lifetime_range_children_st.target)
#define LIFETIME_RANGE_INCLUSIVE(n) ((n)->data.N_lifetime_range->inclusive)
#define LIFETIME_RANGE_ACTION_ID(n) ((n)->data.N_lifetime_range->action_id)
#define LIFETIME_RANGE_NEXT_ACTION_ID(n) ((n)->data.N_lifetime_range->next_action_id)
#define HIST_LIFETIME_RANGE(n) (((ccn_hist*)n)->data.NH_lifetime_range)
#define ILIFETIME_BEGIN(n) ((n)->data.N_ilifetime->ilifetime_children.ilifetime_children_st.begin)
#define ILIFETIME_END(n) ((n)->data.N_ilifetime->ilifetime_children.ilifetime_children_st.end)
#define ILIFETIME_NEXT(n) ((n)->data.N_ilifetime->ilifetime_children.ilifetime_children_st.next)
#define ILIFETIME_TYPE(n) ((n)->data.N_ilifetime->type)
#define HIST_ILIFETIME(n) (((ccn_hist*)n)->data.NH_ilifetime)
#define INODESET_NAME(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.name)
#define INODESET_EXPR(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.expr)
#define INODESET_UNPACKED(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.unpacked)
#define INODESET_NEXT(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.next)
#define INODESET_IINFO(n) ((n)->data.N_inodeset->iinfo)
#define HIST_INODESET(n) (((ccn_hist*)n)->data.NH_inodeset)
#define INODE_NAME(n) ((n)->data.N_inode->inode_children.inode_children_st.name)
#define INODE_NEXT(n) ((n)->data.N_inode->inode_children.inode_children_st.next)
#define INODE_ICHILDREN(n) ((n)->data.N_inode->inode_children.inode_children_st.ichildren)
#define INODE_IATTRIBUTES(n) ((n)->data.N_inode->inode_children.inode_children_st.iattributes)
#define INODE_LIFETIMES(n) ((n)->data.N_inode->inode_children.inode_children_st.lifetimes)
#define INODE_IIFNO(n) ((n)->data.N_inode->iifno)
#define INODE_IS_ROOT(n) ((n)->data.N_inode->is_root)
#define INODE_INDEX(n) ((n)->data.N_inode->index)
#define HIST_INODE(n) (((ccn_hist*)n)->data.NH_inode)
#define IPASS_NAME(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.name)
#define IPASS_IPREFIX(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.iprefix)
#define IPASS_TARGET_FUNC(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.target_func)
#define IPASS_NEXT(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.next)
#define IPASS_IIFNO(n) ((n)->data.N_ipass->iifno)
#define HIST_IPASS(n) (((ccn_hist*)n)->data.NH_ipass)
#define ITRAVERSAL_NAME(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.name)
#define ITRAVERSAL_IPREFIX(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.iprefix)
#define ITRAVERSAL_INODES(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.inodes)
#define ITRAVERSAL_DATA(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.data)
#define ITRAVERSAL_NEXT(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.next)
#define ITRAVERSAL_INDEX(n) ((n)->data.N_itraversal->index)
#define ITRAVERSAL_IINFO(n) ((n)->data.N_itraversal->iinfo)
#define HIST_ITRAVERSAL(n) (((ccn_hist*)n)->data.NH_itraversal)
#define IPHASE_NAME(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.name)
#define IPHASE_IPREFIX(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.iprefix)
#define IPHASE_GATE_FUNC(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.gate_func)
#define IPHASE_IACTIONS(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.iactions)
#define IPHASE_NEXT(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.next)
#define IPHASE_IS_START(n) ((n)->data.N_iphase->is_start)
#define IPHASE_IS_CYCLE(n) ((n)->data.N_iphase->is_cycle)
#define IPHASE_IINFO(n) ((n)->data.N_iphase->iinfo)
#define HIST_IPHASE(n) (((ccn_hist*)n)->data.NH_iphase)
#define IACTIONS_REFERENCE(n) ((n)->data.N_iactions->iactions_children.iactions_children_st.reference)
#define IACTIONS_NEXT(n) ((n)->data.N_iactions->iactions_children.iactions_children_st.next)
#define IACTIONS_ACTION_ID(n) ((n)->data.N_iactions->action_id)
#define HIST_IACTIONS(n) (((ccn_hist*)n)->data.NH_iactions)
#define AST_IPHASES(n) ((n)->data.N_ast->ast_children.ast_children_st.iphases)
#define AST_ITRAVERSALS(n) ((n)->data.N_ast->ast_children.ast_children_st.itraversals)
#define AST_IPASSES(n) ((n)->data.N_ast->ast_children.ast_children_st.ipasses)
#define AST_INODES(n) ((n)->data.N_ast->ast_children.ast_children_st.inodes)
#define AST_INODESETS(n) ((n)->data.N_ast->ast_children.ast_children_st.inodesets)
#define AST_ENUMS(n) ((n)->data.N_ast->ast_children.ast_children_st.enums)
#define AST_STABLE(n) ((n)->data.N_ast->ast_children.ast_children_st.stable)
#define AST_NUM_TRAVERSALS(n) ((n)->data.N_ast->num_traversals)
#define AST_NUM_NODES(n) ((n)->data.N_ast->num_nodes)
#define AST_ROOT_NODE(n) ((n)->data.N_ast->root_node)
#define AST_START_PHASE(n) ((n)->data.N_ast->start_phase)
#define AST_USES_UNSAFE(n) ((n)->data.N_ast->uses_unsafe)
#define HIST_AST(n) (((ccn_hist*)n)->data.NH_ast)
node_st *ASTid(char * orig, char * lwr, char * Upr);
node_st *ASTienum(node_st *vals, node_st *name, node_st *iprefix, char * iinfo);
node_st *ASTattribute();
node_st *ASTitravdata(node_st *name);
node_st *ASTsetoperation(node_st *left, node_st *right, enum setoperation_type type);
node_st *ASTsetliteral(node_st *reference);
node_st *ASTsetreference();
node_st *ASTste();
node_st *ASTchild(node_st *name);
node_st *ASTlifetime_range();
node_st *ASTilifetime();
node_st *ASTinodeset();
node_st *ASTinode(node_st *name, char * iifno);
node_st *ASTipass(node_st *name, char * iifno);
node_st *ASTitraversal(node_st *name);
node_st *ASTiphase(node_st *name, int is_start);
node_st *ASTiactions();
node_st *ASTast();
union HIST_DATA {
    struct NODE_HIST_AST *NH_ast;
    struct NODE_HIST_IACTIONS *NH_iactions;
    struct NODE_HIST_IPHASE *NH_iphase;
    struct NODE_HIST_ITRAVERSAL *NH_itraversal;
    struct NODE_HIST_IPASS *NH_ipass;
    struct NODE_HIST_INODE *NH_inode;
    struct NODE_HIST_INODESET *NH_inodeset;
    struct NODE_HIST_ILIFETIME *NH_ilifetime;
    struct NODE_HIST_LIFETIME_RANGE *NH_lifetime_range;
    struct NODE_HIST_CHILD *NH_child;
    struct NODE_HIST_STE *NH_ste;
    struct NODE_HIST_SETREFERENCE *NH_setreference;
    struct NODE_HIST_SETLITERAL *NH_setliteral;
    struct NODE_HIST_SETOPERATION *NH_setoperation;
    struct NODE_HIST_ITRAVDATA *NH_itravdata;
    struct NODE_HIST_ATTRIBUTE *NH_attribute;
    struct NODE_HIST_IENUM *NH_ienum;
    struct NODE_HIST_ID *NH_id;
};

union NODE_DATA {
    struct NODE_DATA_AST *N_ast;
    struct NODE_DATA_IACTIONS *N_iactions;
    struct NODE_DATA_IPHASE *N_iphase;
    struct NODE_DATA_ITRAVERSAL *N_itraversal;
    struct NODE_DATA_IPASS *N_ipass;
    struct NODE_DATA_INODE *N_inode;
    struct NODE_DATA_INODESET *N_inodeset;
    struct NODE_DATA_ILIFETIME *N_ilifetime;
    struct NODE_DATA_LIFETIME_RANGE *N_lifetime_range;
    struct NODE_DATA_CHILD *N_child;
    struct NODE_DATA_STE *N_ste;
    struct NODE_DATA_SETREFERENCE *N_setreference;
    struct NODE_DATA_SETLITERAL *N_setliteral;
    struct NODE_DATA_SETOPERATION *N_setoperation;
    struct NODE_DATA_ITRAVDATA *N_itravdata;
    struct NODE_DATA_ATTRIBUTE *N_attribute;
    struct NODE_DATA_IENUM *N_ienum;
    struct NODE_DATA_ID *N_id;
};

#define HIST_TRAVERSAL(n) ((n)->trav)
#define HIST_NEXT(n) ((n)->next)
typedef struct ccn_hist {
    union HIST_DATA data;
    enum ccn_traversal_type trav;
    struct ccn_hist *next;
} ccn_hist;

#define NODE_TYPE(n) ((n)->nodetype)
#define NODE_CHILDREN(n) ((n)->children)
#define NODE_NUMCHILDREN(n) ((n)->num_children)
#define NODE_FILENAME(n) ((n)->filename)
#define NODE_BLINE(n) ((n)->begin_line)
#define NODE_ELINE(n) ((n)->end_line)
#define NODE_BCOL(n) ((n)->begin_col)
#define NODE_ECOL(n) ((n)->end_col)
#define NODE_ID(n) ((n)->id)
#define NODE_HIST(n) ((n)->hist)
#define NODE_PARENT(n) ((n)->parent)
typedef struct ccn_node {
    enum ccn_nodetype nodetype;
    union NODE_DATA data;
    ccn_hist *hist;
    struct ccn_node **children;
    char *filename;
    long int num_children;
    uint32_t begin_line;
    uint32_t end_line;
    uint32_t begin_col;
    uint32_t end_col;
    // Used by debugger
    int id;
    struct ccn_node *parent;
    bool trashed;
} ccn_node;

