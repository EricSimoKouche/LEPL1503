#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @pre file_name != NULL, nom du fichier original 
 *      new_file_name != NULL, nom du nouveau fichier (la copie)
 * 
 * @post copie le contenus de {file_name} vers {new_file_name}.
 *       retourne 0 si la fonction se termine avec succès, -1 en cas d'erreurs. 
 */
int copy(char *file_name, char *new_file_name) {
    int old_fd = -1, new_fd = -1;
    void *src = MAP_FAILED, *dest = MAP_FAILED;
    struct stat old_st;
    size_t file_size;
    

    // 1. Open the file and get the map its data into memory
    old_fd = open(file_name, O_RDONLY);
    if (old_fd == -1) goto error;

    if (fstat(old_fd, &old_st) == -1) goto error;

    file_size = old_st.st_size;
    // Special case : When the source file is empty
    if (file_size == 0) {
        new_fd = open (new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777 & old_st.st_mode);
        close(old_fd);
        close(new_fd);
        return 0;
    }

    src = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, old_fd, 0);
    if (src == MAP_FAILED) goto error;

    // 2. Create a file to copy to
    new_fd = open (new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777 & old_st.st_mode);
    if (new_fd == -1) goto error;

    if (ftruncate(new_fd, file_size)) goto error;

    dest = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, new_fd, 0);
    if (dest == MAP_FAILED) goto error;

    // 3. Copy the content of {file_name} in {new_file_name}
    memcpy(dest, src, file_size);

    if (msync(dest, file_size, MS_SYNC) == -1) goto error;

    // 4. Unmmapping and closing the files
    if (munmap(src, file_size) == -1 || munmap(dest, file_size) == -1) goto error;
    if (close(old_fd) == -1 || close(new_fd) == -1) goto error;

    return 0;

error :
    if (src != MAP_FAILED) munmap(src, file_size);
    if (dest != MAP_FAILED) munmap(dest, file_size);
    if (old_fd != -1) close(old_fd);
    if (new_fd != -1) close(new_fd);
    return -1;
}

int main() {
    printf("result of the copy : %d\n", copy("empty.txt", "copy.txt"));
    return 0;
}