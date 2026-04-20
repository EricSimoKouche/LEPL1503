#include <sys/mman.h>
#include <sys/stat.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
 * @pre filename != NULL, index >= 0
 * @post return the integer at the index {index}
 * 	 of the array in the file {filename}
 * 	 return -1 in case of error
 * 	 return -2 if index >= length of array
 */
int get(char *filename, int index) {
	
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		return -1;
	}

	struct stat st;
	if (fstat(fd, &st) != 0) {
		close(fd);
		return -1;
	}

	size_t size = st.st_size;
	void *data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED) {
		close(fd);
		return -1;
	}

	int length = (int) size / sizeof(int);
	if (index >= length) {
		munmap(data, size);
		close(fd);
		return -2;
	}

	int *integers = (int *) data;
	int val_index = integers[index];

	munmap(data, size);
	if (close(fd) == -1)
		return -1;
	return val_index;
}

/*
 * @pre filename != NULL, index >= 0
 * @post Set the element in the file {filename}
 * 	 at index {index} at value {value}
 * 	 do nothing in case of errors
 */
void set(char *filename, int index, int value) {

	int fd = open(filename, O_RDWR);
	if (fd == -1) {
		return;
	}

	struct stat st;
	if (fstat(fd, &st) != 0) {
		close(fd);
		return;
	}

	size_t size = st.st_size;
	void *data = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
		close(fd);
		return;
	}

	int length = (int) size / sizeof(int);
	if (index >= length) {
		munmap(data, size);
		close(fd);
		return;
	}

	int *integers = (int *) data;
	integers[index] = value;

	msync(data, size, MS_SYNC);
	munmap(data, size);
	close(fd);
}
