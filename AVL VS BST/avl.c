#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

binary_tree *create_empty_binary_tree()
{
    return NULL;
}

binary_tree *create_binary_tree_avl(int value) 
{
    binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
    new_binary_tree->item = value;
    new_binary_tree->left = NULL;
    new_binary_tree->right = NULL;

    return new_binary_tree;
}

binary_tree *rotate_left(binary_tree *bt) 
{

    binary_tree *new_binary_tree = create_empty_binary_tree();

    if (!is_empty_binary_tree(bt) && !is_empty_binary_tree(bt->right)) 
    {
        new_binary_tree = bt->right;
        bt->right = new_binary_tree->left;
        new_binary_tree->left = bt;
    }
    return new_binary_tree;
}

binary_tree *rotate_right(binary_tree *bt) 
{
    binary_tree *new_binary_tree = create_empty_binary_tree();
    if (!is_empty_binary_tree(bt) && !is_empty_binary_tree(bt->left)) 
    {
        new_binary_tree = bt->left;
        bt->left = new_binary_tree->right;
        new_binary_tree->right = bt;
    }
    return new_binary_tree;
}

int is_empty_binary_tree(binary_tree *bt) 
{
    return (bt == NULL);
}

int balance_factor_of_tree(binary_tree* bt) 
{
    if (!is_empty_binary_tree(bt))
    {
        return (avl_get(bt->left) - avl_get(bt->right));
    }
    return 0;
}

int avl(binary_tree* bt) 
{
    int balance_factor = balance_factor_of_tree(bt);

    int right_avl=1;
    int left_avl=1;

    if (!is_empty_binary_tree(bt->left)) 
    {
        left_avl = avl(bt->left);
    }
    if (!is_empty_binary_tree(bt->right)) 
    {
        right_avl = avl(bt->right);
    }
    if (right_avl && left_avl)
    {
        return ((-2 < balance_factor) && (balance_factor < 2));
    }
    return 0;
}

int avl_get(binary_tree *bt) 
{
    if (is_empty_binary_tree(bt))
    {
        return -1;
    }
    int left_height;
    left_height = avl_get(bt->left);
    int right_height;
    right_height = avl_get(bt -> right);
    
    if (left_height > right_height)
    {
        return (left_height+1);
    }
    return (right_height+1);
}

binary_tree *insert_avl(binary_tree *bt, int value) 
{
    if (is_empty_binary_tree(bt)) 
    {
        bt = create_binary_tree(value);
    } 
    else if (bt->item > value) 
    {
        bt->left = insert_avl(bt->left, value);
    } 
    else 
    {
        bt->right = insert_avl(bt->right, value);
    }
    return bt;
}

binary_tree *balance_binary_tree(binary_tree *avle) 
{
    if (!is_empty_binary_tree(avle->left) && !avl(avle->left)) 
    {
        avle->left = balance_binary_tree(avle->left);
    }
    if (!avl(avle) && !is_empty_binary_tree(avle->right) && !avl(avle->right)) 
    {
        avle->right = balance_binary_tree(avle->right);
    }
    if (!avl(avle))
    {
        if (balance_factor_of_tree(avle)>1)
        { 
            if (balance_factor_of_tree(avle->left) < 0) 
            { 
                avle->left = rotate_left(avle->left);
            }
            avle = rotate_right(avle);
        } 
        else if (balance_factor_of_tree(avle)<1)
        {
            
            if (balance_factor_of_tree(avle->right) > 0) 
            {
                avle->right = rotate_right(avle->right);
            }

            avle = rotate_left(avle);
        }
    }
    return avle;
}   

binary_tree* search_avl(binary_tree *avl, int item, int *comparisons)
{
    if((avl == NULL) || (avl->item == item))
    {
        ++*comparisons;
        return avl;
    }
    else if(avl->item > item)
    {
        ++*comparisons;
        return search_avl(avl->left, item, &*comparisons);
    }
    else
    {
        ++*comparisons;
        return search_avl(avl->right, item, &*comparisons);
    }
}

void free_avl(binary_tree *avl) 
{
    if(!is_empty_binary_tree(avl)) 
    {
        free_bt(avl->left);
        free_bt(avl->right);
        free(avl);
    }
}