#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node *next;
	int value;
} node_t;

typedef struct queue {
	struct node *tail;
	int size;
} queue_t;

/*
 * Add @val value at the head of the @q queue
 *
 * @param val the value to enqueue
 * @param q the queue
 *
 * @return 0 if no error, -1 otherwise
 *
 * pre : The queue q will always be valid, you don't need to handle the NULL case.
 */
int enqueue(queue_t *q, int val) {
	
	if (q == NULL) 
		return -1;

	node_t *new_node = malloc(sizeof(node_t));
	if (!new_node) 
		return -1;

	new_node->value = val;
	
	if (q->size == 0) {
		new_node->next = new_node;
		q->tail = new_node;
	} else {
		new_node->next = q->tail->next;
		q->tail->next = new_node;
	}
	q->size++;

	return 0;
}

/*
 * Remove the node at the tail of the @q queue and return the value of this node.
 *
 * @param q the queue
 * @return The value at the tail
 *
 * pre : The given queue will always be valid, you do not need to handle NULL case.
 * 
 */
int dequeue(queue_t *q) {

	if(q == NULL || q->tail == NULL) 
		return -1;

	node_t *prev = q->tail;
	node_t *current = q->tail->next;

	while (current != q->tail) {
		prev = current;
		current = current->next;
	}

	int val = current->value;
	if (q->size == 1) {
		q->tail = NULL;
	} else {
		prev->next = current->next;
		q->tail = prev;
	}

	q->size--;
	free(current);
	
	return val;
}

int main() {
	printf("Advanced queue\n");
	return 0;
}



