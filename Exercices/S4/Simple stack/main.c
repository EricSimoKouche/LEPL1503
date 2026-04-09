#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
	struct node *next;
	char *name;
};

/*
 * Remove the top element of the stack and return its content.
 *
 * @param head a pointer to the top of the stack
 * @param result a pointer to store the popped element
 *
 * @return 0 if no error, 1 otherwise
 *
 * pre : @result contains a null-terminated correct string
 * post : @result contains the string @name from the element at the top of the stack
 *
 */
int pop (struct node **head, char *result) {

	if (head == NULL || *head == NULL) 
		return 1;

	struct node *current = *head;
	*head = (*head)->next;

	char *name = current->name;
	size_t name_length = strlen(name);

	int i = 0;
	while (i < name_length) {
		result[i] = name[i];
		i++;
	}
	result[i] = '\0';
	
	free(name);
	free(current);
	return 0;
}

/*
 * Add @name at the "top" of the stack.
 *
 * @param head pointer to the top of the stack 
 * @param name the string to be placed in the element at the top of the stack
 *
 * @return 0 if no error, 1 otherwise
 *
 */
int push (struct node **head, const char *value) {
	
	if (head == NULL || value == NULL) 
		return 1;

	size_t value_length = strlen(value);
	char *name = (char *) malloc(value_length + 1);
	if (!name) {
		return 1;
	}
	strncpy(name, value, value_length);

	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	if (!new_node) {
		free(name);
		return 1;
	}

	new_node->name = name;
	new_node->next = *head;
	*head = new_node;
	return 0;
}

int main () {
	printf("Simple stack\n");
	return 0;
}

