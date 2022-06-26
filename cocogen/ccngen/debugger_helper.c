#include "ccngen/ast.h"
#include "ccngen/debugger_helper.h"
#ifdef INCLUDE_DEBUGGER
#include <stddef.h>
#include "palm/str.h"
int DBGHelper_ntoi(enum ccn_nodetype type, char *name) {
    switch (type) {
        case NT_ID:
            if (STReq(name, "next")) return 0;
            if (STReq(name, "orig")) return 1;
            if (STReq(name, "lwr")) return 2;
            if (STReq(name, "upr")) return 3;
            if (STReq(name, "row")) return 4;
            if (STReq(name, "col_begin")) return 5;
            if (STReq(name, "col_end")) return 6;
            return -1;
                    case NT_IENUM:
            if (STReq(name, "vals")) return 0;
            if (STReq(name, "name")) return 1;
            if (STReq(name, "iprefix")) return 2;
            if (STReq(name, "next")) return 3;
            if (STReq(name, "iinfo")) return 4;
            return -1;
                    case NT_ATTRIBUTE:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "type_reference")) return 1;
            if (STReq(name, "lifetimes")) return 2;
            if (STReq(name, "next")) return 3;
            if (STReq(name, "type")) return 4;
            if (STReq(name, "in_constructor")) return 5;
            return -1;
                    case NT_ITRAVDATA:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "type_reference")) return 1;
            if (STReq(name, "next")) return 2;
            if (STReq(name, "type")) return 3;
            if (STReq(name, "include_file")) return 4;
            return -1;
                    case NT_SETOPERATION:
            if (STReq(name, "left")) return 0;
            if (STReq(name, "right")) return 1;
            if (STReq(name, "type")) return 2;
            return -1;
                    case NT_SETLITERAL:
            if (STReq(name, "reference")) return 0;
            if (STReq(name, "left")) return 1;
            if (STReq(name, "right")) return 2;
            return -1;
                    case NT_SETREFERENCE:
            if (STReq(name, "reference")) return 0;
            return -1;
                    case NT_STE:
            if (STReq(name, "next")) return 0;
            if (STReq(name, "key")) return 1;
            if (STReq(name, "value")) return 2;
            return -1;
                    case NT_CHILD:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "lifetimes")) return 1;
            if (STReq(name, "next")) return 2;
            if (STReq(name, "type_reference")) return 3;
            if (STReq(name, "type")) return 4;
            if (STReq(name, "in_constructor")) return 5;
            if (STReq(name, "is_mandatory")) return 6;
            return -1;
                    case NT_LIFETIME_RANGE:
            if (STReq(name, "target")) return 0;
            if (STReq(name, "inclusive")) return 1;
            if (STReq(name, "action_id")) return 2;
            if (STReq(name, "next_action_id")) return 3;
            return -1;
                    case NT_ILIFETIME:
            if (STReq(name, "begin")) return 0;
            if (STReq(name, "end")) return 1;
            if (STReq(name, "next")) return 2;
            if (STReq(name, "type")) return 3;
            return -1;
                    case NT_INODESET:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "expr")) return 1;
            if (STReq(name, "unpacked")) return 2;
            if (STReq(name, "next")) return 3;
            if (STReq(name, "iinfo")) return 4;
            return -1;
                    case NT_INODE:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "next")) return 1;
            if (STReq(name, "ichildren")) return 2;
            if (STReq(name, "iattributes")) return 3;
            if (STReq(name, "lifetimes")) return 4;
            if (STReq(name, "iifno")) return 5;
            if (STReq(name, "is_root")) return 6;
            if (STReq(name, "index")) return 7;
            return -1;
                    case NT_IPASS:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "iprefix")) return 1;
            if (STReq(name, "target_func")) return 2;
            if (STReq(name, "next")) return 3;
            if (STReq(name, "iifno")) return 4;
            return -1;
                    case NT_ITRAVERSAL:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "iprefix")) return 1;
            if (STReq(name, "inodes")) return 2;
            if (STReq(name, "data")) return 3;
            if (STReq(name, "next")) return 4;
            if (STReq(name, "index")) return 5;
            if (STReq(name, "iinfo")) return 6;
            return -1;
                    case NT_IPHASE:
            if (STReq(name, "name")) return 0;
            if (STReq(name, "iprefix")) return 1;
            if (STReq(name, "gate_func")) return 2;
            if (STReq(name, "iactions")) return 3;
            if (STReq(name, "next")) return 4;
            if (STReq(name, "is_start")) return 5;
            if (STReq(name, "is_cycle")) return 6;
            if (STReq(name, "iinfo")) return 7;
            return -1;
                    case NT_IACTIONS:
            if (STReq(name, "reference")) return 0;
            if (STReq(name, "next")) return 1;
            if (STReq(name, "action_id")) return 2;
            return -1;
                    case NT_AST:
            if (STReq(name, "iphases")) return 0;
            if (STReq(name, "itraversals")) return 1;
            if (STReq(name, "ipasses")) return 2;
            if (STReq(name, "inodes")) return 3;
            if (STReq(name, "inodesets")) return 4;
            if (STReq(name, "enums")) return 5;
            if (STReq(name, "stable")) return 6;
            if (STReq(name, "num_traversals")) return 7;
            if (STReq(name, "num_nodes")) return 8;
            if (STReq(name, "root_node")) return 9;
            if (STReq(name, "start_phase")) return 10;
            if (STReq(name, "uses_unsafe")) return 11;
            return -1;
                    default:
            return -1;
                }

}

