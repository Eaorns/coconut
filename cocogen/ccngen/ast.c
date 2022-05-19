#define _GNU_SOURCE  // Required for REG_RIP
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <ucontext.h>
#include "ccngen/ast.h"
#include "palm/memory.h"
#include "palm/watchpoint.h"
#include "palm/watchpointalloc.h"
int node_id_ctr = 0;
node_st *NewNode() {
    node_st *node = MEMmalloc(sizeof(node_st));
    NODE_TYPE(node) = NT_NULL;
    NODE_CHILDREN(node) = NULL;
    NODE_FILENAME(node) = NULL;
    NODE_NUMCHILDREN(node) = 0;
    NODE_BLINE(node) = 0;
    NODE_ELINE(node) = 0;
    NODE_BCOL(node) = 0;
    NODE_ECOL(node) = 0;
    NODE_ID(node) = node_id_ctr++;
    NODE_PARENT(node) = NULL;
    return node;
}

struct wp_handler_data {
    size_t index;
    size_t offset;
    enum H_DATTYPES datatype;
    bool is_child;
};

struct wp_handler_data ID_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_ID, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_ID, hist) - offsetof(struct NODE_DATA_ID, orig), .datatype = HDT_string, .is_child = false }, { .index = 2, .offset = offsetof(struct NODE_DATA_ID, hist) - offsetof(struct NODE_DATA_ID, lwr), .datatype = HDT_string, .is_child = false }, { .index = 3, .offset = offsetof(struct NODE_DATA_ID, hist) - offsetof(struct NODE_DATA_ID, upr), .datatype = HDT_string, .is_child = false }, { .index = 4, .offset = offsetof(struct NODE_DATA_ID, hist) - offsetof(struct NODE_DATA_ID, row), .datatype = HDT_int, .is_child = false }, { .index = 5, .offset = offsetof(struct NODE_DATA_ID, hist) - offsetof(struct NODE_DATA_ID, col_begin), .datatype = HDT_int, .is_child = false }, { .index = 6, .offset = offsetof(struct NODE_DATA_ID, hist) - offsetof(struct NODE_DATA_ID, col_end), .datatype = HDT_int, .is_child = false }, };
void wphandler_id(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_ID *hist = (struct NODE_HIST_ID *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
            struct hist_item_link *s0 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s0->val = old_val;
            s0->rip = rip;
            s0->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s0;
            break;
        case 1:;
            struct hist_item_string *s1 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s1->val = (char*)old_val;
            s1->rip = rip;
            s1->next = hist->hist.hist_list[0];
            hist->hist.hist_list[1] = s1;
            break;
        case 2:;
            struct hist_item_string *s2 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s2->val = (char*)old_val;
            s2->rip = rip;
            s2->next = hist->hist.hist_list[0];
            hist->hist.hist_list[2] = s2;
            break;
        case 3:;
            struct hist_item_string *s3 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s3->val = (char*)old_val;
            s3->rip = rip;
            s3->next = hist->hist.hist_list[0];
            hist->hist.hist_list[3] = s3;
            break;
        case 4:;
            struct hist_item_int *s4 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s4->val = *(int*)(&old_val);
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
        case 5:;
            struct hist_item_int *s5 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s5->val = *(int*)(&old_val);
            s5->rip = rip;
            s5->next = hist->hist.hist_list[0];
            hist->hist.hist_list[5] = s5;
            break;
        case 6:;
            struct hist_item_int *s6 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s6->val = *(int*)(&old_val);
            s6->rip = rip;
            s6->next = hist->hist.hist_list[0];
            hist->hist.hist_list[6] = s6;
            break;
    }

}

node_st *ASTid(char * orig, char * lwr, char * Upr) {
    node_st *node = NewNode();
    node->data.N_id = MEMmalloc(sizeof(struct NODE_DATA_ID));
    NODE_TYPE(node) = NT_ID;
    node->data.N_id->hist = MEMmalloc(sizeof(struct NODE_HIST_ID));
    ID_NEXT(node) = NULL;
    ID_ORIG(node) = orig;
    ID_LWR(node) = lwr;
    ID_UPR(node) = Upr;
    ID_ROW(node) = 0;
    ID_COL_BEGIN(node) = 0;
    ID_COL_END(node) = 0;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_id->id_children.id_children_at;
    return node;}

struct wp_handler_data IENUM_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_IENUM, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_IENUM, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_IENUM, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_IENUM, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_IENUM, hist) - offsetof(struct NODE_DATA_IENUM, iinfo), .datatype = HDT_string, .is_child = false }, };
void wphandler_ienum(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_IENUM *hist = (struct NODE_HIST_IENUM *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
            struct hist_item_link *s3 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s3->val = old_val;
            s3->rip = rip;
            s3->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s3;
            break;
        case 4:;
            struct hist_item_string *s4 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s4->val = (char*)old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
    }

}

