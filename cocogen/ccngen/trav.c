#include <stdbool.h>
#include "palm/dbug.h"
#include "ccn/ccn.h"
#include "ccngen/ast.h"
node_st *TRAVlifetimes(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_INODE:
            res = TRAVopt(INODE_LIFETIMES(node));
            if (INODE_LIFETIMES(node) != res) {
                INODE_LIFETIMES(node) = res;
            }

            break;
            break;
        case NT_CHILD:
            res = TRAVopt(CHILD_LIFETIMES(node));
            if (CHILD_LIFETIMES(node) != res) {
                CHILD_LIFETIMES(node) = res;
            }

            break;
            break;
        case NT_ATTRIBUTE:
            res = TRAVopt(ATTRIBUTE_LIFETIMES(node));
            if (ATTRIBUTE_LIFETIMES(node) != res) {
                ATTRIBUTE_LIFETIMES(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child lifetimes");
            break;
    }

    return node;
}

node_st *TRAVinodes(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_INODES(node));
            if (AST_INODES(node) != res) {
                AST_INODES(node) = res;
            }

            break;
            break;
        case NT_ITRAVERSAL:
            res = TRAVopt(ITRAVERSAL_INODES(node));
            if (ITRAVERSAL_INODES(node) != res) {
                ITRAVERSAL_INODES(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child inodes");
            break;
    }

    return node;
}

node_st *TRAVdata(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_ITRAVERSAL:
            res = TRAVopt(ITRAVERSAL_DATA(node));
            if (ITRAVERSAL_DATA(node) != res) {
                ITRAVERSAL_DATA(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child data");
            break;
    }

    return node;
}

node_st *TRAViactions(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IPHASE:
            res = TRAVopt(IPHASE_IACTIONS(node));
            if (IPHASE_IACTIONS(node) != res) {
                IPHASE_IACTIONS(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child iactions");
            break;
    }

    return node;
}

node_st *TRAVipasses(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_IPASSES(node));
            if (AST_IPASSES(node) != res) {
                AST_IPASSES(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child ipasses");
            break;
    }

    return node;
}

node_st *TRAVinodesets(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_INODESETS(node));
            if (AST_INODESETS(node) != res) {
                AST_INODESETS(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child inodesets");
            break;
    }

    return node;
}

node_st *TRAVreference(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IACTIONS:
            res = TRAVopt(IACTIONS_REFERENCE(node));
            if (IACTIONS_REFERENCE(node) != res) {
                IACTIONS_REFERENCE(node) = res;
            }

            break;
            break;
        case NT_SETREFERENCE:
            res = TRAVopt(SETREFERENCE_REFERENCE(node));
            if (SETREFERENCE_REFERENCE(node) != res) {
                SETREFERENCE_REFERENCE(node) = res;
            }

            break;
            break;
        case NT_SETLITERAL:
            res = TRAVopt(SETLITERAL_REFERENCE(node));
            if (SETLITERAL_REFERENCE(node) != res) {
                SETLITERAL_REFERENCE(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child reference");
            break;
    }

    return node;
}

node_st *TRAVtarget(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_LIFETIME_RANGE:
            res = TRAVopt(LIFETIME_RANGE_TARGET(node));
            if (LIFETIME_RANGE_TARGET(node) != res) {
                LIFETIME_RANGE_TARGET(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child target");
            break;
    }

    return node;
}

node_st *TRAVbegin(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_ILIFETIME:
            res = TRAVopt(ILIFETIME_BEGIN(node));
            if (ILIFETIME_BEGIN(node) != res) {
                ILIFETIME_BEGIN(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child begin");
            break;
    }

    return node;
}

node_st *TRAVstable(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_STABLE(node));
            if (AST_STABLE(node) != res) {
                AST_STABLE(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child stable");
            break;
    }

    return node;
}

node_st *TRAVgate_func(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IPHASE:
            res = TRAVopt(IPHASE_GATE_FUNC(node));
            if (IPHASE_GATE_FUNC(node) != res) {
                IPHASE_GATE_FUNC(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child gate_func");
            break;
    }

    return node;
}

node_st *TRAVend(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_ILIFETIME:
            res = TRAVopt(ILIFETIME_END(node));
            if (ILIFETIME_END(node) != res) {
                ILIFETIME_END(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child end");
            break;
    }

    return node;
}

node_st *TRAVunpacked(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_INODESET:
            res = TRAVopt(INODESET_UNPACKED(node));
            if (INODESET_UNPACKED(node) != res) {
                INODESET_UNPACKED(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child unpacked");
            break;
    }

    return node;
}

node_st *TRAVichildren(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_INODE:
            res = TRAVopt(INODE_ICHILDREN(node));
            if (INODE_ICHILDREN(node) != res) {
                INODE_ICHILDREN(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child ichildren");
            break;
    }

    return node;
}

node_st *TRAVVals(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IENUM:
            res = TRAVopt(IENUM_VALS(node));
            if (IENUM_VALS(node) != res) {
                IENUM_VALS(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child Vals");
            break;
    }

    return node;
}

node_st *TRAVnext(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IACTIONS:
            res = TRAVopt(IACTIONS_NEXT(node));
            if (IACTIONS_NEXT(node) != res) {
                IACTIONS_NEXT(node) = res;
            }

            break;
            break;
        case NT_IPHASE:
            res = TRAVopt(IPHASE_NEXT(node));
            if (IPHASE_NEXT(node) != res) {
                IPHASE_NEXT(node) = res;
            }

            break;
            break;
        case NT_ITRAVERSAL:
            res = TRAVopt(ITRAVERSAL_NEXT(node));
            if (ITRAVERSAL_NEXT(node) != res) {
                ITRAVERSAL_NEXT(node) = res;
            }

            break;
            break;
        case NT_IPASS:
            res = TRAVopt(IPASS_NEXT(node));
            if (IPASS_NEXT(node) != res) {
                IPASS_NEXT(node) = res;
            }

            break;
            break;
        case NT_INODE:
            res = TRAVopt(INODE_NEXT(node));
            if (INODE_NEXT(node) != res) {
                INODE_NEXT(node) = res;
            }

            break;
            break;
        case NT_INODESET:
            res = TRAVopt(INODESET_NEXT(node));
            if (INODESET_NEXT(node) != res) {
                INODESET_NEXT(node) = res;
            }

            break;
            break;
        case NT_ILIFETIME:
            res = TRAVopt(ILIFETIME_NEXT(node));
            if (ILIFETIME_NEXT(node) != res) {
                ILIFETIME_NEXT(node) = res;
            }

            break;
            break;
        case NT_CHILD:
            res = TRAVopt(CHILD_NEXT(node));
            if (CHILD_NEXT(node) != res) {
                CHILD_NEXT(node) = res;
            }

            break;
            break;
        case NT_STE:
            res = TRAVopt(STE_NEXT(node));
            if (STE_NEXT(node) != res) {
                STE_NEXT(node) = res;
            }

            break;
            break;
        case NT_ITRAVDATA:
            res = TRAVopt(ITRAVDATA_NEXT(node));
            if (ITRAVDATA_NEXT(node) != res) {
                ITRAVDATA_NEXT(node) = res;
            }

            break;
            break;
        case NT_ATTRIBUTE:
            res = TRAVopt(ATTRIBUTE_NEXT(node));
            if (ATTRIBUTE_NEXT(node) != res) {
                ATTRIBUTE_NEXT(node) = res;
            }

            break;
            break;
        case NT_IENUM:
            res = TRAVopt(IENUM_NEXT(node));
            if (IENUM_NEXT(node) != res) {
                IENUM_NEXT(node) = res;
            }

            break;
            break;
        case NT_ID:
            res = TRAVopt(ID_NEXT(node));
            if (ID_NEXT(node) != res) {
                ID_NEXT(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child next");
            break;
    }

    return node;
}

node_st *TRAVname(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IPHASE:
            res = TRAVopt(IPHASE_NAME(node));
            if (IPHASE_NAME(node) != res) {
                IPHASE_NAME(node) = res;
            }

            break;
            break;
        case NT_ITRAVERSAL:
            res = TRAVopt(ITRAVERSAL_NAME(node));
            if (ITRAVERSAL_NAME(node) != res) {
                ITRAVERSAL_NAME(node) = res;
            }

            break;
            break;
        case NT_IPASS:
            res = TRAVopt(IPASS_NAME(node));
            if (IPASS_NAME(node) != res) {
                IPASS_NAME(node) = res;
            }

            break;
            break;
        case NT_INODE:
            res = TRAVopt(INODE_NAME(node));
            if (INODE_NAME(node) != res) {
                INODE_NAME(node) = res;
            }

            break;
            break;
        case NT_INODESET:
            res = TRAVopt(INODESET_NAME(node));
            if (INODESET_NAME(node) != res) {
                INODESET_NAME(node) = res;
            }

            break;
            break;
        case NT_CHILD:
            res = TRAVopt(CHILD_NAME(node));
            if (CHILD_NAME(node) != res) {
                CHILD_NAME(node) = res;
            }

            break;
            break;
        case NT_ITRAVDATA:
            res = TRAVopt(ITRAVDATA_NAME(node));
            if (ITRAVDATA_NAME(node) != res) {
                ITRAVDATA_NAME(node) = res;
            }

            break;
            break;
        case NT_ATTRIBUTE:
            res = TRAVopt(ATTRIBUTE_NAME(node));
            if (ATTRIBUTE_NAME(node) != res) {
                ATTRIBUTE_NAME(node) = res;
            }

            break;
            break;
        case NT_IENUM:
            res = TRAVopt(IENUM_NAME(node));
            if (IENUM_NAME(node) != res) {
                IENUM_NAME(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child name");
            break;
    }

    return node;
}

node_st *TRAVleft(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_SETLITERAL:
            res = TRAVopt(SETLITERAL_LEFT(node));
            if (SETLITERAL_LEFT(node) != res) {
                SETLITERAL_LEFT(node) = res;
            }

            break;
            break;
        case NT_SETOPERATION:
            res = TRAVopt(SETOPERATION_LEFT(node));
            if (SETOPERATION_LEFT(node) != res) {
                SETOPERATION_LEFT(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child left");
            break;
    }

    return node;
}

node_st *TRAVtype_reference(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_CHILD:
            res = TRAVopt(CHILD_TYPE_REFERENCE(node));
            if (CHILD_TYPE_REFERENCE(node) != res) {
                CHILD_TYPE_REFERENCE(node) = res;
            }

            break;
            break;
        case NT_ITRAVDATA:
            res = TRAVopt(ITRAVDATA_TYPE_REFERENCE(node));
            if (ITRAVDATA_TYPE_REFERENCE(node) != res) {
                ITRAVDATA_TYPE_REFERENCE(node) = res;
            }

            break;
            break;
        case NT_ATTRIBUTE:
            res = TRAVopt(ATTRIBUTE_TYPE_REFERENCE(node));
            if (ATTRIBUTE_TYPE_REFERENCE(node) != res) {
                ATTRIBUTE_TYPE_REFERENCE(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child type_reference");
            break;
    }

    return node;
}

node_st *TRAViphases(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_IPHASES(node));
            if (AST_IPHASES(node) != res) {
                AST_IPHASES(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child iphases");
            break;
    }

    return node;
}

node_st *TRAVright(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_SETLITERAL:
            res = TRAVopt(SETLITERAL_RIGHT(node));
            if (SETLITERAL_RIGHT(node) != res) {
                SETLITERAL_RIGHT(node) = res;
            }

            break;
            break;
        case NT_SETOPERATION:
            res = TRAVopt(SETOPERATION_RIGHT(node));
            if (SETOPERATION_RIGHT(node) != res) {
                SETOPERATION_RIGHT(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child right");
            break;
    }

    return node;
}

node_st *TRAViattributes(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_INODE:
            res = TRAVopt(INODE_IATTRIBUTES(node));
            if (INODE_IATTRIBUTES(node) != res) {
                INODE_IATTRIBUTES(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child iattributes");
            break;
    }

    return node;
}

node_st *TRAViprefix(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IPHASE:
            res = TRAVopt(IPHASE_IPREFIX(node));
            if (IPHASE_IPREFIX(node) != res) {
                IPHASE_IPREFIX(node) = res;
            }

            break;
            break;
        case NT_ITRAVERSAL:
            res = TRAVopt(ITRAVERSAL_IPREFIX(node));
            if (ITRAVERSAL_IPREFIX(node) != res) {
                ITRAVERSAL_IPREFIX(node) = res;
            }

            break;
            break;
        case NT_IPASS:
            res = TRAVopt(IPASS_IPREFIX(node));
            if (IPASS_IPREFIX(node) != res) {
                IPASS_IPREFIX(node) = res;
            }

            break;
            break;
        case NT_IENUM:
            res = TRAVopt(IENUM_IPREFIX(node));
            if (IENUM_IPREFIX(node) != res) {
                IENUM_IPREFIX(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child iprefix");
            break;
    }

    return node;
}

node_st *TRAVexpr(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_INODESET:
            res = TRAVopt(INODESET_EXPR(node));
            if (INODESET_EXPR(node) != res) {
                INODESET_EXPR(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child expr");
            break;
    }

    return node;
}

node_st *TRAVtarget_func(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_IPASS:
            res = TRAVopt(IPASS_TARGET_FUNC(node));
            if (IPASS_TARGET_FUNC(node) != res) {
                IPASS_TARGET_FUNC(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child target_func");
            break;
    }

    return node;
}

node_st *TRAVenums(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_ENUMS(node));
            if (AST_ENUMS(node) != res) {
                AST_ENUMS(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child enums");
            break;
    }

    return node;
}

node_st *TRAVitraversals(node_st *node) {
    node_st *res;
    switch (NODE_TYPE(node)) {
        case NT_AST:
            res = TRAVopt(AST_ITRAVERSALS(node));
            if (AST_ITRAVERSALS(node) != res) {
                AST_ITRAVERSALS(node) = res;
            }

            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child itraversals");
            break;
    }

    return node;
}

