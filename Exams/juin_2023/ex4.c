#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @pre file_name != NULL, nom du fichier source
 *      new_file_name != NULL, nom du fichier destination (la copie)
 *
 * @post copie le contenu de  {file_name} vers {new_file_name}.
 *       return 0 si la fonction se termine avec succès, -1 en cas d'erreur.
 */
int copy(char *file_name, char *new_file_name)
{
    int src_fd = -1, dest_fd = -1;
    void *src = MAP_FAILED, *dest = MAP_FAILED;
    struct stat old_st;
    size_t file_size;

    // 1. Get the data from the source file

    src_fd = open(file_name, O_RDONLY);
    if (src_fd == -1)
        goto error;

    if (fstat(src_fd, &old_st) == -1)
        goto error;

    file_size = old_st.st_size;
    // Special case: When the source file is empty
    if (file_size == 0)
    {
        dest_fd = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777 & old_st.st_mode);
        close(src_fd);
        close(dest_fd);
        return 0;
    }

    src = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (src == MAP_FAILED)
        goto error;

    // 2. Initialize the dest file with the right size and mode (acces-rights)

    dest_fd = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777 & old_st.st_mode);
    if (dest_fd == -1)
        goto error;

    if (ftruncate(dest_fd, file_size) == -1)
        goto error;

    dest = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, dest_fd, 0);
    if (dest == MAP_FAILED)
        goto error;

    // 3. Copy the data in the dest file

    memcpy(dest, src, file_size);

    // 4. Syncing with the HDD

    if (msync(dest, file_size, MS_SYNC) == -1)
        goto error;

    // 5. Unmap and close the files
    
    if (munmap(src, file_size) == -1 || munmap(dest, file_size) == -1)
        goto error;
    if (close(src_fd) == -1 || close(dest_fd) == -1)
        goto error;

    return 0;

error:
    if (src != MAP_FAILED)
        munmap(src, file_size);
    if (dest != MAP_FAILED)
        munmap(dest, file_size);
    if (src_fd != -1)
        close(src_fd);
    if (dest_fd != -1)
        close(dest_fd);
    return -1;
}