node_st *ASTienum(node_st *vals, node_st *name, node_st *iprefix, char * iinfo) {
    node_st *node = NewNode();
    node->data.N_ienum = MEMmalloc(sizeof(struct NODE_DATA_IENUM));
    NODE_TYPE(node) = NT_IENUM;
    node->data.N_ienum->hist = MEMmalloc(sizeof(struct NODE_HIST_IENUM));
    IENUM_VALS(node) = vals;
    IENUM_NAME(node) = name;
    IENUM_IPREFIX(node) = iprefix;
    IENUM_NEXT(node) = NULL;
    IENUM_IINFO(node) = iinfo;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_ienum->ienum_children.ienum_children_at;
    return node;}

struct wp_handler_data ATTRIBUTE_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_ATTRIBUTE, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_ATTRIBUTE, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_ATTRIBUTE, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_ATTRIBUTE, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_ATTRIBUTE, hist) - offsetof(struct NODE_DATA_ATTRIBUTE, type), .datatype = HDT_link_or_enum, .is_child = false }, { .index = 5, .offset = offsetof(struct NODE_DATA_ATTRIBUTE, hist) - offsetof(struct NODE_DATA_ATTRIBUTE, in_constructor), .datatype = HDT_int, .is_child = false }, };
void wphandler_attribute(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_ATTRIBUTE *hist = (struct NODE_HIST_ATTRIBUTE *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
            struct hist_item_link *s3 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s3->val = old_val;
            s3->rip = rip;
            s3->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s3;
            break;
        case 4:;
            struct hist_item_link_or_enum *s4 = (struct hist_item_link_or_enum *)malloc(sizeof(struct hist_item_link_or_enum));
            s4->val = *(int*)(&old_val);
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
        case 5:;
            struct hist_item_int *s5 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s5->val = *(int*)(&old_val);
            s5->rip = rip;
            s5->next = hist->hist.hist_list[0];
            hist->hist.hist_list[5] = s5;
            break;
    }

}

node_st *ASTattribute() {
    node_st *node = NewNode();
    node->data.N_attribute = MEMmalloc(sizeof(struct NODE_DATA_ATTRIBUTE));
    NODE_TYPE(node) = NT_ATTRIBUTE;
    node->data.N_attribute->hist = MEMmalloc(sizeof(struct NODE_HIST_ATTRIBUTE));
    ATTRIBUTE_NAME(node) = NULL;
    ATTRIBUTE_TYPE_REFERENCE(node) = NULL;
    ATTRIBUTE_LIFETIMES(node) = NULL;
    ATTRIBUTE_NEXT(node) = NULL;
    ATTRIBUTE_TYPE(node) = 0;
    ATTRIBUTE_IN_CONSTRUCTOR(node) = 0;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_attribute->attribute_children.attribute_children_at;
    return node;}

struct wp_handler_data ITRAVDATA_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_ITRAVDATA, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_ITRAVDATA, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_ITRAVDATA, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_ITRAVDATA, hist) - offsetof(struct NODE_DATA_ITRAVDATA, type), .datatype = HDT_link_or_enum, .is_child = false }, { .index = 4, .offset = offsetof(struct NODE_DATA_ITRAVDATA, hist) - offsetof(struct NODE_DATA_ITRAVDATA, include_file), .datatype = HDT_string, .is_child = false }, };
void wphandler_itravdata(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_ITRAVDATA *hist = (struct NODE_HIST_ITRAVDATA *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
            struct hist_item_link *s2 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s2->val = old_val;
            s2->rip = rip;
            s2->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s2;
            break;
        case 3:;
            struct hist_item_link_or_enum *s3 = (struct hist_item_link_or_enum *)malloc(sizeof(struct hist_item_link_or_enum));
            s3->val = *(int*)(&old_val);
            s3->rip = rip;
            s3->next = hist->hist.hist_list[0];
            hist->hist.hist_list[3] = s3;
            break;
        case 4:;
            struct hist_item_string *s4 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s4->val = (char*)old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
    }

}

node_st *ASTitravdata(node_st *name) {
    node_st *node = NewNode();
    node->data.N_itravdata = MEMmalloc(sizeof(struct NODE_DATA_ITRAVDATA));
    NODE_TYPE(node) = NT_ITRAVDATA;
    node->data.N_itravdata->hist = MEMmalloc(sizeof(struct NODE_HIST_ITRAVDATA));
    ITRAVDATA_NAME(node) = name;
    ITRAVDATA_TYPE_REFERENCE(node) = NULL;
    ITRAVDATA_NEXT(node) = NULL;
    ITRAVDATA_TYPE(node) = 0;
    ITRAVDATA_INCLUDE_FILE(node) = NULL;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_itravdata->itravdata_children.itravdata_children_at;
    return node;}

