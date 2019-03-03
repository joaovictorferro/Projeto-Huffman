#ifndef abb_tree
#define abb_tree

#include "typedef.h"

int is_empty(binary_tree *bt);

void free_bt(binary_tree *bt);

binary_tree* create_binary_tree_abb(int item, binary_tree *left, binary_tree *right);

binary_tree* add(binary_tree *bt, int item);

binary_tree* search_abb(binary_tree *bt, int item, int *comparisons);

#endif