#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Creates a buffer that has the same size as src, and copies the content of src to this buffer.
 *
 * @param src string to be copied
 * @return A pointer. If src == NULL or in case of error, return NULL
 *
 * Remember that strings are terminated with '\0' and that strlen("abc") returns 3 even if 4bytes are required to store this string.
 */
char *buf_strcpy(const char *src) {
	
	if (src == NULL) return NULL;

	size_t len = strlen(src);
	char *buf = malloc(len + 1);

	if (!buf) {
		return NULL;
	}

	buf[len] = '\0';

	for (size_t i = 0; i < len; i++) {
		buf[i] = src[i];
	}

	return buf;
}

void main (int argc, char **argv) {

	char *word = "Mama";
	char *copy = buf_strcpy(word);
	if (!copy) 
		printf("Error detected");

	printf("the copy is %s\n", copy);

	free(copy);
}

