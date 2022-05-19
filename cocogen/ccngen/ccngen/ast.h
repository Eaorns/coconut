#pragma once
#pragma once
#include "ccn/ccn_types.h"
#include "ccngen/enum.h"
typedef struct ccn_node node_st;
enum H_DATTYPES {
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

struct hist_item_user {
    void *val;
    void *rip;
    node_st *prev_parent;
    struct hist_item_user *next;
};

struct hist_item_link {
    node_st *val;
    void *rip;
    struct hist_item_link *next;
};

struct hist_item_link_or_enum {
    int val;
    void *rip;
    struct hist_item_link_or_enum *next;
};

struct hist_item_int {
    int val;
    void *rip;
    struct hist_item_int *next;
};

struct hist_item_string {
    char * val;
    void *rip;
    struct hist_item_string *next;
};

struct hist_item_bool {
    bool val;
    void *rip;
    struct hist_item_bool *next;
};

struct hist_item_int8 {
    int8_t val;
    void *rip;
    struct hist_item_int8 *next;
};

struct hist_item_int16 {
    int16_t val;
    void *rip;
    struct hist_item_int16 *next;
};

struct hist_item_int32 {
    int32_t val;
    void *rip;
    struct hist_item_int32 *next;
};

struct hist_item_int64 {
    int64_t val;
    void *rip;
    struct hist_item_int64 *next;
};

struct hist_item_float {
    float val;
    void *rip;
    struct hist_item_float *next;
};

struct hist_item_double {
    double val;
    void *rip;
    struct hist_item_double *next;
};

struct hist_item_uint {
    unsigned int val;
    void *rip;
    struct hist_item_uint *next;
};

struct hist_item_uint8 {
    uint8_t val;
    void *rip;
    struct hist_item_uint8 *next;
};

struct hist_item_uint16 {
    uint16_t val;
    void *rip;
    struct hist_item_uint16 *next;
};

struct hist_item_uint32 {
    uint32_t val;
    void *rip;
    struct hist_item_uint32 *next;
};

struct hist_item_uint64 {
    uint64_t val;
    void *rip;
    struct hist_item_uint64 *next;
};

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
    
    struct NODE_HIST_ID *hist;
};

struct NODE_HIST_ID {
    union HIST_ID {
        struct HIST_ITEMS_ID {
            struct hist_item_link *next;
            struct hist_item_string *orig;
            struct hist_item_string *lwr;
            struct hist_item_string *upr;
            struct hist_item_int *row;
            struct hist_item_int *col_begin;
            struct hist_item_int *col_end;
        } hist_items;

        void *hist_list[7];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_ID *next;
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
    
    struct NODE_HIST_IENUM *hist;
};

struct NODE_HIST_IENUM {
    union HIST_IENUM {
        struct HIST_ITEMS_IENUM {
            struct hist_item_link *vals;
            struct hist_item_link *name;
            struct hist_item_link *iprefix;
            struct hist_item_link *next;
            struct hist_item_string *iinfo;
        } hist_items;

        void *hist_list[5];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_IENUM *next;
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
    
    struct NODE_HIST_ATTRIBUTE *hist;
};

struct NODE_HIST_ATTRIBUTE {
    union HIST_ATTRIBUTE {
        struct HIST_ITEMS_ATTRIBUTE {
            struct hist_item_link *name;
            struct hist_item_link *type_reference;
            struct hist_item_link *lifetimes;
            struct hist_item_link *next;
            struct hist_item_link_or_enum *type;
            struct hist_item_int *in_constructor;
        } hist_items;

        void *hist_list[6];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_ATTRIBUTE *next;
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
    
    struct NODE_HIST_ITRAVDATA *hist;
};

struct NODE_HIST_ITRAVDATA {
    union HIST_ITRAVDATA {
        struct HIST_ITEMS_ITRAVDATA {
            struct hist_item_link *name;
            struct hist_item_link *type_reference;
            struct hist_item_link *next;
            struct hist_item_link_or_enum *type;
            struct hist_item_string *include_file;
        } hist_items;

        void *hist_list[5];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_ITRAVDATA *next;
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
    