char *DBGHelper_iton(enum ccn_nodetype type, int idx) {
    switch (type) {
        case NT_ID:
            switch (idx) {
                case 0: return "next";
                case 1: return "orig";
                case 2: return "lwr";
                case 3: return "upr";
                case 4: return "row";
                case 5: return "col_begin";
                case 6: return "col_end";
                default:
                    return NULL;
                                }

                    case NT_IENUM:
            switch (idx) {
                case 0: return "vals";
                case 1: return "name";
                case 2: return "iprefix";
                case 3: return "next";
                case 4: return "iinfo";
                default:
                    return NULL;
                                }

                    case NT_ATTRIBUTE:
            switch (idx) {
                case 0: return "name";
                case 1: return "type_reference";
                case 2: return "lifetimes";
                case 3: return "next";
                case 4: return "type";
                case 5: return "in_constructor";
                default:
                    return NULL;
                                }

                    case NT_ITRAVDATA:
            switch (idx) {
                case 0: return "name";
                case 1: return "type_reference";
                case 2: return "next";
                case 3: return "type";
                case 4: return "include_file";
                default:
                    return NULL;
                                }

                    case NT_SETOPERATION:
            switch (idx) {
                case 0: return "left";
                case 1: return "right";
                case 2: return "type";
                default:
                    return NULL;
                                }

                    case NT_SETLITERAL:
            switch (idx) {
                case 0: return "reference";
                case 1: return "left";
                case 2: return "right";
                default:
                    return NULL;
                                }

                    case NT_SETREFERENCE:
            switch (idx) {
                case 0: return "reference";
                default:
                    return NULL;
                                }

                    case NT_STE:
            switch (idx) {
                case 0: return "next";
                case 1: return "key";
                case 2: return "value";
                default:
                    return NULL;
                                }

                    case NT_CHILD:
            switch (idx) {
                case 0: return "name";
                case 1: return "lifetimes";
                case 2: return "next";
                case 3: return "type_reference";
                case 4: return "type";
                case 5: return "in_constructor";
                case 6: return "is_mandatory";
                default:
                    return NULL;
                                }

                    case NT_LIFETIME_RANGE:
            switch (idx) {
                case 0: return "target";
                case 1: return "inclusive";
                case 2: return "action_id";
                case 3: return "next_action_id";
                default:
                    return NULL;
                                }

                    case NT_ILIFETIME:
            switch (idx) {
                case 0: return "begin";
                case 1: return "end";
                case 2: return "next";
                case 3: return "type";
                default:
                    return NULL;
                                }

                    case NT_INODESET:
            switch (idx) {
                case 0: return "name";
                case 1: return "expr";
                case 2: return "unpacked";
                case 3: return "next";
                case 4: return "iinfo";
                default:
                    return NULL;
                                }

                    case NT_INODE:
            switch (idx) {
                case 0: return "name";
                case 1: return "next";
                case 2: return "ichildren";
                case 3: return "iattributes";
                case 4: return "lifetimes";
                case 5: return "iifno";
                case 6: return "is_root";
                case 7: return "index";
                default:
                    return NULL;
                                }

                    case NT_IPASS:
            switch (idx) {
                case 0: return "name";
                case 1: return "iprefix";
                case 2: return "target_func";
                case 3: return "next";
                case 4: return "iifno";
                default:
                    return NULL;
                                }

                    case NT_ITRAVERSAL:
            switch (idx) {
                case 0: return "name";
                case 1: return "iprefix";
                case 2: return "inodes";
                case 3: return "data";
                case 4: return "next";
                case 5: return "index";
                case 6: return "iinfo";
                default:
                    return NULL;
                                }

                    case NT_IPHASE:
            switch (idx) {
                case 0: return "name";
                case 1: return "iprefix";
                case 2: return "gate_func";
                case 3: return "iactions";
                case 4: return "next";
                case 5: return "is_start";
                case 6: return "is_cycle";
                case 7: return "iinfo";
                default:
                    return NULL;
                                }

                    case NT_IACTIONS:
            switch (idx) {
                case 0: return "reference";
                case 1: return "next";
                case 2: return "action_id";
                default:
                    return NULL;
                                }

                    case NT_AST:
            switch (idx) {
                case 0: return "iphases";
                case 1: return "itraversals";
                case 2: return "ipasses";
                case 3: return "inodes";
                case 4: return "inodesets";
                case 5: return "enums";
                case 6: return "stable";
                case 7: return "num_traversals";
                case 8: return "num_nodes";
                case 9: return "root_node";
                case 10: return "start_phase";
                case 11: return "uses_unsafe";
                default:
                    return NULL;
                                }

                    default:
            return NULL;
                }

}