struct wp_handler_data SETOPERATION_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_SETOPERATION, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_SETOPERATION, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_SETOPERATION, hist) - offsetof(struct NODE_DATA_SETOPERATION, type), .datatype = HDT_link_or_enum, .is_child = false }, };
void wphandler_setoperation(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_SETOPERATION *hist = (struct NODE_HIST_SETOPERATION *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
            struct hist_item_link *s1 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s1->val = old_val;
            s1->rip = rip;
            s1->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s1;
            break;
        case 2:;
            struct hist_item_link_or_enum *s2 = (struct hist_item_link_or_enum *)malloc(sizeof(struct hist_item_link_or_enum));
            s2->val = *(int*)(&old_val);
            s2->rip = rip;
            s2->next = hist->hist.hist_list[0];
            hist->hist.hist_list[2] = s2;
            break;
    }

}

node_st *ASTsetoperation(node_st *left, node_st *right, enum setoperation_type type) {
    node_st *node = NewNode();
    node->data.N_setoperation = MEMmalloc(sizeof(struct NODE_DATA_SETOPERATION));
    NODE_TYPE(node) = NT_SETOPERATION;
    node->data.N_setoperation->hist = MEMmalloc(sizeof(struct NODE_HIST_SETOPERATION));
    SETOPERATION_LEFT(node) = left;
    SETOPERATION_RIGHT(node) = right;
    SETOPERATION_TYPE(node) = type;
    NODE_NUMCHILDREN(node) = 2;
    NODE_CHILDREN(node) = node->data.N_setoperation->setoperation_children.setoperation_children_at;
    return node;}

struct wp_handler_data SETLITERAL_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_SETLITERAL, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_SETLITERAL, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_SETLITERAL, hist) - 16, .datatype = HDT_link, .is_child = true }, };
void wphandler_setliteral(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_SETLITERAL *hist = (struct NODE_HIST_SETLITERAL *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
            struct hist_item_link *s2 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s2->val = old_val;
            s2->rip = rip;
            s2->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s2;
            break;
    }

}

node_st *ASTsetliteral(node_st *reference) {
    node_st *node = NewNode();
    node->data.N_setliteral = MEMmalloc(sizeof(struct NODE_DATA_SETLITERAL));
    NODE_TYPE(node) = NT_SETLITERAL;
    node->data.N_setliteral->hist = MEMmalloc(sizeof(struct NODE_HIST_SETLITERAL));
    SETLITERAL_REFERENCE(node) = reference;
    SETLITERAL_LEFT(node) = NULL;
    SETLITERAL_RIGHT(node) = NULL;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_setliteral->setliteral_children.setliteral_children_at;
    return node;}

struct wp_handler_data SETREFERENCE_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_SETREFERENCE, hist) - 0, .datatype = HDT_link, .is_child = true }, };
void wphandler_setreference(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_SETREFERENCE *hist = (struct NODE_HIST_SETREFERENCE *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
            struct hist_item_link *s0 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s0->val = old_val;
            s0->rip = rip;
            s0->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s0;
            break;
    }

}

node_st *ASTsetreference() {
    node_st *node = NewNode();
    node->data.N_setreference = MEMmalloc(sizeof(struct NODE_DATA_SETREFERENCE));
    NODE_TYPE(node) = NT_SETREFERENCE;
    node->data.N_setreference->hist = MEMmalloc(sizeof(struct NODE_HIST_SETREFERENCE));
    SETREFERENCE_REFERENCE(node) = NULL;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_setreference->setreference_children.setreference_children_at;
    return node;}

struct wp_handler_data STE_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_STE, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_STE, hist) - offsetof(struct NODE_DATA_STE, key), .datatype = HDT_link, .is_child = false }, { .index = 2, .offset = offsetof(struct NODE_DATA_STE, hist) - offsetof(struct NODE_DATA_STE, value), .datatype = HDT_link, .is_child = false }, };
void wphandler_ste(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_STE *hist = (struct NODE_HIST_STE *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
            struct hist_item_link *s0 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s0->val = old_val;
            s0->rip = rip;
            s0->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s0;
            break;
        case 1:;
            struct hist_item_link *s1 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s1->val = old_val;
            s1->rip = rip;
            s1->next = hist->hist.hist_list[0];
            hist->hist.hist_list[1] = s1;
            break;
        case 2:;
            struct hist_item_link *s2 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s2->val = old_val;
            s2->rip = rip;
            s2->next = hist->hist.hist_list[0];
            hist->hist.hist_list[2] = s2;
            break;
    }

}

