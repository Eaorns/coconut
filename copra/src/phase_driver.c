#include <ctype.h>
#include <err.h>
#include <palm/str.h>
#include <palm/memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "ccn/action_types.h"
#include "ccn/dynamic_core.h"
#include "ccngen/action_handling.h"
#include "ccngen/debugger_helper.h"
#include "palm/ctinfo.h"
#include "palm/watchpoint.h"
#include "palm/watchpointalloc.h"
#include "ccn/phase_driver.h"
#include "ccn/ccn_dbg.h"

#define ACTION_HIST_REALLOC_AMT 128

struct phase_driver {
    size_t level;
    size_t action_id;
    // Begin used by debugger
    size_t action_ctr;
    ucontext_t *curr_context;
    struct ccn_node *root_node;
    // End used by debugger
    size_t cycle_iter;
    size_t max_cycles;
    size_t breakpoint_id;
    enum pd_verbosity verbosity;
    bool fixed_point;
    bool action_error;
    bool phase_error;
    bool tree_check;
    struct ccn_phase *current_phase;
    char *breakpoint;
};

struct debugger_data {
    enum ccn_action_id *action_hist;
    ucontext_t *context_hist;
    struct phase_driver *phase_driver_hist;
    size_t hist_size;

    struct ccn_node *err_node;
    ucontext_t crash_context;
    bool segfaulting;
    size_t restoring_context;
};

static struct debugger_data debugger_data = {
    .action_hist = NULL,
    .context_hist = NULL,
    .phase_driver_hist = NULL,
    .hist_size = 0,
    .err_node = NULL,
    .crash_context = { 0 },
    .segfaulting = false,
    .restoring_context = (size_t)-1
};

static struct phase_driver phase_driver = {
    .level = 0,
    .action_id = 0,
    .action_ctr = 0,
    .cycle_iter = 0,
    .breakpoint_id = 0,
    .max_cycles = 100,
    .current_phase = NULL,
    .fixed_point = false,
    .action_error = false,
    .phase_error = false,
    .tree_check = true,
    .verbosity = PD_V_QUIET,
    .breakpoint = NULL,
};

static void resetPhaseDriver()
{
    debugger_data.action_hist = MEMfree(debugger_data.action_hist);
    debugger_data.context_hist = MEMfree(debugger_data.context_hist);
    debugger_data.phase_driver_hist = MEMfree(debugger_data.phase_driver_hist);
    debugger_data.hist_size = 0;
    debugger_data.err_node = NULL;
    debugger_data.crash_context = (ucontext_t){ 0 };
    debugger_data.segfaulting = false;
    debugger_data.restoring_context = (size_t)-1;
    
    phase_driver.level = 0;
    phase_driver.action_id = 0;
    phase_driver.action_ctr = 0;
    phase_driver.cycle_iter = 0;
    phase_driver.current_phase = NULL;
    phase_driver.fixed_point = false;
    phase_driver.action_error = false;
    phase_driver.phase_error = false;
}

static struct ccn_node *StartPhase(struct ccn_phase *phase, char *phase_name, struct ccn_node *node);

extern void BreakpointHandler(node_st *node);

