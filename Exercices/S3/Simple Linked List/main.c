#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    int value;
} node_t;

typedef struct list {
    struct node* first;
    int size;
} list_t;

/*
    Create a new node containing the value @value.

    @value : value stored in the node 
    @next : pointer to the next node, initialized to NULL.
    @return : returns the pointer to the newly created node, 
                or NULL if an error occured
*/
node_t* init_node(int value) 
{
    node_t* node = malloc(sizeof(node_t));
    if (!node) return NULL;
    node->value = value;
    node->next = NULL;

    return node;
}

/*
    Add a node at the end of the list @list and increment the number of nodes in the list (member 'size')

    @list : linked list
    @value : value to add to the list

    @return : 0 if success, 1 otherwise
*/
int add_node(list_t* list, int value)
{
    if (!list) return 1;

    node_t* new_node = init_node(value);
    if (!new_node) return 1;

    if (list->size == 0)
    {
        list->first = new_node;
    } 
    else
    {
        new_node->next = list->first;
        list->first = new_node;
    } 

    list->size++;

    return 0;
}

void free_list(list_t* list) 
{
    int i = 0;
    node_t* current = list->first;
    while (i < list->size) 
    {
        node_t* tmp = current;
        current = current->next;
        free(tmp);
        i++;
    }
    free(list);
}

int main (int argc, char** argv)
{
    list_t list;
    list.first = NULL;
    list.size = 0;


    // Build the list :
    add_node(&list, 10);
    add_node(&list, 20);

    printf("the operation was %s\n", add_node(&list, 30) == 0 ? "a success" : "a failure");
    printf("the size of the list is %d\n", list.size);
    node_t* current = list.first;
    int i = 0;
    while (current)  
    {
        printf("[Node %d] - %d\n", i, current->value);
        current = current->next;
        i++;
    }
    return 0;
}