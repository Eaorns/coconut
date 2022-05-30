#include "palm/memory.h"

#include <stdlib.h>
#include <string.h>

#include "palm/dbug.h"
#include "palm/ctinfo.h"


typedef struct free_queue {
    void *ptr;
    size_t action;
    struct free_queue *next;
} free_queue;

bool queue_freeing = true;
size_t curr_action = 0;
free_queue *queue = NULL;

void MEMdoQueue(bool queue)
{
    queue_freeing = queue;
}

void MEMsetAction(size_t action)
{
    curr_action = action;
}

void MEMunfreeAction(size_t lwr, size_t upr)
{
    free_queue *prev, *curr = queue;
    while (curr) {
        if (curr->action >= lwr && curr->action <= upr) {
            if (prev == NULL) 
                queue = curr->next;
            else
                prev->next = curr->next;

            free(curr);
            
            if (prev == NULL)
                curr = queue;
            else
                curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void *MEMunfree(void *address)
{
    free_queue *prev, *curr = queue;
    while (curr) {
        if (curr->ptr == address) {
            if (prev == NULL)
                queue = curr->next;
            else
                prev->next = curr->next;
            free(curr);
            return address;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void MEMqueueCleanup(size_t lwr, size_t upr)
{
    free_queue *next, *item = queue;
    while (item) {
        next = item->next;
        if (item->action >= lwr && item->action <= upr) {
            free(item->ptr);
            if (item == queue)
                queue = next;
            free(item);
        }
        item = next;
    }
}


/**
 * Allocate memory. If memory can not be allocated this function
 * calls the CTIabortOufOfMemory function and exists.
 * @param size Amount to allocate.
 * @return A pointer to an allocated structure.
 */
void *MEMmalloc(size_t size)
{
    void *ptr;

    DBUG_ASSERT((size >= 0), "called with negative size!");

    if (size > 0) {
        /*
        * Since some UNIX system (e.g. ALPHA) do return NULL for size 0 as well
        * we do complain for ((NULL == tmp) && (size > 0)) only!!
        */
        ptr = malloc(size);

        if (ptr == NULL) {
            CTIabortOutOfMemory(size);
        }
    }
    else {
        ptr = NULL;
    }

    return ptr;
}

/**
 * Allocate memory. If memory can not be allocated this function
 * calls the CTIabortOufOfMemory function and exists.
 * @param size Amount to allocate.
 * @return A pointer to an allocated structure.
 */
void *MEMcalloc(size_t size)
{
    void *ptr;

    DBUG_ASSERT((size >= 0), "called with negative size!");

    if (size > 0) {
        /*
        * Since some UNIX system (e.g. ALPHA) do return NULL for size 0 as well
        * we do complain for ((NULL == tmp) && (size > 0)) only!!
        */
        ptr = calloc(size, 1);

        if (ptr == NULL) {
            CTIabortOutOfMemory(size);
        }
    }
    else {
        ptr = NULL;
    }

    return ptr;
}

/**
 * Free memory. Returns NULL, but allows to do assignment to freed structure.
 * @param address address to free.
 */
void *MEMfree(void *address)
{
    if(address != NULL) {
        if (queue_freeing) {
            free_queue *item = MEMmalloc(sizeof(free_queue));
            item->ptr = address;
            item->action = curr_action;
            item->next = queue;
            queue = item;
        } else {
            free(address);
        }
        address = NULL;
    }

    return address;
}

void *MEMcopy(size_t size, void *mem)
{
    void *result;

    result = MEMmalloc(size);
    result = memcpy(result, mem, size);

    return result;
}
