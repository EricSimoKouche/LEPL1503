#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

/*
 * @pre filename != NULL, name of the file 
 * @post returns the sum of all integers stored in the binary file.
 * 	 returns -1 if open() failed.
 * 	 returns -2 if close() failed.
 * 	 returns -3 if mmap() failed.
 * 	 returns -4 if munmap() failed.
 * 	 returns -5 if fstat() failed.
 */
int sum_file(char *filename) {
	int fd, sum, i, *integers;
	struct stat st;
	size_t size;

	fd = open(filename, O_RDONLY);
	if (fd == -1) 
		return -1;

	if (fstat(fd, &st) == -1) {
		close(fd);
		return -5;
	}

	size = st.st_size;

	if (size == 0) {
		close(fd);
		return 0;
	}

	integers = (int *) mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (integers == MAP_FAILED) {
		close(fd);
		return -3;
	}
	
	i = 0;
	sum = 0;
	while (i < size / sizeof(int)) {
		sum += integers[i];
		i++;
	}

	if (munmap(integers, size) == -1) {
		close(fd);
		return -4;
	}

	if (close(fd) == -1) {
		return -2;
	}

	return sum;
}
