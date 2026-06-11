struct hm {
    int h;
    int m;
};

/**
 * @arr : pointeur vers le tableau contenant les struct hm
 * @n : nombre l'éléments dans ce tableau
 *
 * @pre le tableau contient au moins 1 élément
 *      h, m >= 0, m <= 59
 * @post renvoie une structure contenant un entier pour les heures et un pour les minutes
*/
struct hm sum_of_hm(struct hm *arr, int n) 
{
    int nb_h = 0, nb_m = 0;
    for (int i = 0; i < n; i++) 
    {
        nb_h += arr[i].h;
        nb_m += arr[i].m;
    }

    nb_h += nb_m / 60;
    nb_m %= 60;
    struct hm res = {.h = nb_h, .m = nb_m};
    return res;
}