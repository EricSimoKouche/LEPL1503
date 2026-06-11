typedef struct node 
{
    struct node* next;
    int value;
} node_t;

typedef struct queue 
{
    struct node* head;
    int size;
} queue_t;

/**
 * Ajoute la valeur @val à l'endroit adéquat de la liste @q.
 * 
 * @val : la valeur à ajouter
 * @q   : la liste
 * 
 * @pre q != NULL, @q est une liste triée valide, val n'est pas déjà dans présent dans la liste
 * @return -1 en cas d'erreur, 0 sinon
 */
int enqueue(queue_t* q, int val) 
{
    node_t* new_node = malloc(sizeof(node_t));
    if (new_node == NULL) 
        return -1;

    new_node->value = val;
    new_node->next = NULL; 

    // Cas 1 : La liste est vide
    if (q->head == NULL) 
    {
        q->head = new_node;
        new_node->next = new_node; // Le nœud boucle sur lui-même
    }
    // Cas 2 : Ajout à la première place
    else if (val < q->head->value) 
    {
        // 1. Trouver le dernier élément pour maintenir la circularité
        node_t* last = q->head;
        while (last->next != q->head) 
        {
            last = last->next;
        }
        
        // 2. Insérer le nouveau nœud
        new_node->next = q->head;
        q->head = new_node;
        
        // 3. Fermer la boucle
        last->next = q->head; 
    }
    // Cas 3 : Ajout au milieu ou à la fin
    else 
    {
        node_t* current = q->head;
        node_t* prev = NULL;
        int i = 0;
        
        // On avance tant qu'on n'a pas fait un tour complet ET que la valeur est plus grande
        while (i < q->size && current->value < val) 
        {
            prev = current;
            current = current->next;
            i++;
        }
        
        // On insère entre 'prev' et 'current'.
        // Si on est à la fin, 'current' pointe vers 'head', ce qui maintient la circularité !
        prev->next = new_node;
        new_node->next = current;
    }
    
    q->size++;
    return 0;
}