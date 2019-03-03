#ifndef avl
#define avl_tree

#include "typedef.h"

binary_tree *create_empty_binary_tree();

binary_tree *create_binary_tree_avl(int value);

binary_tree *rotate_left(binary_tree *binary_tree);

binary_tree *rotate_right(binary_tree *binary_tree);

int is_empty_binary_tree(binary_tree *binary_tree);

int balance_factor_of_tree(binary_tree* binary_tree);

int avl(binary_tree* binary_tree);

int avl_get(binary_tree *binary_tree);

binary_tree *insert_avl(binary_tree *binary_tree, int value);

binary_tree *balance_binary_tree(binary_tree *avle);

binary_tree* search_avl(binary_tree *avl, int item, int *comparisons);

void free_avl(binary_tree *bt);

#endif