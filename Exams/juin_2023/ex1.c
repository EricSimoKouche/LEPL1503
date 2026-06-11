struct record
{
    char *student; // name of the student
    int n;         // numbers of courses taken
    int *points;   // points earned in each course
}

/** 
 * @pre n>0 correspond au nombre d'étudiants dans la classe, *classe!=NULL
 * @post retourne le nombre de cours en échecs pour l'ensemble des étudiants de la classe
 */
int
echecs(int n, struct record *classe)
{
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        res += echec_for_student(&classe[i]);
    }
    return res;
}

/**
 * @pre student the record of a student
 * @post le nombre de cours non reussi par cet(te) étudiant(e)
 */
int echec_for_student(struct record *student)
{
    int nb = student->n;
    int count = 0;

    for (int i = 0; i < nb; i++)
    {
        if (student->points[i] < 10)
        {
            count++;
        }
    }
    return count;
}