    struct NODE_HIST_SETOPERATION *hist;
};

struct NODE_HIST_SETOPERATION {
    union HIST_SETOPERATION {
        struct HIST_ITEMS_SETOPERATION {
            struct hist_item_link *left;
            struct hist_item_link *right;
            struct hist_item_link_or_enum *type;
        } hist_items;

        void *hist_list[3];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_SETOPERATION *next;
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

    
    struct NODE_HIST_SETLITERAL *hist;
};

struct NODE_HIST_SETLITERAL {
    union HIST_SETLITERAL {
        struct HIST_ITEMS_SETLITERAL {
            struct hist_item_link *reference;
            struct hist_item_link *left;
            struct hist_item_link *right;
        } hist_items;

        void *hist_list[3];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_SETLITERAL *next;
};

struct NODE_DATA_SETREFERENCE {
    union NODE_CHILDREN_SETREFERENCE {
        struct NODE_CHILDREN_SETREFERENCE_STRUCT {
            node_st *reference;
        } setreference_children_st;

        node_st *setreference_children_at[1];
    } setreference_children;

    
    struct NODE_HIST_SETREFERENCE *hist;
};

struct NODE_HIST_SETREFERENCE {
    union HIST_SETREFERENCE {
        struct HIST_ITEMS_SETREFERENCE {
            struct hist_item_link *reference;
        } hist_items;

        void *hist_list[1];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_SETREFERENCE *next;
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
    
    struct NODE_HIST_STE *hist;
};

struct NODE_HIST_STE {
    union HIST_STE {
        struct HIST_ITEMS_STE {
            struct hist_item_link *next;
            struct hist_item_link *key;
            struct hist_item_link *value;
        } hist_items;

        void *hist_list[3];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_STE *next;
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
    
    struct NODE_HIST_CHILD *hist;
};

struct NODE_HIST_CHILD {
    union HIST_CHILD {
        struct HIST_ITEMS_CHILD {
            struct hist_item_link *name;
            struct hist_item_link *lifetimes;
            struct hist_item_link *next;
            struct hist_item_link *type_reference;
            struct hist_item_link_or_enum *type;
            struct hist_item_int *in_constructor;
            struct hist_item_int *is_mandatory;
        } hist_items;

        void *hist_list[7];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_CHILD *next;
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
    
    struct NODE_HIST_LIFETIME_RANGE *hist;
};

struct NODE_HIST_LIFETIME_RANGE {
    union HIST_LIFETIME_RANGE {
        struct HIST_ITEMS_LIFETIME_RANGE {
            struct hist_item_link *target;
            struct hist_item_bool *inclusive;
            struct hist_item_int *action_id;
            struct hist_item_int *next_action_id;
        } hist_items;

        void *hist_list[4];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_LIFETIME_RANGE *next;
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
    
    struct NODE_HIST_ILIFETIME *hist;
};

struct NODE_HIST_ILIFETIME {
    union HIST_ILIFETIME {
        struct HIST_ITEMS_ILIFETIME {
            struct hist_item_link *begin;
            struct hist_item_link *end;
            struct hist_item_link *next;
            struct hist_item_link_or_enum *type;
        } hist_items;

        void *hist_list[4];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_ILIFETIME *next;
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
    
    struct NODE_HIST_INODESET *hist;
};

struct NODE_HIST_INODESET {
    union HIST_INODESET {
        struct HIST_ITEMS_INODESET {
            struct hist_item_link *name;
            struct hist_item_link *expr;
            struct hist_item_link *unpacked;
            struct hist_item_link *next;
            struct hist_item_string *iinfo;
        } hist_items;

        void *hist_list[5];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_INODESET *next;
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
    
    struct NODE_HIST_INODE *hist;
};

struct NODE_HIST_INODE {
    union HIST_INODE {
        struct HIST_ITEMS_INODE {
            struct hist_item_link *name;
            struct hist_item_link *next;
            struct hist_item_link *ichildren;
            struct hist_item_link *iattributes;
            struct hist_item_link *lifetimes;
            struct hist_item_string *iifno;
            struct hist_item_int *is_root;
            struct hist_item_int *index;
        } hist_items;

        void *hist_list[8];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_INODE *next;
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
    