struct ccn_node *CCNdispatchAction(struct ccn_action *action, enum ccn_nodetype root_type, struct ccn_node *node,
                          bool is_root) {
    phase_driver.action_id++;
    phase_driver.root_node = node;
    if (debugger_data.hist_size <= ++phase_driver.action_ctr) {
        debugger_data.hist_size += ACTION_HIST_REALLOC_AMT;
        // TODO replace realloc with memory.h function
        debugger_data.action_hist = realloc(debugger_data.action_hist, debugger_data.hist_size * sizeof(enum ccn_action_id));  
        debugger_data.context_hist = realloc(debugger_data.context_hist, debugger_data.hist_size * sizeof(ucontext_t));
        debugger_data.phase_driver_hist = realloc(debugger_data.phase_driver_hist, debugger_data.hist_size * sizeof(struct phase_driver));
    }
    debugger_data.action_hist[phase_driver.action_ctr] = action->action_id;
    memcpy(&(debugger_data.phase_driver_hist[phase_driver.action_ctr]), &phase_driver, sizeof(struct phase_driver));
    getcontext(&(debugger_data.context_hist[phase_driver.action_ctr]));
    phase_driver.curr_context = &(debugger_data.context_hist[phase_driver.action_ctr]);

    if (debugger_data.restoring_context != (size_t)-1) {
        memcpy(&phase_driver, &(debugger_data.phase_driver_hist[debugger_data.restoring_context]), sizeof(struct phase_driver));
        debugger_data.restoring_context = (size_t)-1;

        if (debugger_data.err_node != NULL)
            CCNdebug(debugger_data.err_node);
        else
            CCNdebug(phase_driver.root_node);

        debugger_data.segfaulting = false;
    }

    printf("asdfasdfasdfasdf\n");

    // Needed to break after a phase with action ids.
    size_t start_id = phase_driver.action_id;

    if (action->type == CCN_ACTION_PHASE && phase_driver.verbosity > PD_V_QUIET) {
        fprintf(stderr, ">> %s\n", action->name);
    } else {
        if (phase_driver.verbosity > PD_V_SMALL) {
            fprintf(stderr, "  *** %s\n", action->name);
        }
    }

    if (phase_driver.tree_check) {
        int curr_err = CTIgetErrors();
        node = TRAVstart(node, TRAV_check);
        if (CTIgetErrors() != curr_err) {
            CTIabortOnError();
        }
    }

    bool phase_error = false;
    switch (action->type) {
    case CCN_ACTION_PASS:
        node = PASSstart(node, action->pass.pass_type);
        break;
    case CCN_ACTION_TRAVERSAL:
        node = TRAVstart(node, action->traversal.trav_type);
        break;
    case CCN_ACTION_PHASE:
        phase_error = phase_driver.phase_error;
        phase_driver.phase_error = false;
        node = StartPhase(&(action->phase), action->name, node);
        phase_driver.phase_error = phase_error || phase_driver.phase_error;
        break;
    case CCN_ACTION_NULL:
        err(EXIT_FAILURE, "[coconut] error in phase driver.");
    }
    if (phase_driver.action_error) {
        fprintf(stderr, "[coconut] Action error received. Stopping...\n");
        CTIabortCompilation();
    }

    if (phase_driver.breakpoint) {
        if (STReqci(phase_driver.breakpoint, action->name)) {
            BreakpointHandler(node);
            exit(0);
        }
    }
    if (phase_driver.breakpoint_id > 0 && phase_driver.breakpoint_id == start_id) {
        BreakpointHandler(node);
        exit(0);
    }
    if (action->type == CCN_ACTION_PHASE && phase_driver.verbosity > PD_V_QUIET) {
        fprintf(stderr, "<< %s\n", action->name);
    }

    (void)root_type;
    (void)is_root;
    return node;
}

/* Moves action counter used by lifetimes forward when we skip. */
static void SkipPhase(struct ccn_phase *phase) {
    size_t action_counter = 0;
    enum ccn_action_id action_id = phase->action_table[action_counter];
    while (action_id != CCNAC_ID_NULL) {
        phase_driver.action_id++;
        {
            struct ccn_action *action = CCNgetActionFromID(action_id);
            if (action->type == CCN_ACTION_PHASE) {
                SkipPhase(&(action->phase));
            }
        }
        action_counter++;
        action_id = phase->action_table[action_counter];
    }
}

char *Checkbreakpoint(char *name)
{
    int len = STRlen(name);
    for (int i = 0; i < len; i++) {
        if (phase_driver.breakpoint[i] == '\0') {
            return NULL;
        }
        if (tolower(name[i]) != tolower(phase_driver.breakpoint[i])) {
            return NULL;
        }
    }
    // Handled by the action start.
    if (STRlen(phase_driver.breakpoint) == len) {
        return NULL;
    }
    if (phase_driver.breakpoint[len] == '.') {
        if (phase_driver.breakpoint[len + 1] == '\0') {
            fprintf(stderr, "[coconut] breakpoint string is invalid.\n");
            return NULL;
        }
        return phase_driver.breakpoint + len + 1;
    }

    return NULL;
}

