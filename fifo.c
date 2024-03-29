#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

//store page number for the oldest page
int curr;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {
	// calculate value for evictFrame
	int evictFrame = curr; 
	// increment frame # for next evict
	curr++;
	curr = curr % memsize;
	return evictFrame;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
	//the first frame to replave will be frame 0
	curr = 0;
}
