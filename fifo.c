#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

//data that will store the frame number in FIFO order
struct QueueNode{
	unsigned int frame;
	struct QueueNode *next;
};
//pointer that stores the frame number that was accessed first
struct QueueNode *first;
//pointer that stores the frame number that was accessed last
struct QueueNode *last;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {
	int evictFrame = first->frame;
	//proper freeing mechanism for first QueueNode is still missing
	if(first->next != NULL){
		struct QueueNode *tempNode;
		tempNode = first->next;
		free(first);
		first = tempNode;
		free(tempNode);
	}

	// if therse only one node in the Queue the pointer to the first node is not changed
	/*
	if(first->next != NULL){
		first = first->next;
	}
	*/
	return evictFrame;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {
	// the QueueNode for last has already been created
	last->frame = p->frame;
	// create QueueNode for future
	last->next = malloc(sizeof(struct QueueNode));
	last = last->next;
	last->next = NULL;
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
	first = malloc(sizeof(struct QueueNode));
	first->next = NULL;
	//since there's only QueueNode first and last QueueNodes are the same
	last = first;
}
