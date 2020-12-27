#include "gen_helpers/out_macros.h"
#include "ccn/dynamic_core.h"
#include "gen_helpers/format.h"
#include "globals.h"

node_st *DGTDGitraversal(node_st *node)
{
    if (ITRAVERSAL_DATA(node)) {
        FILE *fp = globals.fp;
        int indent = 0;
        node_st *id =  ITRAVERSAL_IPREFIX(node);

        OUT("#define DATA_%s_GET() (TRAVgetCurrent()->trav_data.%s)\n",
            ID_UPR(id), ID_LWR(ITRAVERSAL_NAME(node)));
    }

    TRAVopt(ITRAVERSAL_NEXT(node));
    return node;
}
