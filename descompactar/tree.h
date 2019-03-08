#include <stdio.h> 
#include <string.h> 

/* estrutura de um nó de uma árvore fila binária */
typedef struct node_tree node_t;

struct node_tree 
{
    unsigned int character;
    node_t *left; 
	node_t *right;
};

/* cria os nos da arvore*/
node_t *create_node(unsigned int character, node_t *left, node_t *right); 

unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size);

node_t *build_tree(unsigned int **tree_array);

node_t *get_tree(FILE *input_file, unsigned int tree_size); 