node_st *ASTste() {
    node_st *node = NewNode();
    node->data.N_ste = MEMmalloc(sizeof(struct NODE_DATA_STE));
    NODE_TYPE(node) = NT_STE;
    node->data.N_ste->hist = MEMmalloc(sizeof(struct NODE_HIST_STE));
    STE_NEXT(node) = NULL;
    STE_KEY(node) = NULL;
    STE_VALUE(node) = NULL;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_ste->ste_children.ste_children_at;
    return node;}

struct wp_handler_data CHILD_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_CHILD, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_CHILD, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_CHILD, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_CHILD, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_CHILD, hist) - offsetof(struct NODE_DATA_CHILD, type), .datatype = HDT_link_or_enum, .is_child = false }, { .index = 5, .offset = offsetof(struct NODE_DATA_CHILD, hist) - offsetof(struct NODE_DATA_CHILD, in_constructor), .datatype = HDT_int, .is_child = false }, { .index = 6, .offset = offsetof(struct NODE_DATA_CHILD, hist) - offsetof(struct NODE_DATA_CHILD, is_mandatory), .datatype = HDT_int, .is_child = false }, };
void wphandler_child(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_CHILD *hist = (struct NODE_HIST_CHILD *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
            struct hist_item_link *s3 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s3->val = old_val;
            s3->rip = rip;
            s3->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s3;
            break;
        case 4:;
            struct hist_item_link_or_enum *s4 = (struct hist_item_link_or_enum *)malloc(sizeof(struct hist_item_link_or_enum));
            s4->val = *(int*)(&old_val);
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
        case 5:;
            struct hist_item_int *s5 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s5->val = *(int*)(&old_val);
            s5->rip = rip;
            s5->next = hist->hist.hist_list[0];
            hist->hist.hist_list[5] = s5;
            break;
        case 6:;
            struct hist_item_int *s6 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s6->val = *(int*)(&old_val);
            s6->rip = rip;
            s6->next = hist->hist.hist_list[0];
            hist->hist.hist_list[6] = s6;
            break;
    }

}

node_st *ASTchild(node_st *name) {
    node_st *node = NewNode();
    node->data.N_child = MEMmalloc(sizeof(struct NODE_DATA_CHILD));
    NODE_TYPE(node) = NT_CHILD;
    node->data.N_child->hist = MEMmalloc(sizeof(struct NODE_HIST_CHILD));
    CHILD_NAME(node) = name;
    CHILD_LIFETIMES(node) = NULL;
    CHILD_NEXT(node) = NULL;
    CHILD_TYPE_REFERENCE(node) = NULL;
    CHILD_TYPE(node) = 0;
    CHILD_IN_CONSTRUCTOR(node) = 0;
    CHILD_IS_MANDATORY(node) = 0;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_child->child_children.child_children_at;
    return node;}

struct wp_handler_data LIFETIME_RANGE_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_LIFETIME_RANGE, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_LIFETIME_RANGE, hist) - offsetof(struct NODE_DATA_LIFETIME_RANGE, inclusive), .datatype = HDT_bool, .is_child = false }, { .index = 2, .offset = offsetof(struct NODE_DATA_LIFETIME_RANGE, hist) - offsetof(struct NODE_DATA_LIFETIME_RANGE, action_id), .datatype = HDT_int, .is_child = false }, { .index = 3, .offset = offsetof(struct NODE_DATA_LIFETIME_RANGE, hist) - offsetof(struct NODE_DATA_LIFETIME_RANGE, next_action_id), .datatype = HDT_int, .is_child = false }, };
void wphandler_lifetime_range(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_LIFETIME_RANGE *hist = (struct NODE_HIST_LIFETIME_RANGE *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
            struct hist_item_link *s0 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s0->val = old_val;
            s0->rip = rip;
            s0->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s0;
            break;
        case 1:;
            struct hist_item_bool *s1 = (struct hist_item_bool *)malloc(sizeof(struct hist_item_bool));
            s1->val = *(bool*)(&old_val);
            s1->rip = rip;
            s1->next = hist->hist.hist_list[0];
            hist->hist.hist_list[1] = s1;
            break;
        case 2:;
            struct hist_item_int *s2 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s2->val = *(int*)(&old_val);
            s2->rip = rip;
            s2->next = hist->hist.hist_list[0];
            hist->hist.hist_list[2] = s2;
            break;
        case 3:;
            struct hist_item_int *s3 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s3->val = *(int*)(&old_val);
            s3->rip = rip;
            s3->next = hist->hist.hist_list[0];
            hist->hist.hist_list[3] = s3;
            break;
    }

}

