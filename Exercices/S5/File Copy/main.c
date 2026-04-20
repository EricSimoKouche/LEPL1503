#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * @pre file_name != NULL, name of the original file 
 * 	new_file_name!= NULL, name of the new file (the copy)
 *
 * @post copy the contents of {file_name} to {new_file_name}.
 * 	 return 0 if the function terminates with success, -1 in case of errors.
 */
int copy(char *file_name, char *new_file_name) {

	int old_fd = -1, new_fd = -1;
	void *old_data = MAP_FAILED, *new_data = MAP_FAILED;
	struct stat old_st;

	old_fd = open(file_name, O_RDONLY);
	if (old_fd == -1) return -1;

	if (fstat(old_fd, &old_st) == -1) goto error;
	size_t size = old_st.st_size;

	if (size == 0) {
		new_fd = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, old_st.st_mode & 0777);
		if (new_fd == -1) goto error;
		close(new_fd);
		close(old_fd);
		return 0;
	}
	
	new_fd = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, old_st.st_mode & 0777);
	if (new_fd == -1) goto error;

	if (ftruncate(new_fd, size) == -1) goto error;
	
	old_data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, old_fd, 0);
	new_data = mmap(NULL, size, PROT_WRITE, MAP_SHARED, new_fd, 0);
	if (old_data == MAP_FAILED || new_data == MAP_FAILED) goto error;

	memcpy(new_data, old_data, size);

	msync(new_data, size, MS_SYNC);

	if (munmap(old_data, size) == -1 || munmap(new_data, size) == -1) goto error;
	if (close(old_fd) == -1 || close(new_fd) == -1) goto error;
	return 0;

error :
	if (old_data != MAP_FAILED) munmap(old_data, size);
	if (new_data != MAP_FAILED) munmap(new_data, size);
	if (old_fd != -1) close(old_fd);
	if (new_fd != -1) close(new_fd);
	return -1;
}

int main() {
	char *file_name = "testdata.bin";
	char *new_file_name = "test.bin";
	int old_fd = open(file_name, O_RDONLY);
	
	if (old_fd == -1) return -1;

	struct stat old_st;
	if (fstat(old_fd, &old_st) == -1) {
		close(old_fd);
		return -1;
	}

	size_t size = old_st.st_size;
	void *data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, old_fd, 0);
	if (data == MAP_FAILED) {
		close(old_fd);
		return -1;
	}
	int *integers = (int *) data;
	printf("The content we are going to copy\n");
	for (int i = 0; integers[i]; i++) {
		printf("Elt [%d] = %d\n", i, integers[i]);
	}

	if (copy(file_name, new_file_name) == -1) {
		printf("An error occured during the copy");
		exit(EXIT_FAILURE);
	}

	int new_fd = open(new_file_name, O_RDONLY);
	if (new_fd == -1) {
		munmap(data, size); 
		close(old_fd);
	}

	void *new_data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, new_fd, 0);
	if (new_data == MAP_FAILED) {
		munmap(data, size);
		close(old_fd);
		close(new_fd);
		return -1;
	}

	int *n_integers = (int *) new_data;
	printf("The content of the copy\n");
	for (int i = 0; n_integers[i]; i++) {
		printf("Elt [%d] = %d\n", i, n_integers[i]);
	}

	munmap(data, size);
	munmap(new_data, size);
	close(old_fd);
	close(new_fd);
	return 0;
	
}