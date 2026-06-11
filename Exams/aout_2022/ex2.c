#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    char *name;
};

/*
 * Supprime l'élément du haut de la pile et retourne son contenu.
 *
 * @head : un pointeur vers le haut de la pile
 * @result : un pointeur pour stocker l'élement enlevé
 * @result_size : la taille maximale du buffer 'result' (incluant l'octet nul)
 *
 * @return 0 si pas d'erreur, 1 sinon
 */
int pop(struct node **head, char *result, size_t result_size) {
    // Check if double pointer is NULL OR if the stack is empty
    if (!head || !*head) 
        return 1;

    struct node *pt_node = *head;
    size_t name_length = strlen(pt_node->name);

    // Check if the provided buffer is large enough (including space for '\0')
    if (result_size < name_length + 1) 
        return 1;

    // Copy the string and ensure null-termination
    strcpy(result, pt_node->name);

    // Update the head of the stack
    *head = pt_node->next;

    // Free the memory
    free(pt_node->name);
    free(pt_node);

    return 0;
}

/*
 * Ajoute @name au dessus de la pile.
 */
int push(struct node **head, const char *value) {
    // Protect against NULL pointers for both inputs
    if (!head || !value) 
        return 1;

    // Note: You can use strdup(value) here if your system supports POSIX!
    // But doing it manually with malloc/strcpy is perfectly fine and standard C.
    size_t value_length = strlen(value);
    char *name = malloc(value_length + 1);
    if (!name) 
        return 1;
    strcpy(name, value);

    struct node *new_node = malloc(sizeof(struct node));
    if (!new_node) {
        free(name);
        return 1;
    }
    
    new_node->name = name;
    new_node->next = *head;

    *head = new_node;

    return 0;
}