node_st *ASTlifetime_range() {
    node_st *node = NewNode();
    node->data.N_lifetime_range = MEMmalloc(sizeof(struct NODE_DATA_LIFETIME_RANGE));
    NODE_TYPE(node) = NT_LIFETIME_RANGE;
    node->data.N_lifetime_range->hist = MEMmalloc(sizeof(struct NODE_HIST_LIFETIME_RANGE));
    LIFETIME_RANGE_TARGET(node) = NULL;
    LIFETIME_RANGE_INCLUSIVE(node) = false;
    LIFETIME_RANGE_ACTION_ID(node) = 0;
    LIFETIME_RANGE_NEXT_ACTION_ID(node) = 0;
    NODE_NUMCHILDREN(node) = 1;
    NODE_CHILDREN(node) = node->data.N_lifetime_range->lifetime_range_children.lifetime_range_children_at;
    return node;}

struct wp_handler_data ILIFETIME_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_ILIFETIME, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_ILIFETIME, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_ILIFETIME, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_ILIFETIME, hist) - offsetof(struct NODE_DATA_ILIFETIME, type), .datatype = HDT_link_or_enum, .is_child = false }, };
void wphandler_ilifetime(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_ILIFETIME *hist = (struct NODE_HIST_ILIFETIME *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
            struct hist_item_link *s2 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s2->val = old_val;
            s2->rip = rip;
            s2->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s2;
            break;
        case 3:;
            struct hist_item_link_or_enum *s3 = (struct hist_item_link_or_enum *)malloc(sizeof(struct hist_item_link_or_enum));
            s3->val = *(int*)(&old_val);
            s3->rip = rip;
            s3->next = hist->hist.hist_list[0];
            hist->hist.hist_list[3] = s3;
            break;
    }

}

node_st *ASTilifetime() {
    node_st *node = NewNode();
    node->data.N_ilifetime = MEMmalloc(sizeof(struct NODE_DATA_ILIFETIME));
    NODE_TYPE(node) = NT_ILIFETIME;
    node->data.N_ilifetime->hist = MEMmalloc(sizeof(struct NODE_HIST_ILIFETIME));
    ILIFETIME_BEGIN(node) = NULL;
    ILIFETIME_END(node) = NULL;
    ILIFETIME_NEXT(node) = NULL;
    ILIFETIME_TYPE(node) = 0;
    NODE_NUMCHILDREN(node) = 3;
    NODE_CHILDREN(node) = node->data.N_ilifetime->ilifetime_children.ilifetime_children_at;
    return node;}

struct wp_handler_data INODESET_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_INODESET, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_INODESET, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_INODESET, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_INODESET, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_INODESET, hist) - offsetof(struct NODE_DATA_INODESET, iinfo), .datatype = HDT_string, .is_child = false }, };
void wphandler_inodeset(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_INODESET *hist = (struct NODE_HIST_INODESET *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
            struct hist_item_link *s3 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s3->val = old_val;
            s3->rip = rip;
            s3->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s3;
            break;
        case 4:;
            struct hist_item_string *s4 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s4->val = (char*)old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
    }

}

node_st *ASTinodeset() {
    node_st *node = NewNode();
    node->data.N_inodeset = MEMmalloc(sizeof(struct NODE_DATA_INODESET));
    NODE_TYPE(node) = NT_INODESET;
    node->data.N_inodeset->hist = MEMmalloc(sizeof(struct NODE_HIST_INODESET));
    INODESET_NAME(node) = NULL;
    INODESET_EXPR(node) = NULL;
    INODESET_UNPACKED(node) = NULL;
    INODESET_NEXT(node) = NULL;
    INODESET_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_inodeset->inodeset_children.inodeset_children_at;
    return node;}

struct wp_handler_data INODE_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_INODE, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_INODE, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_INODE, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_INODE, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_INODE, hist) - 32, .datatype = HDT_link, .is_child = true }, { .index = 5, .offset = offsetof(struct NODE_DATA_INODE, hist) - offsetof(struct NODE_DATA_INODE, iifno), .datatype = HDT_string, .is_child = false }, { .index = 6, .offset = offsetof(struct NODE_DATA_INODE, hist) - offsetof(struct NODE_DATA_INODE, is_root), .datatype = HDT_int, .is_child = false }, { .index = 7, .offset = offsetof(struct NODE_DATA_INODE, hist) - offsetof(struct NODE_DATA_INODE, index), .datatype = HDT_int, .is_child = false }, };
void wphandler_inode(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_INODE *hist = (struct NODE_HIST_INODE *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
                    
        case 4:;
            struct hist_item_link *s4 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s4->val = old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s4;
            break;
        case 5:;
            struct hist_item_string *s5 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s5->val = (char*)old_val;
            s5->rip = rip;
            s5->next = hist->hist.hist_list[0];
            hist->hist.hist_list[5] = s5;
            break;
        case 6:;
            struct hist_item_int *s6 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s6->val = *(int*)(&old_val);
            s6->rip = rip;
            s6->next = hist->hist.hist_list[0];
            hist->hist.hist_list[6] = s6;
            break;
        case 7:;
            struct hist_item_int *s7 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s7->val = *(int*)(&old_val);
            s7->rip = rip;
            s7->next = hist->hist.hist_list[0];
            hist->hist.hist_list[7] = s7;
            break;
    }

}

