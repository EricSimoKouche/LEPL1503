#include <stdio.h>
#include <stdlib.h>

int add(int x, int y) { return x+y; }
int sub(int x, int y) { return x-y; }
int multiply(int x, int y) { return x*y; }

/**
 * @table : pointeur vers le premier élément du tableau contenant les fonctions à comparer
 * @x : premier élément à donner en argument aux fonctions
 * @y : deuxième  élément à donner en argument aux fonctions
 *
 * @pre table!=NULL, table[0]!=NULL (le tableau contient au moins 1 fonction), le dernier élément du tableau est NULL
 * @post applique toutes les fonctions contenues dans {table} à {x} et {y} et retourne la valeure maximale obtenue
*/
int maxf(int (**table)(int, int), int x, int y) 
{
    int max = table[0](x, y);
    for (int i = 1; table[i] != NULL; i++) 
    {
        int res = table[i](x, y);
        if (res > max) 
            max = res;
    }

    return max;
}