#include <signal.h>

#define WP_DISABLE
// #define DO_WP_DEBUG

int watchpoint_init();
int watchpoint_fini();
/* The handler function takes the address of the triggered
 * watchpoint, the old value, a pointer to the ucontext,
 * and user_data. */
int watchpoint_add(void *addr, void (*handler)(void*, void*, void*, void*), void *user_data);
int watchpoint_rem(void *addr);


void watchpoint_disable_all();
void watchpoint_enable_all();

void watchpoint_set_default_sigsegvhandler(struct sigaction *sighandler);
void watchpoint_restore_sighandler();