node_st *ASTinode(node_st *name, char * iifno) {
    node_st *node = NewNode();
    node->data.N_inode = MEMmalloc(sizeof(struct NODE_DATA_INODE));
    NODE_TYPE(node) = NT_INODE;
    node->data.N_inode->hist = MEMmalloc(sizeof(struct NODE_HIST_INODE));
    INODE_NAME(node) = name;
    INODE_NEXT(node) = NULL;
    INODE_ICHILDREN(node) = NULL;
    INODE_IATTRIBUTES(node) = NULL;
    INODE_LIFETIMES(node) = NULL;
    INODE_IIFNO(node) = iifno;
    INODE_IS_ROOT(node) = 0;
    INODE_INDEX(node) = 0;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_inode->inode_children.inode_children_at;
    return node;}

struct wp_handler_data IPASS_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_IPASS, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_IPASS, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_IPASS, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_IPASS, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_IPASS, hist) - offsetof(struct NODE_DATA_IPASS, iifno), .datatype = HDT_string, .is_child = false }, };
void wphandler_ipass(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_IPASS *hist = (struct NODE_HIST_IPASS *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
            struct hist_item_link *s3 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s3->val = old_val;
            s3->rip = rip;
            s3->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s3;
            break;
        case 4:;
            struct hist_item_string *s4 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s4->val = (char*)old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[0];
            hist->hist.hist_list[4] = s4;
            break;
    }

}

node_st *ASTipass(node_st *name, char * iifno) {
    node_st *node = NewNode();
    node->data.N_ipass = MEMmalloc(sizeof(struct NODE_DATA_IPASS));
    NODE_TYPE(node) = NT_IPASS;
    node->data.N_ipass->hist = MEMmalloc(sizeof(struct NODE_HIST_IPASS));
    IPASS_NAME(node) = name;
    IPASS_IPREFIX(node) = NULL;
    IPASS_TARGET_FUNC(node) = NULL;
    IPASS_NEXT(node) = NULL;
    IPASS_IIFNO(node) = iifno;
    NODE_NUMCHILDREN(node) = 4;
    NODE_CHILDREN(node) = node->data.N_ipass->ipass_children.ipass_children_at;
    return node;}

struct wp_handler_data ITRAVERSAL_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - 32, .datatype = HDT_link, .is_child = true }, { .index = 5, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - offsetof(struct NODE_DATA_ITRAVERSAL, index), .datatype = HDT_int, .is_child = false }, { .index = 6, .offset = offsetof(struct NODE_DATA_ITRAVERSAL, hist) - offsetof(struct NODE_DATA_ITRAVERSAL, iinfo), .datatype = HDT_string, .is_child = false }, };
void wphandler_itraversal(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_ITRAVERSAL *hist = (struct NODE_HIST_ITRAVERSAL *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
                    
        case 4:;
            struct hist_item_link *s4 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s4->val = old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s4;
            break;
        case 5:;
            struct hist_item_int *s5 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s5->val = *(int*)(&old_val);
            s5->rip = rip;
            s5->next = hist->hist.hist_list[0];
            hist->hist.hist_list[5] = s5;
            break;
        case 6:;
            struct hist_item_string *s6 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s6->val = (char*)old_val;
            s6->rip = rip;
            s6->next = hist->hist.hist_list[0];
            hist->hist.hist_list[6] = s6;
            break;
    }

}

node_st *ASTitraversal(node_st *name) {
    node_st *node = NewNode();
    node->data.N_itraversal = MEMmalloc(sizeof(struct NODE_DATA_ITRAVERSAL));
    NODE_TYPE(node) = NT_ITRAVERSAL;
    node->data.N_itraversal->hist = MEMmalloc(sizeof(struct NODE_HIST_ITRAVERSAL));
    ITRAVERSAL_NAME(node) = name;
    ITRAVERSAL_IPREFIX(node) = NULL;
    ITRAVERSAL_INODES(node) = NULL;
    ITRAVERSAL_DATA(node) = NULL;
    ITRAVERSAL_NEXT(node) = NULL;
    ITRAVERSAL_INDEX(node) = 0;
    ITRAVERSAL_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_itraversal->itraversal_children.itraversal_children_at;
    return node;}

