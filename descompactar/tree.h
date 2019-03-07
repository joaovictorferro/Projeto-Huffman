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

/* retorna um array com os bytes da árvore escrita no arquivo, após os dois
 * primeiros bytes, de acordo com o tamanho da árvore recebido */
unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size);

/* cria uma árvore que é recebida escrita em pré-ordem em um array e a retor-
 * na */
node_t *build_tree(unsigned int **tree_array);

/* retorna a árvore escrita em pré-ordem nos tree_size bytes após o segundo
 * byte no arquivo recebido */
node_t *get_tree(FILE *input_file, unsigned int tree_size); 
