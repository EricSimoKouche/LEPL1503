#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/*
 * Function used to protect a global variable used in the fonction inc().
 *
 * @inc : the function that must be called in critical (=protected) section
 * @nb : the number of times the function inc() has to be called 
 * @mutex : an initialised mutex that has to be used for the protection 
 *
 * @return 0 if no error, -1 otherwise
 */
int protect(void inc(void), int nb, pthread_mutex_t* mutex) {

	int i = 0, err;

	while (i < nb) {
		err = pthread_mutex_lock(mutex);
		if (err == -1) 
			return -1;
		inc();
		err = pthread_mutex_unlock(mutex);
		if (err == -1)
			return -1;
		i++;
	}
	return 0;
}
