#include "decompress.h"

node_t *create_node(unsigned int character, node_t *left, node_t *right) 
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->character = character;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

/* apaga arvore*/
void free_tree(node_t *huff_tree) 
{
	if (huff_tree != NULL) 
	{
		free_tree(huff_tree->left);
		free_tree(huff_tree->right);
		free(huff_tree);
	}
}

/* verifica se o nó é uma folha ou não*/
int is_leaf_decompress(node_t *binary_tree) 
{
	return ((binary_tree != NULL) && (binary_tree->left == NULL) && (binary_tree->right == NULL));
}

/* verificar se o bit esta setado na posiçao ou nao*/
int is_bit_set_decompress(unsigned int character, int position) 
{
	unsigned int mask = 1 << position;
	return (mask & character);
}

void decom(FILE *input_file, unsigned int trash_size, int tree_size, node_t *huff_tree, FILE *output_file) 
{
	if (tree_size == 0) 
	{
		return;
	}

	node_t *current_node = huff_tree;

	unsigned int current_byte;
	unsigned int character;
	unsigned int last_byte; 
	long long int bytes_total; 
	long long int bytes; 
	int i; 

	fseek(input_file, -1, SEEK_END);
	last_byte = getc(input_file);
	bytes_total = ftell(input_file);
	//printf("%lli\n", bytes_total);
	//return ;
	fseek(input_file, (2+tree_size),0);

	current_byte = getc(input_file);
	for (bytes = (2+tree_size); bytes < (bytes_total - 1); bytes++) 
	{
		//printf("%lli\n",bytes);
		for (i = 7; i >= 0; i--) 
		{
			/* se o bit estiver setado, anda para a direita na árvore */
			if (is_bit_set_decompress(current_byte, i) != 0) 
			{
				if (current_node->right != NULL)
				{
					current_node = current_node->right;
				}
			}
			else 
			{
				if (current_node->left != NULL)
				{
					current_node = current_node->left;
				}
			}
			if (is_leaf_decompress(current_node) != 0) 
			{
				fprintf(output_file, "%c", current_node->character);
				current_node = huff_tree;
			}
		}
		current_byte = getc(input_file);
	}
	printf("Sai para ler o lixo\n");

	for (i = 7; i >= (signed int)trash_size; i--) 
	{
		if (is_bit_set_decompress(current_byte, i) != 0) 
		{
			if (current_node->right != NULL)
			{
				current_node = current_node->right;
			}
		}
		else 
		{
			if (current_node->left != NULL)
			{
				current_node = current_node->left;
			}
		}
		if (is_leaf_decompress(current_node) != 0) 
		{
			fprintf(output_file, "%c", current_node->character);
			current_node = huff_tree;
		}
	}
	printf("Decompress ok!!");
	return ;
}

unsigned int get_trash_size(FILE *input_file) 
{
	unsigned int trash_size = 0;
	unsigned char first_byte;
	
	fseek(input_file, 0, SEEK_SET);
	
	first_byte = getc(input_file);
	trash_size = (unsigned int)(first_byte >> 5);
	/*anda 5 bits para pega os 3 bits referentes ao tamanho do lixo*/ 
	return (trash_size); /* retorna o tamanho do lixo */
}

unsigned int get_tree_size(FILE *input_file) 
{
	unsigned int tree_size;
	unsigned char first_byte;
	unsigned char second_byte;

	fseek(input_file, 0, SEEK_SET);

	first_byte = getc(input_file); 
	second_byte = getc(input_file);

	first_byte = first_byte << 3;
	first_byte = first_byte >> 3;
	tree_size = ((first_byte << 8) | second_byte);
	
	return (tree_size);
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
		(*tree_array) ++; 
		left = build_tree(tree_array);
		(*tree_array) ++; 
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

	unsigned int *tree_array_auxiliar;
	tree_array_auxiliar = tree_array;

	node_t *tree_root = build_tree(&tree_array);

	free(tree_array_auxiliar);

	return (tree_root);
}

FILE* removerhuff(char name[])
{
	int n;
	n = strlen(name);
	name[n-5] = '\0';
	return fopen(name,"wb");;
}

void decompressMain()
{
	char name[100],string;
	FILE *input_file = OpenFile(name);
	FILE *output_file; 
	
	if (input_file == NULL) 
	{
		printf("não foi possível ler o arquivo");
		return;
	}

	output_file = removerhuff(name);	
	if (output_file == NULL) 
	{
		printf("não foi possível escrever no arquivo");
		return; 
	}
	unsigned int trash_size = get_trash_size(input_file);

	unsigned int tree_size = get_tree_size(input_file);

	node_t *huff_tree = get_tree(input_file, tree_size);
	
	decom(input_file, trash_size, tree_size, huff_tree, output_file);

	free_tree(huff_tree);
	fclose(input_file);
	fclose(output_file);
}
