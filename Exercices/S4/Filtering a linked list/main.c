#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct node {
	struct node *next;
	int hash;
	int id;
	char name[20];
	char buffer[100];
	unsigned int timestamp;
	char acl;
	short flow;
	char *parent;
	void *fifo;
} node_t ;

/*
 * pair_filter 
 * Make a copy of the linked list starting at head,
 * only taking the elements with an even index
 *
 * @param head head of a linked list, possibly NULL
 * @return A pointer to the filtered linked list, return NULL if error or if head == NULL
 *
 */
struct node *pair_filter(struct node *head) {
	
	if (head == NULL) 
		return NULL;

	struct node *new_head = (struct node *) malloc(sizeof(struct node));
	if (!new_head) 
		return NULL;
	memcpy(new_head, head, sizeof(struct node));
	new_head->next = NULL;

	struct node *new_tail = new_head;
	struct node *current = head->next;
	int i = 1;

	while (current != NULL) {
		if (i % 2 == 0) {
			struct node *new_node = (struct node *) malloc(sizeof(struct node));
			if (!new_node) {
				return NULL;
			}
			memcpy(new_node, current, sizeof(struct node));
			new_node->next = NULL;

			new_tail->next = new_node;
			new_tail = new_node;
		}
		current = current->next;
		i++;
	}

	return new_head;
}

int main() {
	printf("Filtering a linked list\n");
	return 0;
}