struct ccn_node *StartPhase(struct ccn_phase *phase, char *phase_name, struct ccn_node *node) {
    if (phase->gate_func && !phase->gate_func()) {
        if (phase_driver.verbosity >= PD_V_HIGH) {
            fprintf(stderr, "[coconut] Skipping phase %s because gate function returned false.\n", phase_name);
        }
        SkipPhase(phase);
        return node;
    }

    char *old_break = NULL;
    if (phase_driver.breakpoint) {
        char *new_break = Checkbreakpoint(phase_name);
        if (new_break != NULL) {
            old_break = phase_driver.breakpoint;
            phase_driver.breakpoint = new_break;
        }
    }

    struct ccn_phase *prev = phase_driver.current_phase;
    phase_driver.current_phase = phase;
    phase_driver.level++;
    bool cycle = phase->is_cycle;
    uint64_t curr_action_id = phase_driver.action_id;

    do {
        // If we cycle around, reset the action id.
        phase_driver.fixed_point = true;
        phase_driver.action_id = curr_action_id;
        size_t action_counter = 0;
        enum ccn_action_id action_id = phase->action_table[action_counter];
        while (action_id != CCNAC_ID_NULL) {
            struct ccn_action *action = CCNgetActionFromID(action_id);
            node = CCNdispatchAction(action, phase->root_type, node, false);
            action_counter++;
            action_id = phase->action_table[action_counter];
        }
        phase_driver.cycle_iter++;
    } while(cycle && phase_driver.cycle_iter < phase_driver.max_cycles && !(phase_driver.fixed_point));

    if (phase_driver.phase_error) {
        fprintf(stderr, "[coconut] Phase error received. Stopping...\n");
        CTIabortCompilation();
    }

    phase_driver.cycle_iter = 0;
    phase_driver.level--;

    phase_driver.current_phase = prev;
    if (old_break != NULL) {
        phase_driver.breakpoint = old_break;
    }
    return node;
}

/**
 * Notify CoCoNut that a fixed point is not reached in current cycle.
 */
void CCNcycleNotify()
{
    phase_driver.fixed_point = false;
}

/**
 * Signal an action error. CoCoNut will call CTIabortCompilation
 * after the action this error was signalled in.
 */
void CCNerrorAction()
{
    phase_driver.action_error = true;
}

/**
 * Signal an phase error. As a result, CoCoNut will call CTIabortCompilation
 * at the end of the phase this error was signalled in.
 */
void CCNerrorPhase()
{
    phase_driver.phase_error = true;
}

/**
 * Set the maximum number of cycles for a cycle. Can be changed at runtime.
 * @param cycle_count the maximum number of cycles.
 */
void CCNsetCycles(size_t cycle_count)
{
    phase_driver.max_cycles = cycle_count;
}

/**
 * Set a breakpoint at which CoCoNut will stop and call the handler:
 * *BreakpointHandler*.
 * @param breakpoint The breakpoint in format: <phase>.<phase>.<action>
 */
void CCNsetBreakpoint(char *breakpoint)
{
    phase_driver.breakpoint = breakpoint;
}

void CCNsetBreakpointWithID(size_t id)
{
    phase_driver.breakpoint_id = id;
}

/**
 * Set the verbosity level of CoCoNut.
 * @param type the type of verbosity.
 */
void CCNsetVerbosity(enum pd_verbosity type)
{
    phase_driver.verbosity = type;
}

/**
 * Enable or disable consistency checking your tree.
 * @param enable when true, consistency checking is performed.
 */
void CCNsetTreeCheck(bool enable)
{
    phase_driver.tree_check = enable;
}