enum H_DATTYPES DBGHelper_gettype(enum ccn_nodetype type, int idx) {
    switch (type) {
        case NT_ID:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_string;
                case 2: return HDT_string;
                case 3: return HDT_string;
                case 4: return HDT_int;
                case 5: return HDT_int;
                case 6: return HDT_int;
                default:
                    return HDT_NULL;
                                }

                    case NT_IENUM:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_string;
                default:
                    return HDT_NULL;
                                }

                    case NT_ATTRIBUTE:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_link_or_enum;
                case 5: return HDT_int;
                default:
                    return HDT_NULL;
                                }

                    case NT_ITRAVDATA:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link_or_enum;
                case 4: return HDT_string;
                default:
                    return HDT_NULL;
                                }

                    case NT_SETOPERATION:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link_or_enum;
                default:
                    return HDT_NULL;
                                }

                    case NT_SETLITERAL:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                default:
                    return HDT_NULL;
                                }

                    case NT_SETREFERENCE:
            switch (idx) {
                case 0: return HDT_link;
                default:
                    return HDT_NULL;
                                }

                    case NT_STE:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                default:
                    return HDT_NULL;
                                }

                    case NT_CHILD:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_link_or_enum;
                case 5: return HDT_int;
                case 6: return HDT_int;
                default:
                    return HDT_NULL;
                                }

                    case NT_LIFETIME_RANGE:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_bool;
                case 2: return HDT_int;
                case 3: return HDT_int;
                default:
                    return HDT_NULL;
                                }

                    case NT_ILIFETIME:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link_or_enum;
                default:
                    return HDT_NULL;
                                }

                    case NT_INODESET:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_string;
                default:
                    return HDT_NULL;
                                }

                    case NT_INODE:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_link;
                case 5: return HDT_string;
                case 6: return HDT_int;
                case 7: return HDT_int;
                default:
                    return HDT_NULL;
                                }

                    case NT_IPASS:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_string;
                default:
                    return HDT_NULL;
                                }

                    case NT_ITRAVERSAL:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_link;
                case 5: return HDT_int;
                case 6: return HDT_string;
                default:
                    return HDT_NULL;
                                }

                    case NT_IPHASE:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_link;
                case 5: return HDT_int;
                case 6: return HDT_int;
                case 7: return HDT_string;
                default:
                    return HDT_NULL;
                                }

                    case NT_IACTIONS:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_int;
                default:
                    return HDT_NULL;
                                }

                    case NT_AST:
            switch (idx) {
                case 0: return HDT_link;
                case 1: return HDT_link;
                case 2: return HDT_link;
                case 3: return HDT_link;
                case 4: return HDT_link;
                case 5: return HDT_link;
                case 6: return HDT_link;
                case 7: return HDT_int;
                case 8: return HDT_int;
                case 9: return HDT_link;
                case 10: return HDT_link;
                case 11: return HDT_bool;
                default:
                    return HDT_NULL;
                                }

                    default:
            return HDT_NULL;
                }

}

