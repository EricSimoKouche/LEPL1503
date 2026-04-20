#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include the get/set functions from main.c */
int get(char *filename, int index);
void set(char *filename, int index, int value);

int main() {
	const char *testfile = "testdata.bin";
	
	/* Create a test file with 5 integers */
	printf("Creating test file with 5 integers...\n");
	FILE *f = fopen(testfile, "wb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	
	int initial_data[] = {10, 20, 30, 40, 50};
	fwrite(initial_data, sizeof(int), 5, f);
	fclose(f);
	printf("File created: %s\n\n", testfile);
	
	/* Test get() function */
	printf("=== Testing get() ===\n");
	for (int i = 0; i < 5; i++) {
		int val = get((char *)testfile, i);
		printf("Index %d: value = %d\n", i, val);
	}
	printf("\n");
	
	/* Test set() function */
	printf("=== Testing set() ===\n");
	printf("Setting index 2 to 999...\n");
	set((char *)testfile, 2, 999);
	printf("Setting index 4 to 111...\n");
	set((char *)testfile, 4, 111);
	printf("\n");
	
	/* Verify changes were written */
	printf("=== Verifying changes ===\n");
	for (int i = 0; i < 5; i++) {
		int val = get((char *)testfile, i);
		printf("Index %d: value = %d\n", i, val);
	}
	printf("\n");
	
	/* Test out of bounds */
	printf("=== Testing out of bounds ===\n");
	int result = get((char *)testfile, 10);
	printf("get(index=10): result = %d (expect -2)\n", result);
	
	return 0;
}
