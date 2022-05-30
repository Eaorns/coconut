#pragma once

#include <stdlib.h>
#include <stdbool.h>

extern void *MEMmalloc(size_t size);
extern void *MEMcalloc(size_t size);
extern void *MEMfree(void *address);
extern void *MEMcopy(size_t size, void *mem);

extern void MEMdoQueue(bool queue);
extern void MEMsetAction(size_t action);
extern void *MEMunfree(void *address);
extern void MEMunfreeAction(size_t lwr, size_t upr);
extern void MEMqueueCleanup(size_t lwr, size_t upr);