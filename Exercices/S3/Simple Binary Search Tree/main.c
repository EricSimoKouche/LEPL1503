#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* left; // to smaller values
    struct node* right; // to larger values
} node_t;

typedef struct bt{
    struct node* root;
} bt_t;


/*
    @value : the integer to search
    Return 1 if there is a node containing @calue in @tree and 0 otherwise.
*/
int contains(bt_t* tree, int value) 
{
    if ( !tree || !tree->root ) 
        return 0;

    if (tree->root->value == value) 
    {
        return 1;
    }

    if (value < tree->root->value)
    {
        bt_t left_tree = {tree->root->left};
        return contains(&left_tree, value);
    }

    bt_t right_tree = {tree->root->right};
    return contains(&right_tree, value);
}

node_t* create_node(int value) 
{
    node_t* new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int main(int argc, char** argv) 
{
    bt_t tree;

    // Create nodes
    node_t* n10 = create_node(10);
    node_t* n5 = create_node(5);
    node_t* n15 = create_node(15);

    // Build tree
    tree.root = n10;

    n10->left = n5;
    n10->right = n15;

    printf("No error\n");
    printf("%d", contains(&tree, 10));

    return 0;
}