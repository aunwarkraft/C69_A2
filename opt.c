#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

// from sim.h
#define MAXLINE 256

extern int memsize;

// get tracefile path
extern char *tracefile;

extern int debug;

extern struct frame *coremap;

int size;
addr_t *addr_list;

void count_lines(FILE *infp);
void populate_addr_list(FILE *infp);

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {

	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
    size = 0;
    FILE *f;
    f = fopen(tracefile, "r");

    if (f == NULL) {
        fprintf(stderr, "fopen: '%s': permision denied\n", tracefile);
        exit(-1);
    }
    
    count_lines(f);
    // a list of addresses
    addr_list = malloc(size * sizeof(addr_t));
    
    populate_addr_list(f);
}

// modified from sim.c
void count_lines(FILE *infp) {
	char buf[MAXLINE];
	addr_t vaddr = 0;
	char type;

	while(fgets(buf, MAXLINE, infp) != NULL) {
		if(buf[0] != '=') {
			sscanf(buf, "%c %lx", &type, &vaddr);
			if(debug)  {
				printf("%c %lx\n", type, vaddr);
			}
			size++;
		} else {
			continue;
		}

	}
}

// modified from sim.c
void populate_addr_list(FILE *infp) {
	char buf[MAXLINE];
	addr_t vaddr = 0;
	char type;
    int i = 0;

	while(fgets(buf, MAXLINE, infp) != NULL) {
		if(buf[0] != '=') {
			sscanf(buf, "%c %lx", &type, &vaddr);
			if(debug)  {
				printf("%c %lx\n", type, vaddr);
			}
            addr_list[i] = vaddr;
			i++;
		} else {
			continue;
		}

	}
}

