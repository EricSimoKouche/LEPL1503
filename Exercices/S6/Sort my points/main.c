typedef struct points
{
    int NOMA;
    float LEPL1103;
    float LEPL1203;
    float LEPL1108;
    float LEPL1302;
    float LEPL1402;
    float average;
} points_t;

/*
 * Function used to compare two structures based on their averages.
 *
 * @s1 : a pointer to the first structure
 * @s2 : a pointer to the second structure
 *
 * @return an integer less than, equal to, or greater than zero if the first argument is considered to be
 *        respectively less than, equal to, or greater than the second
 */
int compar(const void *s1, const void *s2)
{
    points_t *student_1 = (points_t *)s1, *student_2 = (points_t *)s2;
    float avg_1 = student_1->average, avg_2 = student_2->average;
    float diff = avg_1 - avg_2;

    if (diff < 0)
        return -1;
    else if (diff > 0)
        return 1;
    else
        return 0;
}

/*
 * Function used to update the file with the structures stored in it
 *
 * @filename : the path indicating where to find the file (!= NULL)
 *
 * @return 0 if no error
 *        -1 if open failed
 *        -2 if mmap failed
 *        -3 if munmap failed
 *        -4 if msync failed
 *        -5 if fstat failed
 *        -6 if close failed
 */
int sort(char *filename)
{
    int fd, nb_points;
    struct stat st;
    size_t size;
    points_t *points;

    fd = open(filename, O_RDWR, 0644);
    if (fd == -1)
    {
        return -1;
    }

    if (fstat(fd, &st) == -1)
    {
        close(fd);
        return -5;
    }

    size = st.st_size;
    nb_points = size / sizeof(struct points);

    // mapped the points into the virtual memory
    points = (points_t *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (points == MAP_FAILED)
    {
        close(fd);
        return -2;
    }

    // Compute the average and stored it into each structure
    for (int i = 0; i < nb_points; i++)
    {
        float average = (points[i].LEPL1103 + points[i].LEPL1203 + points[i].LEPL1108 + points[i].LEPL1302 + points[i].LEPL1402) / 5;
        points[i].average = average;
    }

    // sort the list of points based on the average
    qsort(points, nb_points, sizeof(struct points), compar);

    // syncing the result
    if (msync(points, size, MS_SYNC) == -1)
    {
        munmap(points, size);
        close(fd);
        return -4;
    }

    // unmap the mapped memory
    if (munmap(points, size) == -1)
    {
        close(fd);
        return -3;
    }

    if (close(fd) == -1)
    {
        return -6;
    }

    return 0;
}