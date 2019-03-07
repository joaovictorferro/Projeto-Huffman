#include "tree.h"

node_t *create_node(unsigned int character, node_t *left, node_t *right) 
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->character = character;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size) 
{
	unsigned int i;
	int *tree_array;
	tree_array = (unsigned int *)malloc(sizeof(unsigned int)*(tree_size));
	fseek(input_file, 2, 0);

	for (i = 0; i < tree_size; i++) 
	{
		tree_array[i] = getc(input_file);
	}
	return (tree_array); 
}

node_t *build_tree(unsigned int **tree_array) 
{
	if (**tree_array == '*') 
	{
		node_t *left;
		*tree_array = (*tree_array + 1); 
		left = build_tree(tree_array);
		*tree_array = (*tree_array + 1); 
		return (create_node('*', left, build_tree(tree_array)));

	}
	else if (**tree_array == '\\') 
	{
		*tree_array = (*tree_array + 1);
		return (create_node(**tree_array, NULL, NULL));

	}
	return (create_node(**tree_array, NULL, NULL)); 
}

node_t *get_tree(FILE *input_file, unsigned int tree_size) 
{
	if (tree_size == 0) 
	{
		return NULL;
	}
	unsigned int *tree_array;
	tree_array = get_tree_array(input_file, tree_size);

	unsigned int *tree_array_zero;
	tree_array_zero = tree_array;
	node_t *tree_root = build_tree(&tree_array);	
	free(tree_array_zero);

	return (tree_root);
}