#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

static int clock;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
    int i;
    int evict = 0;
    int min = clock;
    // examine every page and find the one with the oldest time stamp
    for(i = 0; i < memsize; i++) {
        if(coremap[i].pte->clock < min) {
            min = coremap[i].pte->clock;
            evict = i;
        }
    }
	
	return evict;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
    clock++;
    p->clock = clock;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
    clock = 0;
}
