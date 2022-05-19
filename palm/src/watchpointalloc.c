#include "palm/watchpointalloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

// #define DO_WPA_DEBUG
#ifdef DO_WPA_DEBUG
#define WPA_DEBUG printf
#else
#define WPA_DEBUG(...) while (0) {}
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE sysconf(_SC_PAGE_SIZE)
#endif

/* Increase this if fragmentation of pages triggers ENOMEM (see man mprotect(2)) */
#define PAGE_GROUP_SIZE 1
#define PAGE_ALLOC_SIZE (PAGE_GROUP_SIZE * PAGE_SIZE)

#define RECENT_ALLOC_AMT 8

// #define ALLOC_TABLE_SIZE 4096
#define ALLOC_TABLE_SIZE 2048
#define ALLOC_TABLE_BASE(addr) ((long)addr % ALLOC_TABLE_SIZE)

typedef struct apage {
    void *base;
    size_t size;
    size_t offset;
    size_t left;
    int allocs;
    struct apage *next;
} wpa_page;

typedef struct aalloc {
    void *addr;
    size_t size;
    wpa_page *page;
    struct aalloc *next;
} wpa_alloc;

wpa_page **alloc_candidates;
wpa_alloc **alloc_table;

int wpalloc_init()
{
    alloc_candidates = malloc(sizeof(void*) * RECENT_ALLOC_AMT);
    alloc_table = malloc(sizeof(void*) * ALLOC_TABLE_SIZE);

    return 0;
}

int wpalloc_fini()
{
    wpa_alloc *curr, *next;
    for (int i = 0; i < ALLOC_TABLE_SIZE; i++) {
        // printf("[!] Freeing table entry %i\n", i);
        curr = alloc_table[i];
        while (curr != NULL) {
            // TODO this generates SIGSEGV with ALLOC_TABLE_SIZE 4096????
            // printf("[!] Freeing entry %p...\n", curr);
            next = curr->next;
            curr->page->allocs--;
            if (curr->page->allocs == 0) {
                // printf("[!] Unmapping...\n");
                munmap(curr->page->base, curr->page->size);
                free(curr->page);
            }
            free(curr);
            curr = next;
        }
        // printf("[!] Done with %i!\n", i);
    }

    free(alloc_candidates);
    free(alloc_table);

    return 0;
}

void *wpalloc(unsigned int size)
{
    wpa_alloc *entry = malloc(sizeof(wpa_alloc));
    entry->size = size;

    wpa_page *page;
    for (int i = 0; i < RECENT_ALLOC_AMT; i++) {
        page = alloc_candidates[i];
        if (page != NULL && page->left > size) {
            entry->page = page;
            entry->addr = page->base + page->offset;
            entry->next = alloc_table[ALLOC_TABLE_BASE(entry->addr)];
            alloc_table[ALLOC_TABLE_BASE(entry->addr)] = entry;

            page->offset += size;
            page->left -= size;
            page->allocs++;
            WPA_DEBUG("[wpalloc] ALLOCing %u e %p\n", size, entry->addr);
            return entry->addr;
        }
    }

    /* Not enough space found in candidate pages, create new */
    WPA_DEBUG("[wpalloc] Creating new page...\n");
    page = malloc(sizeof(wpa_page));
    page->size = (PAGE_ALLOC_SIZE > size) ? PAGE_ALLOC_SIZE :
                                            ((size / PAGE_ALLOC_SIZE) + 1) * PAGE_ALLOC_SIZE;
    page->base = mmap(NULL, page->size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (page->base == MAP_FAILED) {
        WPA_DEBUG("[wpalloc] mmap failed!\n");
        free(page);
        return NULL;
    }
        // fprintf(stderr, "mmap successful\n");
    page->offset = size;
    page->left = page->size - size;
    page->allocs = 1;

    entry->page = page;
    entry->addr = page->base;
    entry->next = alloc_table[ALLOC_TABLE_BASE(entry->addr)];
    alloc_table[ALLOC_TABLE_BASE(entry->addr)] = entry;

    /* Add new page to list of candidates if its remaining
     * space is more than offered by one of the candidates */
    int candidate = -1;
    size_t candidate_left = page->left;
    for (int i = 0; i < RECENT_ALLOC_AMT; i++) {
        if (alloc_candidates[i] == NULL) {
            WPA_DEBUG("[wpalloc] NULL entry! Added page to opts\n");
            alloc_candidates[i] = page;
            return entry->addr;
        }
        WPA_DEBUG("[wpalloc] Candidate %i (%p) has %u left, %u\n", i,
                  alloc_candidates[i]->base,alloc_candidates[i]->left, page->left);
        if (alloc_candidates[i]->left < candidate_left) {
            candidate = i;
            candidate_left = alloc_candidates[i]->left;
        }
    }

    if (candidate >= 0 && candidate_left < page->left) {
        alloc_candidates[candidate] = page;
        WPA_DEBUG("[wpalloc] Added page %p to opts\n", page->base);
    }

    WPA_DEBUG("[wpalloc] ALLOCing %u n %p\n", size, entry->addr);
    return entry->addr;
}

void wpfree(void *ptr)
{
    wpa_alloc *prev = NULL, *entry = alloc_table[ALLOC_TABLE_BASE(ptr)];

    while (entry != NULL) {
        if (entry->addr == ptr) {
            entry->page->allocs--;

            if (entry->page->allocs == 0) {
                for (int i = 0; i < RECENT_ALLOC_AMT; i++) {
                    if (alloc_candidates[i] == entry->page) {
                        alloc_candidates[i] = NULL;
                        break;
                    }
                }
                WPA_DEBUG("[wpdebug] Page %p empty, freeing...\n");
                munmap(entry->page->base, entry->page->size);
            }

            if (prev == NULL)
                alloc_table[ALLOC_TABLE_BASE(ptr)] = entry->next;
            else
                prev->next = entry->next;

            WPA_DEBUG("[wpalloc] FREEing %p\n", ptr);
            free(entry);

            break;
        }
        prev = entry;
        entry = entry->next;
    }

    return;
}