struct wp_handler_data IPHASE_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - 32, .datatype = HDT_link, .is_child = true }, { .index = 5, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - offsetof(struct NODE_DATA_IPHASE, is_start), .datatype = HDT_int, .is_child = false }, { .index = 6, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - offsetof(struct NODE_DATA_IPHASE, is_cycle), .datatype = HDT_int, .is_child = false }, { .index = 7, .offset = offsetof(struct NODE_DATA_IPHASE, hist) - offsetof(struct NODE_DATA_IPHASE, iinfo), .datatype = HDT_string, .is_child = false }, };
void wphandler_iphase(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_IPHASE *hist = (struct NODE_HIST_IPHASE *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
                    
        case 4:;
            struct hist_item_link *s4 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s4->val = old_val;
            s4->rip = rip;
            s4->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s4;
            break;
        case 5:;
            struct hist_item_int *s5 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s5->val = *(int*)(&old_val);
            s5->rip = rip;
            s5->next = hist->hist.hist_list[0];
            hist->hist.hist_list[5] = s5;
            break;
        case 6:;
            struct hist_item_int *s6 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s6->val = *(int*)(&old_val);
            s6->rip = rip;
            s6->next = hist->hist.hist_list[0];
            hist->hist.hist_list[6] = s6;
            break;
        case 7:;
            struct hist_item_string *s7 = (struct hist_item_string *)malloc(sizeof(struct hist_item_string));
            s7->val = (char*)old_val;
            s7->rip = rip;
            s7->next = hist->hist.hist_list[0];
            hist->hist.hist_list[7] = s7;
            break;
    }

}

node_st *ASTiphase(node_st *name, int is_start) {
    node_st *node = NewNode();
    node->data.N_iphase = MEMmalloc(sizeof(struct NODE_DATA_IPHASE));
    NODE_TYPE(node) = NT_IPHASE;
    node->data.N_iphase->hist = MEMmalloc(sizeof(struct NODE_HIST_IPHASE));
    IPHASE_NAME(node) = name;
    IPHASE_IPREFIX(node) = NULL;
    IPHASE_GATE_FUNC(node) = NULL;
    IPHASE_IACTIONS(node) = NULL;
    IPHASE_NEXT(node) = NULL;
    IPHASE_IS_START(node) = is_start;
    IPHASE_IS_CYCLE(node) = 0;
    IPHASE_IINFO(node) = NULL;
    NODE_NUMCHILDREN(node) = 5;
    NODE_CHILDREN(node) = node->data.N_iphase->iphase_children.iphase_children_at;
    return node;}

struct wp_handler_data IACTIONS_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_IACTIONS, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_IACTIONS, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_IACTIONS, hist) - offsetof(struct NODE_DATA_IACTIONS, action_id), .datatype = HDT_int, .is_child = false }, };
void wphandler_iactions(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_IACTIONS *hist = (struct NODE_HIST_IACTIONS *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
            struct hist_item_link *s1 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s1->val = old_val;
            s1->rip = rip;
            s1->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s1;
            break;
        case 2:;
            struct hist_item_int *s2 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s2->val = *(int*)(&old_val);
            s2->rip = rip;
            s2->next = hist->hist.hist_list[0];
            hist->hist.hist_list[2] = s2;
            break;
    }

}

node_st *ASTiactions() {
    node_st *node = NewNode();
    node->data.N_iactions = MEMmalloc(sizeof(struct NODE_DATA_IACTIONS));
    NODE_TYPE(node) = NT_IACTIONS;
    node->data.N_iactions->hist = MEMmalloc(sizeof(struct NODE_HIST_IACTIONS));
    IACTIONS_REFERENCE(node) = NULL;
    IACTIONS_NEXT(node) = NULL;
    IACTIONS_ACTION_ID(node) = 0;
    NODE_NUMCHILDREN(node) = 2;
    NODE_CHILDREN(node) = node->data.N_iactions->iactions_children.iactions_children_at;
    return node;}

