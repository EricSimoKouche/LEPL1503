#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @pre -
 * @post retourne le nombre de caractères différents dans la chaîne pointée par str
 * Exemples:
 *  - ndiff("ABA") retourne 2
 *  - ndiff("") retourne 0
 *  - ndiff(NULL) retourne 0
 *  - ndiff("AabBAb") retourne 4
 */
int ndiff(char *str)
{
    if (!str || strcmp(str, "") == 0)
        return 0;

    size_t str_len = strlen(str);
    // 1. Initialize the array of count
    int chars[256];
    for (int i = 0; i < 256; i++)
        chars[i] = 0;

    // 2. Filling the array of count
    for (int i = 0; i < str_len; i++)
        chars[str[i]]++;

    // 3. Counting the number of non-null cases
    int count = 0;
    for (int i = 0; i < 256; i++)
        if (chars[i] != 0)
            count++;

    return count;
}