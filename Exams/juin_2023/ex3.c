typedef struct node
{
    int key;
    double value;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct list
{
    node_t *head;
    node_t *tail;
} list_t;

list_t *create_list()
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;

    return list;
}

int insert(list_t *list, int key, double value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
        return -1;

    node->key = key;
    node->value = value;
    node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = node;
        node->prev = NULL;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
    }

    list->tail = node;
    return 0;
}

void free_list(list_t *list)
{
    node_t *current = list->tail;

    if (current == NULL)
    {
        free(list);
        return;
    }

    while (current->prev != NULL)
    {
        current = current->prev;
        free(current->next);
    }

    free(current);
    free(list);
}

/**
 * @pre :
 *  - list n'est pas NULL
 *  - Pour chaque paire a, b d'éléments dans la liste, a.key != b.key,
 *    autrement dit tous les noeuds ont des keys différents
 * @post
 *  - S'il y a un élément avec la clé `key` dans la liste, celui-coi est retiré
 *  - retourne la clé `key` de l'élément retiré
 *  - retourne 0 si aucun élément n'a été trouvé pour cette clé
 */
int delete(list_t *list, int key)
{

    node_t *current = list->head;
    // Case 1: The node to delete is the first
    if (current->key == key)
    {
        current->next->prev = NULL;
        list->head = current->next;
        free(current);
        return key;
    }
    // Case 2: The node to delete is after the first
    else
    {
        while (current->next != NULL & current->key != key)
        {
            current = current->next;
        }
        // Case 2.1: The node to delete is before the end
        if (current->key == key & current->next != NULL)
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return key;
        }
        // Case 2.2: The node to delete is the last
        else if (current->key == key & current->next == NULL)
        {
            current->prev->next = NULL;
            list->tail = current->prev;
            free(current);
            return key;
        }
    }

    // Case 3: The node wasn't found
    return 0;
}