#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Wrapper to the malloc system call.
 * If malloc fails, sleep for 5 seconds, and then try again.
 * If malloc failed 10 times in a row, return NULL.
 */
void *sleepy_malloc(size_t s) {

	void *allocation;
	for (int i = 0; i < 10; i++) {
		allocation = malloc(s);
		if (!allocation) 
			sleep(5);
		else 
			return allocation;

	}
	return NULL;
}

