/**
 * @filename : nom du fichier
 * @index : index auquel se trouve l'entier à retourner
 *
 * @pre filename != NULL, index >= 0
 * @post retourne l'entier à l'indice {index}
 *       dans le tableau contenu dans le fichier {filename}.
 *       retourne -1 en cas d'erreur
 *       retourne -2 si index >= longueur du tableau.
 */
int get(char* filename, int index) 
{
    if (filename == NULL || index < 0) 
        return -1;

    int fd = -1, nb_ints, result;
    int *data = MAP_FAILED;
    size_t file_size;
    struct stat st;

    // 1. Ouvrir le fichier en lecture seule et sauvegarder sa taille
    fd = open(filename, O_RDONLY);
    if (fd == -1) 
        goto error;

    if (fstat(fd, &st) == -1) 
        goto error;

    file_size = st.st_size;
    if (file_size == 0)
        return -2;

    // 2. Mapper les donnees du fichier en memoire
    data = (int *) mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) 
        goto error;

    // 3. Rechercher l'élément souhaité
    nb_ints = file_size / sizeof(int); // Le nombres d'entiers dans le tableau
    if (index >= nb_ints)
    {
        munmap(data, file_size);
        close(fd);
        return -2;
    }
    else 
    {
        result = data[index];
    }

    if (munmap(data, file_size) == -1) 
        goto error;
    if (close(fd) == -1)
        goto error;

    return result;

    error:
    if (data != MAP_FAILED) munmap(data, file_size);
    if (fd != -1) close(fd);
    return -1;
}