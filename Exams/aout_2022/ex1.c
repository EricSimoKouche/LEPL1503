#include <string.h>
#include <stdlib.h>

/* 
 * Crée un tampon/ buffer de la meme taille que {src}, et copie le contenu de {src} dans ce tampon 
 * @src: chaine de caractères à copier
 * @return: retourne le pointeur de la chaine de caracteres copiée. Si {src} == NULL ou en cas d'erreur, retourne NULL
 * 
 * Rapppelez-vous que les chaînes de caractères se terminent par '\0' et que strlen('abc') retourne 3 même si 4 octects sont nécessaires pour stocker cette chaîne. 
*/
char *buf_strcpy(const char* src) {
    if (!src)
        return NULL;
    
    char *buf;
    int src_len = strlen(src);

    buf = malloc(src_len + 1);
    if (!buf) 
        return NULL;
    
    for (int i = 0; i < src_len; i++) {
        buf[i] = src[i];
    }

    buf[src_len] = '\0';
    return buf;
}