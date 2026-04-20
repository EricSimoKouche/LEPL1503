#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

typedef struct point {
	int x; 
	int y;
	int z; 
} point_t;


/*
 * @pre pt != NULL, pointer to the first point_t in the array
 * 	size > 0, the length of the array.
 * 	filename != NULL
 * @post writes the array of point_t in the file.
 * 	 return 0 if everything worked correctly
 * 	 -1 if open() failed.
 * 	 -2 if close() failed.
 * 	 -3 if mmap() failed.
 * 	 -4 if munmap() failed.
 * 	 -5 if msync() failed.
 * 	 -6 if ftruncate() failed.
 */
int save(point_t *pt, int size, char *filename) {
	// Allouer de l'espace memoire pour stocker tous mes entiers
	// Sachant que chaque structures contient 3 entiers alors
	// le nombre total de bytes a alloue est de size * 3 * sizeof(int)
	// which is also size * sizeof(struct point)
	int capacity, i, fd;
	int *data, *integers;
	void *dest;
	
	capacity = size * sizeof(point_t);

	data = malloc(capacity);
	if (!data) 
		return -1;

	i = 0;
	while (i < size) {
		data[i * 3] = pt[i].x;
		data[i * 3 + 1] = pt[i].y;
		data[i * 3 + 2] = pt[i].z;
		i++;
	}
	
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		free(data);
		return -1;
	}

	if (ftruncate(fd, capacity) == -1) {
		free(data);
		close(fd);
		return -6;
	}

	dest = mmap(NULL, capacity, PROT_WRITE, MAP_SHARED, fd, 0);
	if (dest == MAP_FAILED) {
		free(data);
		close(fd);
		return -3;
	}

	integers = (int *) dest;
	memcpy(dest, data,capacity);

	i = 0;
	printf("==== dest ====\n");
	while (i < capacity / sizeof(int)) {
		printf("int[%d] = %d\n", i, integers[i]);
		i++;
	}

	i = 0;
	printf("==== data ====\n");
	while (i < capacity / sizeof(int)) {
		printf("int[%d] = %d\n", i, data[i]);
		i++;
	}

	if (msync(dest, capacity, MS_SYNC) == -1) {
		munmap(dest, capacity);
		free(data);
		close(fd);
		return -5;
	}

	if (munmap(dest, capacity) == -1) {
		close(fd);
		free(data);
		return -4;
	}

	if (close(fd) == -1) {
		return -2;
	}
	
	free(data);
	return 0;
}

int main(void) {

	struct point origin;
	origin.x = 1;
	origin.y = 2;
	origin.z = 3;

	if (save(&origin, 1, "points.dat") != 0) {
		printf("Error\n");
	}
	return 0;
}
