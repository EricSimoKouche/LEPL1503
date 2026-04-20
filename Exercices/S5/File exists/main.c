#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * @pre filename != NULL
 * @post return 0 if the file {filename} exist. -1 Otherwise
 */
int file_exists(char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) 
		return fd;
	else {
		close(fd);
		return 0;
	}
}

int main(void) {
	printf("File Exists\n");
	return 0;
}
