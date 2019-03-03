#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int is_empty(binary_tree *bt)
{
	return(bt == NULL);
}

void free_bt(binary_tree *bt) 
{
    if(!is_empty(bt)) {
        free_bt(bt->left);
        free_bt(bt->right);
        free(bt);
    }
}

binary_tree* create_binary_tree_abb(int item, binary_tree *left, binary_tree *right)
{
	binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
	new_binary_tree->item = item;
	new_binary_tree->left = left;
	new_binary_tree->right = right;
	return new_binary_tree;
}

binary_tree* add(binary_tree *bt, int item)
{
	if(bt == NULL){
		bt = create_binary_tree(item, NULL, NULL);
	}else if(bt->item > item){
		bt->left = add(bt->left, item);
	}else{
		bt->right = add(bt->right, item);
	}
	return bt;
}

binary_tree* search_abb(binary_tree *bt, int item, int *comparisons)
{
	if((bt == NULL) || (bt->item == item)){
		++*comparisons;
		return bt;
	}else if(bt->item > item){
		++*comparisons;
		return search_abb(bt->left, item, &*comparisons);
	}else{
		++*comparisons;
		return search_abb(bt->right, item, &*comparisons);
	}
}