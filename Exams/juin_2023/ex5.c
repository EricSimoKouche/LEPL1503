int identite(int x) { return x; }
int abs(int x)
{
    if (x >= 0)
        return x;
    else
        return -x;
}

/**
 * @pre min < max, f1 !=NULL, f2 != NULL
 * @post applique les fonction f1 et f2 à tous les entiers dans l'intervalle fermé [min, max]
 *       et retourne le nimbre de fois où ces deux fonction donnent le même résultat
 */
int compare(int min, int max, int f1(int), int f2(int))
{
    int count = 0;
    for (int x = min; x <= max; x++)
        if (f1(x) == f2(x))
            count++;
    return count;
}