    struct NODE_HIST_IPASS *hist;
};

struct NODE_HIST_IPASS {
    union HIST_IPASS {
        struct HIST_ITEMS_IPASS {
            struct hist_item_link *name;
            struct hist_item_link *iprefix;
            struct hist_item_link *target_func;
            struct hist_item_link *next;
            struct hist_item_string *iifno;
        } hist_items;

        void *hist_list[5];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_IPASS *next;
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
    
    struct NODE_HIST_ITRAVERSAL *hist;
};

struct NODE_HIST_ITRAVERSAL {
    union HIST_ITRAVERSAL {
        struct HIST_ITEMS_ITRAVERSAL {
            struct hist_item_link *name;
            struct hist_item_link *iprefix;
            struct hist_item_link *inodes;
            struct hist_item_link *data;
            struct hist_item_link *next;
            struct hist_item_int *index;
            struct hist_item_string *iinfo;
        } hist_items;

        void *hist_list[7];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_ITRAVERSAL *next;
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
    
    struct NODE_HIST_IPHASE *hist;
};

struct NODE_HIST_IPHASE {
    union HIST_IPHASE {
        struct HIST_ITEMS_IPHASE {
            struct hist_item_link *name;
            struct hist_item_link *iprefix;
            struct hist_item_link *gate_func;
            struct hist_item_link *iactions;
            struct hist_item_link *next;
            struct hist_item_int *is_start;
            struct hist_item_int *is_cycle;
            struct hist_item_string *iinfo;
        } hist_items;

        void *hist_list[8];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_IPHASE *next;
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
    
    struct NODE_HIST_IACTIONS *hist;
};

struct NODE_HIST_IACTIONS {
    union HIST_IACTIONS {
        struct HIST_ITEMS_IACTIONS {
            struct hist_item_link *reference;
            struct hist_item_link *next;
            struct hist_item_int *action_id;
        } hist_items;

        void *hist_list[3];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_IACTIONS *next;
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
    
    struct NODE_HIST_AST *hist;
};

struct NODE_HIST_AST {
    union HIST_AST {
        struct HIST_ITEMS_AST {
            struct hist_item_link *iphases;
            struct hist_item_link *itraversals;
            struct hist_item_link *ipasses;
            struct hist_item_link *inodes;
            struct hist_item_link *inodesets;
            struct hist_item_link *enums;
            struct hist_item_link *stable;
            struct hist_item_int *num_traversals;
            struct hist_item_int *num_nodes;
            struct hist_item_link *root_node;
            struct hist_item_link *start_phase;
            struct hist_item_bool *uses_unsafe;
        } hist_items;

        void *hist_list[12];
    } hist;