void sighandler_sigsegv(int signo __attribute__((unused)), siginfo_t *info, void *vcontext)
{
    if (debugger_data.segfaulting) {
        fprintf(stderr, "Non-recoverable segmentation fault! Exiting...\n\n");
        struct sigaction actsegv = { 0 };
        actsegv.sa_handler = SIG_DFL;
        sigaction(SIGSEGV, &actsegv, NULL);
        return;
    }
    
    debugger_data.segfaulting = true;

    memcpy(&(debugger_data.crash_context), vcontext, sizeof(ucontext_t));

    // find problematic node, if present
    debugger_data.err_node = NULL;
    if (info->si_addr != NULL) {
        node_st **node_tracker_list = get_node_tracker_list();
        void *field_ptr;
        bool done = false;
        for (size_t i = 0; !done && i < get_node_id_counter(); i++) {
            for (int j = 0; (field_ptr = DBGHelper_getptr(node_tracker_list[i], j)) != NULL; j++) {
                if (field_ptr == info->si_addr) {
                    debugger_data.err_node = node_tracker_list[i];
                    done = true;
                }
            }
        }
    }

    debugger_data.restoring_context = phase_driver.action_ctr;
    setcontext(phase_driver.curr_context);
}

/**
 * Perform an invocation of your compiler.
 * @param node the root of the tree. Will call the free traversal at the end.
 */
void CCNrun(struct ccn_node *node)
{
    /* Register SIGSEGV handler */
    struct sigaction actsegv = { 0 };
    actsegv.sa_flags = SA_SIGINFO;
    actsegv.sa_sigaction = &sighandler_sigsegv;
    sigaction(SIGSEGV, &actsegv, NULL);

    resetPhaseDriver();
    watchpoint_init();
    wpalloc_init();

    watchpoint_set_default_sigsegvhandler(&actsegv);

    phase_driver.root_node = node;
    node = CCNdispatchAction(CCNgetActionFromID(CCN_ROOT_ACTION), CCN_ROOT_TYPE, node, false);
    CCNdebug(node);
    
    watchpoint_fini();
    TRAVstart(node, TRAV_free);
    wpalloc_fini();
    MEMfree(debugger_data.action_hist);
    MEMfree(debugger_data.context_hist);
    MEMfree(debugger_data.phase_driver_hist);
}

size_t CCNgetCurrentActionId()
{
    return phase_driver.action_id;
}

size_t CCNgetCurrentActionCtr()
{
    return phase_driver.action_ctr;
}

enum ccn_action_id *CCNgetActionHist()
{
    return debugger_data.action_hist;
}

struct ccn_node *CCNgetRootNode()
{
    return phase_driver.root_node;
}

bool CCNisSegfaulting()
{
    return debugger_data.segfaulting;
}

void CCNstopSegfaulting()
{
    debugger_data.segfaulting = false;
}

ucontext_t *CCNgetCurrContext()
{
    return phase_driver.curr_context;
}

ucontext_t *CCNgetCrashContext() 
{
    return &(debugger_data.crash_context);
}

static
size_t ShowTree(struct ccn_action *curr, size_t id, int indent)
{
    if (id > 1) {
        for (int i = 0; i < indent; i++) {
            printf("\t");
        }
        printf("%ld: %s\n", id, curr->name);
    }
    id++;
    if (curr->type != CCN_ACTION_PHASE) {
        return id;
    }

    size_t index = 0;
    struct ccn_phase *phase = &curr->phase;
    indent++;
    while (phase->action_table[index] != CCNAC_ID_NULL) {
        id = ShowTree(CCNgetActionFromID(phase->action_table[index]), id, indent);
        index++;
    }
    printf("\n");
    indent--;
    return id;
}

/**
 * Gives a structured representation of your compiler structure.
 */
void CCNshowTree()
{
    ShowTree(CCNgetActionFromID(CCN_ROOT_ACTION), 1, -1);
}
