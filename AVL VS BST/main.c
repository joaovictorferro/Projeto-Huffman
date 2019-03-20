#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct binary_t binary_tree;
struct binary_t
{
	int item;
	struct binary_t *left;
	struct binary_t *right;
};

typedef struct nodeTree node_t;
struct nodeTree 
{ 
    int value;
    int height; 
    node_t *right,*left; 
};

//-------------------------------------AVL--------------------------------------------------------//

node_t *CreateNode(int item)
{
    node_t *newNode = (node_t*) malloc(sizeof(node_t));
    newNode -> value = item;
    newNode -> left = NULL; 
    newNode -> right = NULL;
    newNode -> height = 0;
    return newNode;
}

int max(int a, int b)
{
  return a >= b ? a : b;
}

int height(node_t *node)
{
    if(node == NULL)
    {
     return -1;
    }
    else
    { 
        return 1 + max(height(node->left), height(node->right));
    }
}

int IsBalanced(node_t *node)
{
    int bf = height(node->left) - height(node->right);
    return ( (-1 <= bf) && (bf <= 1) );
}

int BalanceFactor(node_t *node)
{
    if(node == NULL)
    { 
        return 0;
    }
    else if((node->left != NULL) && (node->right != NULL))
    {
        return node->left->height - node->right->height; 
    }
    else if((node->left != NULL) && (node->right == NULL))
    {
        return 1 + node->left->height;
    }
    else
    { 
        return (-node->right->height - 1);
    }
}       

node_t *LeftRot(node_t *node)
{
    node_t *subtree = NULL;

    if(node != NULL && node->right != NULL)
    {
        subtree = node->right;
        node->right = subtree->left;
        subtree->left = node;
    }
    subtree->height = height(subtree);
    node -> height = height(node);
    return subtree;
}

node_t *RightRot(node_t *node)
{
    node_t *subtree = NULL;

    if(node != NULL && node->left != NULL)
    {
        subtree = node->left;
        node->left = subtree->right;
        subtree->right = node;
    }

    subtree->height = height(subtree);
    node->height = height(node);
    return subtree;
}

node_t *AddNode(node_t *node, int item)
{
    if(node == NULL)
    { 
        return CreateNode(item);
    }
    else if(node->value > item)
    { 
        node->left = AddNode(node->left, item);
    }
    else
    { 
        node->right = AddNode(node->right, item);
    }
    
    node -> height = height(node);
    node_t *child;
    int BF = BalanceFactor(node);
  
    if(BF == 2)
    {
        child = node->left;
        if(BalanceFactor(child) == -1)
        { 
            node->left = LeftRot(child);
        }
        node = RightRot(node);
    }
    else if(BF == -2)
    {
        child = node->right;
        if(BalanceFactor(child) == 1)
        { 
            node->right = RightRot(child);
        }
        node = LeftRot(node);
    }
    return node;
}


node_t* search_avl(node_t *avl, int item, int *comparisons)
{
    if((avl == NULL) || (avl->value == item))
    {
        ++*comparisons;
        return avl;
    }
    else if(avl->value > item)
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

int is_empty_binary_tree(node_t *bt)
{
    return(bt == NULL);
}

void free_avl(node_t *avl) 
{
    if(!is_empty_binary_tree(avl)) 
    {
        free_avl(avl->left);
        free_avl(avl->right);
        free(avl);
    }
}

//--------------------------------------ABB-------------------------------------------------------//
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
		bt = create_binary_tree_abb(item, NULL, NULL);
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

//-----------------------------------------------------------------------------------------------//

int main()
{
	int max_size;
	
    printf("Tamanho maximo:");
	scanf("%d", &max_size);
	
    FILE *amostra;
	amostra = fopen("amostra.txt", "w");
	
    int j = 0, k = 0, comp_abb = 0,comp_avl = 0,array[max_size];
	fprintf(amostra, "ABB AVL Valor\n");
		
    binary_tree* root_abb = NULL;
	node_t* root_avl = NULL;
	
    for(j=0;j < max_size;j++)
	{  
        root_abb = add(root_abb, j);
        root_avl = AddNode(root_avl, j);	
	}
			
    for(j = 0; j < max_size; j++)
	{
		k = rand() % max_size;
		search_abb(root_abb, k, &comp_abb);
		search_avl(root_avl, k, &comp_avl);

		printf("%d %d %d\n", (int)comp_abb, (int)comp_avl, k);
		fprintf(amostra, "%d %d %d\n", (int)comp_abb, (int)comp_avl, k);
	    
        comp_abb = 0;
        comp_avl = 0;
    }
	
    free_bt(root_abb);
	free_avl(root_avl);
    fclose(amostra);

	return 0;
}