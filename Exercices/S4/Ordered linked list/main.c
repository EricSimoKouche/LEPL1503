#include <stdlib.h>
#include <stdio.h>

/*
 * @return 0 if equals, negative number if @b is greater 
 * and positive number otherwise. 
 * 
 */
int compare(char a, char b) {
	return a - b;
}

typedef struct node {
	char val;
	struct node *next;
} node_t;

/*
 * @param val value to be inserted. If the value is already in the list, no element is added and the list is not modified
 * @param fun comparison function which defines the order relationship of the list
 * @param head first node of the list, head != NULL
 * 
 * @return 0 if success, -1 otherwise
 *
 */
int insert(node_t **head, char val, int (*cmp)(char, char)) {
	
	node_t *new_node = (node_t *) malloc(sizeof(node_t));
	if (!new_node)
		return -1;
	new_node->val = val;
	new_node->next = NULL;

	// Case of an empty list
	if (*head == NULL) {
		new_node->next = NULL;
		*head = new_node;
		return 0;
	}
	
	if (cmp(val, (*head)->val) == 0) {
		free(new_node);
		return 0;
	
	} else if (cmp(val, (*head)->val) < 0) { // Insert at the begining
		new_node->next = *head ;
		*head = new_node;

	} else {
		node_t *prev = *head;
		node_t *current = (*head)->next;

		while (current != NULL && cmp(val, current->val) > 0) {
			prev = prev->next;
			current = current->next;
		}

		if (current != NULL && cmp(val, current->val) == 0) {
		       	free(new_node);	
			return 0;
		}
		
		new_node->next = current;
		prev->next = new_node;

	}
	return 0;
}

int main() {
	printf("Ordered linked list\n");
	return 0;
}