void *DBGHelper_getptr(node_st *node, int idx) {
    switch (NODE_TYPE(node)) {
        case NT_ID:
            switch (idx) {
                case 0: return (void*)&(ID_NEXT(node));
                case 1: return (void*)&(ID_ORIG(node));
                case 2: return (void*)&(ID_LWR(node));
                case 3: return (void*)&(ID_UPR(node));
                case 4: return (void*)&(ID_ROW(node));
                case 5: return (void*)&(ID_COL_BEGIN(node));
                case 6: return (void*)&(ID_COL_END(node));
                default:
                    return NULL;
                                }

                    case NT_IENUM:
            switch (idx) {
                case 0: return (void*)&(IENUM_VALS(node));
                case 1: return (void*)&(IENUM_NAME(node));
                case 2: return (void*)&(IENUM_IPREFIX(node));
                case 3: return (void*)&(IENUM_NEXT(node));
                case 4: return (void*)&(IENUM_IINFO(node));
                default:
                    return NULL;
                                }

                    case NT_ATTRIBUTE:
            switch (idx) {
                case 0: return (void*)&(ATTRIBUTE_NAME(node));
                case 1: return (void*)&(ATTRIBUTE_TYPE_REFERENCE(node));
                case 2: return (void*)&(ATTRIBUTE_LIFETIMES(node));
                case 3: return (void*)&(ATTRIBUTE_NEXT(node));
                case 4: return (void*)&(ATTRIBUTE_TYPE(node));
                case 5: return (void*)&(ATTRIBUTE_IN_CONSTRUCTOR(node));
                default:
                    return NULL;
                                }

                    case NT_ITRAVDATA:
            switch (idx) {
                case 0: return (void*)&(ITRAVDATA_NAME(node));
                case 1: return (void*)&(ITRAVDATA_TYPE_REFERENCE(node));
                case 2: return (void*)&(ITRAVDATA_NEXT(node));
                case 3: return (void*)&(ITRAVDATA_TYPE(node));
                case 4: return (void*)&(ITRAVDATA_INCLUDE_FILE(node));
                default:
                    return NULL;
                                }

                    case NT_SETOPERATION:
            switch (idx) {
                case 0: return (void*)&(SETOPERATION_LEFT(node));
                case 1: return (void*)&(SETOPERATION_RIGHT(node));
                case 2: return (void*)&(SETOPERATION_TYPE(node));
                default:
                    return NULL;
                                }

                    case NT_SETLITERAL:
            switch (idx) {
                case 0: return (void*)&(SETLITERAL_REFERENCE(node));
                case 1: return (void*)&(SETLITERAL_LEFT(node));
                case 2: return (void*)&(SETLITERAL_RIGHT(node));
                default:
                    return NULL;
                                }

                    case NT_SETREFERENCE:
            switch (idx) {
                case 0: return (void*)&(SETREFERENCE_REFERENCE(node));
                default:
                    return NULL;
                                }

                    case NT_STE:
            switch (idx) {
                case 0: return (void*)&(STE_NEXT(node));
                case 1: return (void*)&(STE_KEY(node));
                case 2: return (void*)&(STE_VALUE(node));
                default:
                    return NULL;
                                }

                    case NT_CHILD:
            switch (idx) {
                case 0: return (void*)&(CHILD_NAME(node));
                case 1: return (void*)&(CHILD_LIFETIMES(node));
                case 2: return (void*)&(CHILD_NEXT(node));
                case 3: return (void*)&(CHILD_TYPE_REFERENCE(node));
                case 4: return (void*)&(CHILD_TYPE(node));
                case 5: return (void*)&(CHILD_IN_CONSTRUCTOR(node));
                case 6: return (void*)&(CHILD_IS_MANDATORY(node));
                default:
                    return NULL;
                                }

                    case NT_LIFETIME_RANGE:
            switch (idx) {
                case 0: return (void*)&(LIFETIME_RANGE_TARGET(node));
                case 1: return (void*)&(LIFETIME_RANGE_INCLUSIVE(node));
                case 2: return (void*)&(LIFETIME_RANGE_ACTION_ID(node));
                case 3: return (void*)&(LIFETIME_RANGE_NEXT_ACTION_ID(node));
                default:
                    return NULL;
                                }

                    case NT_ILIFETIME:
            switch (idx) {
                case 0: return (void*)&(ILIFETIME_BEGIN(node));
                case 1: return (void*)&(ILIFETIME_END(node));
                case 2: return (void*)&(ILIFETIME_NEXT(node));
                case 3: return (void*)&(ILIFETIME_TYPE(node));
                default:
                    return NULL;
                                }

                    case NT_INODESET:
            switch (idx) {
                case 0: return (void*)&(INODESET_NAME(node));
                case 1: return (void*)&(INODESET_EXPR(node));
                case 2: return (void*)&(INODESET_UNPACKED(node));
                case 3: return (void*)&(INODESET_NEXT(node));
                case 4: return (void*)&(INODESET_IINFO(node));
                default:
                    return NULL;
                                }

                    case NT_INODE:
            switch (idx) {
                case 0: return (void*)&(INODE_NAME(node));
                case 1: return (void*)&(INODE_NEXT(node));
                case 2: return (void*)&(INODE_ICHILDREN(node));
                case 3: return (void*)&(INODE_IATTRIBUTES(node));
                case 4: return (void*)&(INODE_LIFETIMES(node));
                case 5: return (void*)&(INODE_IIFNO(node));
                case 6: return (void*)&(INODE_IS_ROOT(node));
                case 7: return (void*)&(INODE_INDEX(node));
                default:
                    return NULL;
                                }

                    case NT_IPASS:
            switch (idx) {
                case 0: return (void*)&(IPASS_NAME(node));
                case 1: return (void*)&(IPASS_IPREFIX(node));
                case 2: return (void*)&(IPASS_TARGET_FUNC(node));
                case 3: return (void*)&(IPASS_NEXT(node));
                case 4: return (void*)&(IPASS_IIFNO(node));
                default:
                    return NULL;
                                }

                    case NT_ITRAVERSAL:
            switch (idx) {
                case 0: return (void*)&(ITRAVERSAL_NAME(node));
                case 1: return (void*)&(ITRAVERSAL_IPREFIX(node));
                case 2: return (void*)&(ITRAVERSAL_INODES(node));
                case 3: return (void*)&(ITRAVERSAL_DATA(node));
                case 4: return (void*)&(ITRAVERSAL_NEXT(node));
                case 5: return (void*)&(ITRAVERSAL_INDEX(node));
                case 6: return (void*)&(ITRAVERSAL_IINFO(node));
                default:
                    return NULL;
                                }

                    case NT_IPHASE:
            switch (idx) {
                case 0: return (void*)&(IPHASE_NAME(node));
                case 1: return (void*)&(IPHASE_IPREFIX(node));
                case 2: return (void*)&(IPHASE_GATE_FUNC(node));
                case 3: return (void*)&(IPHASE_IACTIONS(node));
                case 4: return (void*)&(IPHASE_NEXT(node));
                case 5: return (void*)&(IPHASE_IS_START(node));
                case 6: return (void*)&(IPHASE_IS_CYCLE(node));
                case 7: return (void*)&(IPHASE_IINFO(node));
                default:
                    return NULL;
                                }

                    case NT_IACTIONS:
            switch (idx) {
                case 0: return (void*)&(IACTIONS_REFERENCE(node));
                case 1: return (void*)&(IACTIONS_NEXT(node));
                case 2: return (void*)&(IACTIONS_ACTION_ID(node));
                default:
                    return NULL;
                                }

                    case NT_AST:
            switch (idx) {
                case 0: return (void*)&(AST_IPHASES(node));
                case 1: return (void*)&(AST_ITRAVERSALS(node));
                case 2: return (void*)&(AST_IPASSES(node));
                case 3: return (void*)&(AST_INODES(node));
                case 4: return (void*)&(AST_INODESETS(node));
                case 5: return (void*)&(AST_ENUMS(node));
                case 6: return (void*)&(AST_STABLE(node));
                case 7: return (void*)&(AST_NUM_TRAVERSALS(node));
                case 8: return (void*)&(AST_NUM_NODES(node));
                case 9: return (void*)&(AST_ROOT_NODE(node));
                case 10: return (void*)&(AST_START_PHASE(node));
                case 11: return (void*)&(AST_USES_UNSAFE(node));
                default:
                    return NULL;
                                }

                    default:
            return NULL;
                }

}

