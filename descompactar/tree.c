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
	/* cria um array com o tamanho da árvore recebido */
	int *tree_array;
	tree_array = (unsigned int *)malloc(sizeof(unsigned int)*(tree_size));
	/* vai até o terceito byte do arquivo para receber os caracteres (o ter-
	 * ceiro byte é o primeiro byte da árvore) */
	fseek(input_file, 2, 0);

	/* recebe os caracteres em sequencia tree_size vezes */
	for (i = 0; i < tree_size; i++) 
	{
		tree_array[i] = getc(input_file);
	}
	return (tree_array); /* retorna o endereço para o array criado */
}

node_t *build_tree(unsigned int **tree_array) 
{
	/* se o nó for *, faz o nó da esquerda primeiro, depois anda uma posição
	 * no array (após o nó da esquerda) e retorna o nó da direita já incluso
	 * no nó que está sendo criado com o * */
	if (**tree_array == '*') 
	{
		node_t *left;
		*tree_array = (*tree_array + 1); /* anda uma posição no array */
		left = build_tree(tree_array);
		*tree_array = (*tree_array + 1); /* anda uma posição no array */
		return (create_node('*', left, build_tree(tree_array)));

	}
	/* se o nó for \, retorna uma folha com o próximo caracter */
	else if (**tree_array == '\\') 
	{
		*tree_array = (*tree_array + 1); /* anda uma posição no array */
		return (create_node(**tree_array, NULL, NULL));

	}
	/* se o nó não for * nem \, retorna uma folha com o caracter atual */
	return (create_node(**tree_array, NULL, NULL)); 
}

node_t *get_tree(FILE *input_file, unsigned int tree_size) 
{
	if (tree_size == 0) 
	{
		return NULL;
	}
	/* recebe o array com a árvore em pré-ordem */
	unsigned int *tree_array;
	tree_array = get_tree_array(input_file, tree_size);

	/* guarda a primeira posição do array, que será modificado pela função que
	 * cria a árvore, para que a memória alocada para o array possa ser libe-
	 * rada depois */
	unsigned int *tree_array_zero;
	tree_array_zero = tree_array;

	/* recebe a árvore criada a partir do array recebido */
	node_t *tree_root = build_tree(&tree_array);
	
	/* libera a memória alocada para o array */
	free(tree_array_zero);

	return (tree_root);
}