#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct data {
	int longitude;
	int latitude;
	float avg_temp;
} data_t;

/*
 * Function used to put a new value in the shared buffer.
 *
 * @buf : the shared buffer to fill in with the address pointing to the data_t's
 * @len : the length of the shared buffer 
 * @first : the pointer to ther array index where you can find the first inserted element that's still in the buffer 
 *          (or more exactly the pointer to the first element, **if any**)
 * @last : the pointer to the array index where you can find the first empty space in the buffer
 * 	   (or more exactly the first NULL pointer in the array, **if any**)
 * @in : the number of data_t* pointers in the buffer
 * @d : the darta data_t* that has to be inserted in the buffer
 *
 * @return 0 if no error, -1 otherwise 
 * 
 */
int put (data_t** buf, int len, int* first, int* last, int* in, data_t* d) {
	if (len == *in)
		return -1;

	buf[*last] = d;
	*last = (*last + 1) % len;
	(*in)++;
	return 0;
}

/*
 * Function used to get a value from the shared buffer.
 */
data_t* get(data_t** buf, int len, int* first, int* last, int* in) {
	if (*in == 0 || buf[*first] == NULL)
		return NULL;

	data_t* d = buf[*first];
	*first = (*first + 1) % len;
	(*in)++;
	return d;
}