void DBGHelper_setval(node_st *node, int idx, void *val) {
    void **val_ref = &val;
    switch (NODE_TYPE(node)) {
        case NT_ID:
            switch (idx) {
                case 0: ID_NEXT(node) = (node_st*)val; break;
                case 1: ID_ORIG(node) = *(char **)val_ref; break;
                case 2: ID_LWR(node) = *(char **)val_ref; break;
                case 3: ID_UPR(node) = *(char **)val_ref; break;
                case 4: ID_ROW(node) = *(int*)val_ref; break;
                case 5: ID_COL_BEGIN(node) = *(int*)val_ref; break;
                case 6: ID_COL_END(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_IENUM:
            switch (idx) {
                case 0: IENUM_VALS(node) = (node_st*)val; break;
                case 1: IENUM_NAME(node) = (node_st*)val; break;
                case 2: IENUM_IPREFIX(node) = (node_st*)val; break;
                case 3: IENUM_NEXT(node) = (node_st*)val; break;
                case 4: IENUM_IINFO(node) = *(char **)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_ATTRIBUTE:
            switch (idx) {
                case 0: ATTRIBUTE_NAME(node) = (node_st*)val; break;
                case 1: ATTRIBUTE_TYPE_REFERENCE(node) = (node_st*)val; break;
                case 2: ATTRIBUTE_LIFETIMES(node) = (node_st*)val; break;
                case 3: ATTRIBUTE_NEXT(node) = (node_st*)val; break;
                case 4: ATTRIBUTE_TYPE(node) = *(int*)val_ref; break;
                case 5: ATTRIBUTE_IN_CONSTRUCTOR(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_ITRAVDATA:
            switch (idx) {
                case 0: ITRAVDATA_NAME(node) = (node_st*)val; break;
                case 1: ITRAVDATA_TYPE_REFERENCE(node) = (node_st*)val; break;
                case 2: ITRAVDATA_NEXT(node) = (node_st*)val; break;
                case 3: ITRAVDATA_TYPE(node) = *(int*)val_ref; break;
                case 4: ITRAVDATA_INCLUDE_FILE(node) = *(char **)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_SETOPERATION:
            switch (idx) {
                case 0: SETOPERATION_LEFT(node) = (node_st*)val; break;
                case 1: SETOPERATION_RIGHT(node) = (node_st*)val; break;
                case 2: SETOPERATION_TYPE(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_SETLITERAL:
            switch (idx) {
                case 0: SETLITERAL_REFERENCE(node) = (node_st*)val; break;
                case 1: SETLITERAL_LEFT(node) = (node_st*)val; break;
                case 2: SETLITERAL_RIGHT(node) = (node_st*)val; break;
                default:
                    break;
            }

            break;
        case NT_SETREFERENCE:
            switch (idx) {
                case 0: SETREFERENCE_REFERENCE(node) = (node_st*)val; break;
                default:
                    break;
            }

            break;
        case NT_STE:
            switch (idx) {
                case 0: STE_NEXT(node) = (node_st*)val; break;
                case 1: STE_KEY(node) = (node_st*)val; break;
                case 2: STE_VALUE(node) = (node_st*)val; break;
                default:
                    break;
            }

            break;
        case NT_CHILD:
            switch (idx) {
                case 0: CHILD_NAME(node) = (node_st*)val; break;
                case 1: CHILD_LIFETIMES(node) = (node_st*)val; break;
                case 2: CHILD_NEXT(node) = (node_st*)val; break;
                case 3: CHILD_TYPE_REFERENCE(node) = (node_st*)val; break;
                case 4: CHILD_TYPE(node) = *(int*)val_ref; break;
                case 5: CHILD_IN_CONSTRUCTOR(node) = *(int*)val_ref; break;
                case 6: CHILD_IS_MANDATORY(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_LIFETIME_RANGE:
            switch (idx) {
                case 0: LIFETIME_RANGE_TARGET(node) = (node_st*)val; break;
                case 1: LIFETIME_RANGE_INCLUSIVE(node) = *(bool*)val_ref; break;
                case 2: LIFETIME_RANGE_ACTION_ID(node) = *(int*)val_ref; break;
                case 3: LIFETIME_RANGE_NEXT_ACTION_ID(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_ILIFETIME:
            switch (idx) {
                case 0: ILIFETIME_BEGIN(node) = (node_st*)val; break;
                case 1: ILIFETIME_END(node) = (node_st*)val; break;
                case 2: ILIFETIME_NEXT(node) = (node_st*)val; break;
                case 3: ILIFETIME_TYPE(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_INODESET:
            switch (idx) {
                case 0: INODESET_NAME(node) = (node_st*)val; break;
                case 1: INODESET_EXPR(node) = (node_st*)val; break;
                case 2: INODESET_UNPACKED(node) = (node_st*)val; break;
                case 3: INODESET_NEXT(node) = (node_st*)val; break;
                case 4: INODESET_IINFO(node) = *(char **)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_INODE:
            switch (idx) {
                case 0: INODE_NAME(node) = (node_st*)val; break;
                case 1: INODE_NEXT(node) = (node_st*)val; break;
                case 2: INODE_ICHILDREN(node) = (node_st*)val; break;
                case 3: INODE_IATTRIBUTES(node) = (node_st*)val; break;
                case 4: INODE_LIFETIMES(node) = (node_st*)val; break;
                case 5: INODE_IIFNO(node) = *(char **)val_ref; break;
                case 6: INODE_IS_ROOT(node) = *(int*)val_ref; break;
                case 7: INODE_INDEX(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_IPASS:
            switch (idx) {
                case 0: IPASS_NAME(node) = (node_st*)val; break;
                case 1: IPASS_IPREFIX(node) = (node_st*)val; break;
                case 2: IPASS_TARGET_FUNC(node) = (node_st*)val; break;
                case 3: IPASS_NEXT(node) = (node_st*)val; break;
                case 4: IPASS_IIFNO(node) = *(char **)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_ITRAVERSAL:
            switch (idx) {
                case 0: ITRAVERSAL_NAME(node) = (node_st*)val; break;
                case 1: ITRAVERSAL_IPREFIX(node) = (node_st*)val; break;
                case 2: ITRAVERSAL_INODES(node) = (node_st*)val; break;
                case 3: ITRAVERSAL_DATA(node) = (node_st*)val; break;
                case 4: ITRAVERSAL_NEXT(node) = (node_st*)val; break;
                case 5: ITRAVERSAL_INDEX(node) = *(int*)val_ref; break;
                case 6: ITRAVERSAL_IINFO(node) = *(char **)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_IPHASE:
            switch (idx) {
                case 0: IPHASE_NAME(node) = (node_st*)val; break;
                case 1: IPHASE_IPREFIX(node) = (node_st*)val; break;
                case 2: IPHASE_GATE_FUNC(node) = (node_st*)val; break;
                case 3: IPHASE_IACTIONS(node) = (node_st*)val; break;
                case 4: IPHASE_NEXT(node) = (node_st*)val; break;
                case 5: IPHASE_IS_START(node) = *(int*)val_ref; break;
                case 6: IPHASE_IS_CYCLE(node) = *(int*)val_ref; break;
                case 7: IPHASE_IINFO(node) = *(char **)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_IACTIONS:
            switch (idx) {
                case 0: IACTIONS_REFERENCE(node) = (node_st*)val; break;
                case 1: IACTIONS_NEXT(node) = (node_st*)val; break;
                case 2: IACTIONS_ACTION_ID(node) = *(int*)val_ref; break;
                default:
                    break;
            }

            break;
        case NT_AST:
            switch (idx) {
                case 0: AST_IPHASES(node) = (node_st*)val; break;
                case 1: AST_ITRAVERSALS(node) = (node_st*)val; break;
                case 2: AST_IPASSES(node) = (node_st*)val; break;
                case 3: AST_INODES(node) = (node_st*)val; break;
                case 4: AST_INODESETS(node) = (node_st*)val; break;
                case 5: AST_ENUMS(node) = (node_st*)val; break;
                case 6: AST_STABLE(node) = (node_st*)val; break;
                case 7: AST_NUM_TRAVERSALS(node) = *(int*)val_ref; break;
                case 8: AST_NUM_NODES(node) = *(int*)val_ref; break;
                case 9: AST_ROOT_NODE(node) = (node_st*)val; break;
                case 10: AST_START_PHASE(node) = (node_st*)val; break;
                case 11: AST_USES_UNSAFE(node) = *(bool*)val_ref; break;
                default:
                    break;
            }

            break;
        default:
            break;
    }

}

int DBGHelper_ischild(enum ccn_nodetype type, int idx) {
    switch (type) {
        case NT_ID:
            switch (idx) {
                case 0: return 1;
                case 1: return 0;
                default:
                    return -1;
                                }

                    case NT_IENUM:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 0;
                default:
                    return -1;
                                }

                    case NT_ATTRIBUTE:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 0;
                default:
                    return -1;
                                }

                    case NT_ITRAVDATA:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 0;
                default:
                    return -1;
                                }

                    case NT_SETOPERATION:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 0;
                default:
                    return -1;
                                }

                    case NT_SETLITERAL:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                default:
                    return -1;
                                }

                    case NT_SETREFERENCE:
            switch (idx) {
                case 0: return 1;
                default:
                    return -1;
                                }

                    case NT_STE:
            switch (idx) {
                case 0: return 1;
                case 1: return 0;
                default:
                    return -1;
                                }

                    case NT_CHILD:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 0;
                default:
                    return -1;
                                }

                    case NT_LIFETIME_RANGE:
            switch (idx) {
                case 0: return 1;
                case 1: return 0;
                default:
                    return -1;
                                }

                    case NT_ILIFETIME:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 0;
                default:
                    return -1;
                                }

                    case NT_INODESET:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 0;
                default:
                    return -1;
                                }

                    case NT_INODE:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 1;
                case 5: return 0;
                default:
                    return -1;
                                }

                    case NT_IPASS:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 0;
                default:
                    return -1;
                                }

                    case NT_ITRAVERSAL:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 1;
                case 5: return 0;
                default:
                    return -1;
                                }

                    case NT_IPHASE:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 1;
                case 5: return 0;
                default:
                    return -1;
                                }

                    case NT_IACTIONS:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 0;
                default:
                    return -1;
                                }

                    case NT_AST:
            switch (idx) {
                case 0: return 1;
                case 1: return 1;
                case 2: return 1;
                case 3: return 1;
                case 4: return 1;
                case 5: return 1;
                case 6: return 1;
                case 7: return 0;
                default:
                    return -1;
                                }

                    default:
            return -1;
                }

}

char *DBGHelper_nodename(enum ccn_nodetype type) {
    switch (type) {
        case NT_ID:
            return "id";
                    case NT_IENUM:
            return "ienum";
                    case NT_ATTRIBUTE:
            return "attribute";
                    case NT_ITRAVDATA:
            return "itravdata";
                    case NT_SETOPERATION:
            return "setoperation";
                    case NT_SETLITERAL:
            return "setliteral";
                    case NT_SETREFERENCE:
            return "setreference";
                    case NT_STE:
            return "ste";
                    case NT_CHILD:
            return "child";
                    case NT_LIFETIME_RANGE:
            return "lifetime_range";
                    case NT_ILIFETIME:
            return "ilifetime";
                    case NT_INODESET:
            return "inodeset";
                    case NT_INODE:
            return "inode";
                    case NT_IPASS:
            return "ipass";
                    case NT_ITRAVERSAL:
            return "itraversal";
                    case NT_IPHASE:
            return "iphase";
                    case NT_IACTIONS:
            return "iactions";
                    case NT_AST:
            return "ast";
                    default:
            return NULL;
                }

}

hist_item **DBGHelper_nodehist(enum ccn_nodetype type, ccn_hist *hist, int idx) {
    switch (type) {
        case NT_ID:
            return (hist_item**)&(HIST_ID(hist)->hist.hist_list[idx]);
                    case NT_IENUM:
            return (hist_item**)&(HIST_IENUM(hist)->hist.hist_list[idx]);
                    case NT_ATTRIBUTE:
            return (hist_item**)&(HIST_ATTRIBUTE(hist)->hist.hist_list[idx]);
                    case NT_ITRAVDATA:
            return (hist_item**)&(HIST_ITRAVDATA(hist)->hist.hist_list[idx]);
                    case NT_SETOPERATION:
            return (hist_item**)&(HIST_SETOPERATION(hist)->hist.hist_list[idx]);
                    case NT_SETLITERAL:
            return (hist_item**)&(HIST_SETLITERAL(hist)->hist.hist_list[idx]);
                    case NT_SETREFERENCE:
            return (hist_item**)&(HIST_SETREFERENCE(hist)->hist.hist_list[idx]);
                    case NT_STE:
            return (hist_item**)&(HIST_STE(hist)->hist.hist_list[idx]);
                    case NT_CHILD:
            return (hist_item**)&(HIST_CHILD(hist)->hist.hist_list[idx]);
                    case NT_LIFETIME_RANGE:
            return (hist_item**)&(HIST_LIFETIME_RANGE(hist)->hist.hist_list[idx]);
                    case NT_ILIFETIME:
            return (hist_item**)&(HIST_ILIFETIME(hist)->hist.hist_list[idx]);
                    case NT_INODESET:
            return (hist_item**)&(HIST_INODESET(hist)->hist.hist_list[idx]);
                    case NT_INODE:
            return (hist_item**)&(HIST_INODE(hist)->hist.hist_list[idx]);
                    case NT_IPASS:
            return (hist_item**)&(HIST_IPASS(hist)->hist.hist_list[idx]);
                    case NT_ITRAVERSAL:
            return (hist_item**)&(HIST_ITRAVERSAL(hist)->hist.hist_list[idx]);
                    case NT_IPHASE:
            return (hist_item**)&(HIST_IPHASE(hist)->hist.hist_list[idx]);
                    case NT_IACTIONS:
            return (hist_item**)&(HIST_IACTIONS(hist)->hist.hist_list[idx]);
                    case NT_AST:
            return (hist_item**)&(HIST_AST(hist)->hist.hist_list[idx]);
                    default:
            return NULL;
                }

}

int DBGHelper_node_numvals(enum ccn_nodetype type) {
    switch (type) {
        case NT_ID:
            return 7;
                    case NT_IENUM:
            return 5;
                    case NT_ATTRIBUTE:
            return 6;
                    case NT_ITRAVDATA:
            return 5;
                    case NT_SETOPERATION:
            return 3;
                    case NT_SETLITERAL:
            return 3;
                    case NT_SETREFERENCE:
            return 1;
                    case NT_STE:
            return 3;
                    case NT_CHILD:
            return 7;
                    case NT_LIFETIME_RANGE:
            return 4;
                    case NT_ILIFETIME:
            return 4;
                    case NT_INODESET:
            return 5;
                    case NT_INODE:
            return 8;
                    case NT_IPASS:
            return 5;
                    case NT_ITRAVERSAL:
            return 7;
                    case NT_IPHASE:
            return 8;
                    case NT_IACTIONS:
            return 3;
                    case NT_AST:
            return 12;
                    default:
            return -1;
                }

}

#endif
