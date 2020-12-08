#pragma once
enum ccn_action_id {
    CCNAC_ID_DYNAMIC_GEN_AST,
    CCNAC_ID_DYNAMIC_GEN_TRAV_DATA,
    CCNAC_ID_DYNAMIC_BACKEND,
    CCNAC_ID_PHASE_DRIVER,
    CCNAC_ID_UNPACK_LIFETIMES,
    CCNAC_ID_SEMANTIC,
    CCNAC_ID_STARTPHASE,
    CCNAC_ID_PRINT,
    CCNAC_ID_SETLITERALCONTAINS,
    CCNAC_ID_SETLITERALDIFFERENCE,
    CCNAC_ID_SETLITERALINTERSECT,
    CCNAC_ID_SETLITERALUNION,
    CCNAC_ID_SETLITERALINSERT,
    CCNAC_ID_REACHABILITY,
    CCNAC_ID_UNWRAPSETEXPR,
    CCNAC_ID_BUILDSYMBOLTABLE,
    CCNAC_ID_CHECKEXISTANCE,
    CCNAC_ID_DYNAMIC_GENNODEMACROS,
    CCNAC_ID_DYNAMIC_GENNODESTRUCTS,
    CCNAC_ID_DYNAMIC_GENNODEINITFUNCTIONS,
    CCNAC_ID_DYNAMIC_GENNODEUNION,
    CCNAC_ID_DYNAMIC_GENNODECONSTRUCTOR,
    CCNAC_ID_DYNAMIC_GENENUM,
    CCNAC_ID_DYNAMIC_GENENUMVALUES,
    CCNAC_ID_DYNAMIC_GENTRAVVTABLE,
    CCNAC_ID_DYNAMIC_GENNODESFORTRAVTABLE,
    CCNAC_ID_DYNAMIC_GENPASSTABLE,
    CCNAC_ID_DYNAMIC_GENTRAVTABLE,
    CCNAC_ID_DYNAMIC_GENSYSTEMTRAVERSALS,
    CCNAC_ID_DYNAMIC_GENACTIONSHEADER,
    CCNAC_ID_DYNAMIC_GENTRAVACTIONS,
    CCNAC_ID_DYNAMIC_GENCOPYTRAVERSAL,
    CCNAC_ID_DYNAMIC_GENCONSTRUCTORCALL,
    CCNAC_ID_DYNAMIC_GENFREETRAVERSAL,
    CCNAC_ID_DYNAMIC_GENCHECKTRAVERSAL,
    CCNAC_ID_DYNAMIC_GENTRAVDATASTRUCTS,
    CCNAC_ID_DYNAMIC_GENTRAVDATACTORS,
    CCNAC_ID_DYNAMIC_GENTRAVDATACTORSHEADER,
    CCNAC_ID_DYNAMIC_GENTRAVDATAGETTERS,
    CCNAC_ID_DYNAMIC_GENTRAVDATAUNION,
    CCNAC_ID_GEN_ACTION_ARRAY,
    CCNAC_ID_GEN_ACTION_ARRAY_HEADER,
    CCNAC_ID_GEN_IDS_TABLES,
    CCNAC_ID_GEN_GATE_HEADER,
    CCNAC_ID_DYNAMIC_GENTRAVDATATABLES,
    CCNAC_ID_GEN_DOT,
    CCNAC_ID_MAP_ID_TO_LIFETIME,
    CCNAC_ID_ASSIGN_ID_TO_ACTION,
    CCNAC_ID_DYNAMIC_GENBASENODEINIT,
    CCNAC_ID_DYNAMIC_SWITCH_TO_AST_SOURCE,
    CCNAC_ID_DYNAMIC_GENBASENODE,
    CCNAC_ID_DYNAMIC_START_AST_HEADER,
    CCNAC_ID_DYNAMIC_SWITCH_TRAV_DATA,
    CCNAC_ID_DYNAMIC_START_TRAV_DATA,
    CCNAC_ID_DYNAMIC_START_TABLE_GEN,
    CCNAC_ID_DYNAMIC_START_ENUM_HEADER,
    CCNAC_ID_SCANANDPARSE,
    CCNAC_ID_check,
    CCNAC_ID_free,
    CCNAC_ID_cleanup,
    CCNAC_ID_NULL,
};

#ifndef CCN_NUM_OF_ACTIONS
#define CCN_NUM_OF_ACTIONS 60
#endif
#ifndef CCN_ROOT_TYPE
#define CCN_ROOT_TYPE NT_AST
#endif
#ifndef CCN_ROOT_ACTION
#define CCN_ROOT_ACTION CCNAC_ID_STARTPHASE
#endif

