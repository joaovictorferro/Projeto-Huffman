#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct binary_t binary_tree;
struct binary_t
{
	int item;
	struct binary_t *left;
	struct binary_t *right;
};

binary_tree *create_binary_tree_avl(int value) 
{
    binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
    new_binary_tree->item = value;
    new_binary_tree->left = NULL;
    new_binary_tree->right = NULL;

    return new_binary_tree;
}

int is_empty_binary_tree(binary_tree *bt) 
{
    return (bt == NULL);
}

binary_tree *create_empty_binary_tree()
{
    return NULL;
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

binary_tree *insert_avl(binary_tree *bt, int value) 
{
    if (is_empty_binary_tree(bt)) 
    {
        bt = create_binary_tree_avl(value);
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
        free_avl(avl->left);
        free_avl(avl->right);
        free(avl);
    }
}

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

void swap(int *a, int *b) 
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

int main(){
	int max_size, each;
	printf("Tamanho maximo:");
	scanf("%d", &max_size);
	FILE *amostra;
	amostra = fopen("amostra.txt", "w");
	int i=0, j=0, k, media = 0, comp_abb = 0, cont = 0,comp_avl = 0,media1 = 0;
	fprintf(amostra, "ABB AVL Size\n");
	clock_t tempo;
  	tempo = clock();
		binary_tree* root_abb = create_empty_binary_tree();
		binary_tree* root_avl = create_empty_binary_tree();
		for(j = 0; j < max_size; j++)
		{
			if(j == 0)
			{
				root_abb = add(root_abb,j);
			}
			else
			{
				root_abb = add(root_abb, j);
			}
			root_avl = insert_avl(root_avl,j);
			if (avl (root_avl)) 
			{
            	//printf("Continuou AVL...\n  ");
        	} 
        	else 
        	{
                //printf("ajustar balanceamento...\n  ");
                root_avl = balance_binary_tree (root_avl);
        	}
        }
			for(j = 0; j < 100; j++)
			{
				k = rand() %j;
				search_abb(root_abb, k, &comp_abb);
				search_avl(root_avl, k, &comp_avl);
				media += comp_abb;
				//printf("%d\n",media );
				media1 += comp_avl;
				comp_abb = 0;
				comp_avl = 0;
				printf("%d %d %d\n", (int)media1, (int)media, j);
				fprintf(amostra, "%d %d %d\n", (int)media1, (int)media, j);
				media = media1 = 0;
			}
			free_bt(root_abb);
			free_avl(root_avl);
	printf("Tempo:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
	fclose(amostra);
	return 0;
}