struct wp_handler_data AST_data[] = {{ .index = 0, .offset = offsetof(struct NODE_DATA_AST, hist) - 0, .datatype = HDT_link, .is_child = true }, { .index = 1, .offset = offsetof(struct NODE_DATA_AST, hist) - 8, .datatype = HDT_link, .is_child = true }, { .index = 2, .offset = offsetof(struct NODE_DATA_AST, hist) - 16, .datatype = HDT_link, .is_child = true }, { .index = 3, .offset = offsetof(struct NODE_DATA_AST, hist) - 24, .datatype = HDT_link, .is_child = true }, { .index = 4, .offset = offsetof(struct NODE_DATA_AST, hist) - 32, .datatype = HDT_link, .is_child = true }, { .index = 5, .offset = offsetof(struct NODE_DATA_AST, hist) - 40, .datatype = HDT_link, .is_child = true }, { .index = 6, .offset = offsetof(struct NODE_DATA_AST, hist) - 48, .datatype = HDT_link, .is_child = true }, { .index = 7, .offset = offsetof(struct NODE_DATA_AST, hist) - offsetof(struct NODE_DATA_AST, num_traversals), .datatype = HDT_int, .is_child = false }, { .index = 8, .offset = offsetof(struct NODE_DATA_AST, hist) - offsetof(struct NODE_DATA_AST, num_nodes), .datatype = HDT_int, .is_child = false }, { .index = 9, .offset = offsetof(struct NODE_DATA_AST, hist) - offsetof(struct NODE_DATA_AST, root_node), .datatype = HDT_link, .is_child = false }, { .index = 10, .offset = offsetof(struct NODE_DATA_AST, hist) - offsetof(struct NODE_DATA_AST, start_phase), .datatype = HDT_link, .is_child = false }, { .index = 11, .offset = offsetof(struct NODE_DATA_AST, hist) - offsetof(struct NODE_DATA_AST, uses_unsafe), .datatype = HDT_bool, .is_child = false }, };
void wphandler_ast(void *addr, void *old_val, void *ucontext, void *userdata) {
    ucontext_t *context = (ucontext_t *)ucontext;
    struct wp_handler_data *data = (struct wp_handler_data *)userdata;
    void *rip = (void *)context->uc_mcontext.gregs[REG_RIP];
    struct NODE_HIST_AST *hist = (struct NODE_HIST_AST *)(&addr + data->offset);
    switch (data->index) {
        case 0:;
                    
        case 1:;
                    
        case 2:;
                    
        case 3:;
                    
        case 4:;
                    
        case 5:;
                    
        case 6:;
            struct hist_item_link *s6 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s6->val = old_val;
            s6->rip = rip;
            s6->next = hist->hist.hist_list[data->index];
            hist->hist.hist_list[data->index] = s6;
            break;
        case 7:;
            struct hist_item_int *s7 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s7->val = *(int*)(&old_val);
            s7->rip = rip;
            s7->next = hist->hist.hist_list[0];
            hist->hist.hist_list[7] = s7;
            break;
        case 8:;
            struct hist_item_int *s8 = (struct hist_item_int *)malloc(sizeof(struct hist_item_int));
            s8->val = *(int*)(&old_val);
            s8->rip = rip;
            s8->next = hist->hist.hist_list[0];
            hist->hist.hist_list[8] = s8;
            break;
        case 9:;
            struct hist_item_link *s9 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s9->val = old_val;
            s9->rip = rip;
            s9->next = hist->hist.hist_list[0];
            hist->hist.hist_list[9] = s9;
            break;
        case 10:;
            struct hist_item_link *s10 = (struct hist_item_link *)malloc(sizeof(struct hist_item_link));
            s10->val = old_val;
            s10->rip = rip;
            s10->next = hist->hist.hist_list[0];
            hist->hist.hist_list[10] = s10;
            break;
        case 11:;
            struct hist_item_bool *s11 = (struct hist_item_bool *)malloc(sizeof(struct hist_item_bool));
            s11->val = *(bool*)(&old_val);
            s11->rip = rip;
            s11->next = hist->hist.hist_list[0];
            hist->hist.hist_list[11] = s11;
            break;
    }

}

node_st *ASTast() {
    node_st *node = NewNode();
    node->data.N_ast = MEMmalloc(sizeof(struct NODE_DATA_AST));
    NODE_TYPE(node) = NT_AST;
    node->data.N_ast->hist = MEMmalloc(sizeof(struct NODE_HIST_AST));
    AST_IPHASES(node) = NULL;
    AST_ITRAVERSALS(node) = NULL;
    AST_IPASSES(node) = NULL;
    AST_INODES(node) = NULL;
    AST_INODESETS(node) = NULL;
    AST_ENUMS(node) = NULL;
    AST_STABLE(node) = NULL;
    AST_NUM_TRAVERSALS(node) = 0;
    AST_NUM_NODES(node) = 0;
    AST_ROOT_NODE(node) = NULL;
    AST_START_PHASE(node) = NULL;
    AST_USES_UNSAFE(node) = false;
    NODE_NUMCHILDREN(node) = 7;
    NODE_CHILDREN(node) = node->data.N_ast->ast_children.ast_children_at;
    return node;}

