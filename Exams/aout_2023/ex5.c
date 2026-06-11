 /**
  * @pre string!=NULL, chaîne de caractères terminée par '\0'
  * @post retourne une chaîne de caractères contenant
  *       une seule fois chaque caractère présent dans string.
  *       le pointeur retourné doit être alloué par malloc
  *       et la taille de la zone mémoire retournée doit correspondre
  *       au nombre de caractères différents dans le string
  *       retourne NULL en cas d'erreur
  */

char * ndiff(char *string) 
{
   
    size_t str_len = strlen(string);
    if (str_len == 0) {
        char *res = malloc(1);
        if (res == NULL) 
            return NULL;

        res[0] = '\0';
        return res;
    }
    
    int count, index;
    int chars[256] = {0};

    for (int i = 0; i < str_len; i++) 
        chars[string[i]] += 1;

    count = 0;
    for (int i = 0; i < 256; i++) {
        if (chars[i] != 0) 
            count += 1;
    }

    char *res = malloc(count + 1);
    if (res == NULL) 
        return NULL;

    index = 0;
    for (int i = 0; i < 256; i++) 
    {
        if (chars[i] != 0) 
        {
            res[index] = (char) i;
            index++;
        }
    }
    res[index] = '\0';
    return res;
}