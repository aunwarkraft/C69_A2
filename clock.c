#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

// points to candidate frame that will be evicted if it hass not been recently referened
int curr;
// this list stores reference status for all frames
// 1 for reference, 0 for not referenced
int *refList;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	//stores frame that is to be evicted
	int evictFrame;
	//loop until a frame that has not been recently referenced is encountered
	while(refList[curr] == 1){
		refList[curr] = 0;
		curr++;
		curr = curr % memsize;
	}
	evictFrame = curr;
	refList[evictFrame] = 1;
	//future candidate frame will be frame right after the frame being evicted rn
	//curr++;
	curr = curr % memsize;
	return evictFrame;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	int refFrame;
	// get frame # and initialized it's refList value as 1(referenced)
	refFrame = p->frame % memsize;
	refList[refFrame] = 1;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
	// initialize candidate frame as the first frame
	curr = 0;
	//allocate heap space and initialize all references to 0 (not referenced)
	refList = malloc(sizeof(int) * memsize);
	int i = 0;
	for(i = 0; i < memsize; i++){
		refList[i] = 0;
	}
}