    enum ccn_traversal_type trav;
    struct NODE_HIST_AST *next;
};

#define ID_NEXT(n) ((n)->data.N_id->id_children.id_children_st.next)
#define ID_ORIG(n) ((n)->data.N_id->orig)
#define ID_LWR(n) ((n)->data.N_id->lwr)
#define ID_UPR(n) ((n)->data.N_id->upr)
#define ID_ROW(n) ((n)->data.N_id->row)
#define ID_COL_BEGIN(n) ((n)->data.N_id->col_begin)
#define ID_COL_END(n) ((n)->data.N_id->col_end)
#define NODE_HIST_ID(n) ((n)->data.N_id->hist)
#define IENUM_VALS(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.vals)
#define IENUM_NAME(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.name)
#define IENUM_IPREFIX(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.iprefix)
#define IENUM_NEXT(n) ((n)->data.N_ienum->ienum_children.ienum_children_st.next)
#define IENUM_IINFO(n) ((n)->data.N_ienum->iinfo)
#define NODE_HIST_IENUM(n) ((n)->data.N_ienum->hist)
#define ATTRIBUTE_NAME(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.name)
#define ATTRIBUTE_TYPE_REFERENCE(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.type_reference)
#define ATTRIBUTE_LIFETIMES(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.lifetimes)
#define ATTRIBUTE_NEXT(n) ((n)->data.N_attribute->attribute_children.attribute_children_st.next)
#define ATTRIBUTE_TYPE(n) ((n)->data.N_attribute->type)
#define ATTRIBUTE_IN_CONSTRUCTOR(n) ((n)->data.N_attribute->in_constructor)
#define NODE_HIST_ATTRIBUTE(n) ((n)->data.N_attribute->hist)
#define ITRAVDATA_NAME(n) ((n)->data.N_itravdata->itravdata_children.itravdata_children_st.name)
#define ITRAVDATA_TYPE_REFERENCE(n) ((n)->data.N_itravdata->itravdata_children.itravdata_children_st.type_reference)
#define ITRAVDATA_NEXT(n) ((n)->data.N_itravdata->itravdata_children.itravdata_children_st.next)
#define ITRAVDATA_TYPE(n) ((n)->data.N_itravdata->type)
#define ITRAVDATA_INCLUDE_FILE(n) ((n)->data.N_itravdata->include_file)
#define NODE_HIST_ITRAVDATA(n) ((n)->data.N_itravdata->hist)
#define SETOPERATION_LEFT(n) ((n)->data.N_setoperation->setoperation_children.setoperation_children_st.left)
#define SETOPERATION_RIGHT(n) ((n)->data.N_setoperation->setoperation_children.setoperation_children_st.right)
#define SETOPERATION_TYPE(n) ((n)->data.N_setoperation->type)
#define NODE_HIST_SETOPERATION(n) ((n)->data.N_setoperation->hist)
#define SETLITERAL_REFERENCE(n) ((n)->data.N_setliteral->setliteral_children.setliteral_children_st.reference)
#define SETLITERAL_LEFT(n) ((n)->data.N_setliteral->setliteral_children.setliteral_children_st.left)
#define SETLITERAL_RIGHT(n) ((n)->data.N_setliteral->setliteral_children.setliteral_children_st.right)
#define NODE_HIST_SETLITERAL(n) ((n)->data.N_setliteral->hist)
#define SETREFERENCE_REFERENCE(n) ((n)->data.N_setreference->setreference_children.setreference_children_st.reference)
#define NODE_HIST_SETREFERENCE(n) ((n)->data.N_setreference->hist)
#define STE_NEXT(n) ((n)->data.N_ste->ste_children.ste_children_st.next)
#define STE_KEY(n) ((n)->data.N_ste->key)
#define STE_VALUE(n) ((n)->data.N_ste->value)
#define NODE_HIST_STE(n) ((n)->data.N_ste->hist)
#define CHILD_NAME(n) ((n)->data.N_child->child_children.child_children_st.name)
#define CHILD_LIFETIMES(n) ((n)->data.N_child->child_children.child_children_st.lifetimes)
#define CHILD_NEXT(n) ((n)->data.N_child->child_children.child_children_st.next)
#define CHILD_TYPE_REFERENCE(n) ((n)->data.N_child->child_children.child_children_st.type_reference)
#define CHILD_TYPE(n) ((n)->data.N_child->type)
#define CHILD_IN_CONSTRUCTOR(n) ((n)->data.N_child->in_constructor)
#define CHILD_IS_MANDATORY(n) ((n)->data.N_child->is_mandatory)
#define NODE_HIST_CHILD(n) ((n)->data.N_child->hist)
#define LIFETIME_RANGE_TARGET(n) ((n)->data.N_lifetime_range->lifetime_range_children.lifetime_range_children_st.target)
#define LIFETIME_RANGE_INCLUSIVE(n) ((n)->data.N_lifetime_range->inclusive)
#define LIFETIME_RANGE_ACTION_ID(n) ((n)->data.N_lifetime_range->action_id)
#define LIFETIME_RANGE_NEXT_ACTION_ID(n) ((n)->data.N_lifetime_range->next_action_id)
#define NODE_HIST_LIFETIME_RANGE(n) ((n)->data.N_lifetime_range->hist)
#define ILIFETIME_BEGIN(n) ((n)->data.N_ilifetime->ilifetime_children.ilifetime_children_st.begin)
#define ILIFETIME_END(n) ((n)->data.N_ilifetime->ilifetime_children.ilifetime_children_st.end)
#define ILIFETIME_NEXT(n) ((n)->data.N_ilifetime->ilifetime_children.ilifetime_children_st.next)
#define ILIFETIME_TYPE(n) ((n)->data.N_ilifetime->type)
#define NODE_HIST_ILIFETIME(n) ((n)->data.N_ilifetime->hist)
#define INODESET_NAME(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.name)
#define INODESET_EXPR(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.expr)
#define INODESET_UNPACKED(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.unpacked)
#define INODESET_NEXT(n) ((n)->data.N_inodeset->inodeset_children.inodeset_children_st.next)
#define INODESET_IINFO(n) ((n)->data.N_inodeset->iinfo)
#define NODE_HIST_INODESET(n) ((n)->data.N_inodeset->hist)
#define INODE_NAME(n) ((n)->data.N_inode->inode_children.inode_children_st.name)
#define INODE_NEXT(n) ((n)->data.N_inode->inode_children.inode_children_st.next)
#define INODE_ICHILDREN(n) ((n)->data.N_inode->inode_children.inode_children_st.ichildren)
#define INODE_IATTRIBUTES(n) ((n)->data.N_inode->inode_children.inode_children_st.iattributes)
#define INODE_LIFETIMES(n) ((n)->data.N_inode->inode_children.inode_children_st.lifetimes)
#define INODE_IIFNO(n) ((n)->data.N_inode->iifno)
#define INODE_IS_ROOT(n) ((n)->data.N_inode->is_root)
#define INODE_INDEX(n) ((n)->data.N_inode->index)
#define NODE_HIST_INODE(n) ((n)->data.N_inode->hist)
#define IPASS_NAME(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.name)
#define IPASS_IPREFIX(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.iprefix)
#define IPASS_TARGET_FUNC(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.target_func)
#define IPASS_NEXT(n) ((n)->data.N_ipass->ipass_children.ipass_children_st.next)
#define IPASS_IIFNO(n) ((n)->data.N_ipass->iifno)
#define NODE_HIST_IPASS(n) ((n)->data.N_ipass->hist)
#define ITRAVERSAL_NAME(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.name)
#define ITRAVERSAL_IPREFIX(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.iprefix)
#define ITRAVERSAL_INODES(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.inodes)
#define ITRAVERSAL_DATA(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.data)
#define ITRAVERSAL_NEXT(n) ((n)->data.N_itraversal->itraversal_children.itraversal_children_st.next)
#define ITRAVERSAL_INDEX(n) ((n)->data.N_itraversal->index)
#define ITRAVERSAL_IINFO(n) ((n)->data.N_itraversal->iinfo)
#define NODE_HIST_ITRAVERSAL(n) ((n)->data.N_itraversal->hist)
#define IPHASE_NAME(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.name)
#define IPHASE_IPREFIX(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.iprefix)
#define IPHASE_GATE_FUNC(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.gate_func)
#define IPHASE_IACTIONS(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.iactions)
#define IPHASE_NEXT(n) ((n)->data.N_iphase->iphase_children.iphase_children_st.next)
#define IPHASE_IS_START(n) ((n)->data.N_iphase->is_start)
#define IPHASE_IS_CYCLE(n) ((n)->data.N_iphase->is_cycle)
#define IPHASE_IINFO(n) ((n)->data.N_iphase->iinfo)
#define NODE_HIST_IPHASE(n) ((n)->data.N_iphase->hist)
#define IACTIONS_REFERENCE(n) ((n)->data.N_iactions->iactions_children.iactions_children_st.reference)
#define IACTIONS_NEXT(n) ((n)->data.N_iactions->iactions_children.iactions_children_st.next)
#define IACTIONS_ACTION_ID(n) ((n)->data.N_iactions->action_id)
#define NODE_HIST_IACTIONS(n) ((n)->data.N_iactions->hist)
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
#define NODE_HIST_AST(n) ((n)->data.N_ast->hist)
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

#define NODE_TYPE(n) ((n)->nodetype)
#define NODE_CHILDREN(n) ((n)->children)
#define NODE_NUMCHILDREN(n) ((n)->num_children)
#define NODE_FILENAME(n) ((n)->filename)
#define NODE_BLINE(n) ((n)->begin_line)
#define NODE_ELINE(n) ((n)->end_line)
#define NODE_BCOL(n) ((n)->begin_col)
#define NODE_ECOL(n) ((n)->end_col)
#define NODE_ID(n) ((n)->id)
#define NODE_PARENT(n) ((n)->parent)
typedef struct ccn_node {
    enum ccn_nodetype nodetype;
    union NODE_DATA data;
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
} ccn_node;

