#include <stdio.h> 
#include <string.h> 
#include "tree.h"

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
int is_leaf(node_t *binary_tree) 
{
	return ((binary_tree != NULL) && (binary_tree->left == NULL) && (binary_tree->right == NULL));
}

/* verificar se o bit esta setado na posiçao ou nao*/
int is_bit_set(unsigned int character, int position) 
{
	unsigned int mask = 1 << position;
	return (mask & character);
}

void decompress(FILE *input_file, unsigned int trash_size, int tree_size, node_t *huff_tree, FILE *output_file) 
{
	if (tree_size == 0) 
	{
		return;
	}

	node_t *current_node = huff_tree;

	unsigned int current_byte;
	unsigned int character;
	unsigned int last_byte; 
	int bytes_total; 
	int bytes; 
	int i; 

	fseek(input_file, -1, SEEK_END);
	last_byte = getc(input_file);
	bytes_total = ftell(input_file);

	fseek(input_file, (2+tree_size),0);

	current_byte = getc(input_file);
	for (bytes = (2+tree_size); bytes < (bytes_total - 1); bytes++) 
	{
		for (i = 7; i >= 0; i--) 
		{
			/* se o bit estiver setado, anda para a direita na árvore */
			if (is_bit_set(current_byte, i) != 0) 
			{
				if (current_node->right != NULL)
				{
					current_node = current_node->right;
				}
			}
			else 
			{
				if (current_node->left != NULL)
					current_node = current_node->left;
			}
			if (is_leaf(current_node) != 0) 
			{
				fprintf(output_file, "%c", current_node->character);
				current_node = huff_tree;
			}
		}
		current_byte = getc(input_file);
	}

	for (i = 7; i >= (unsigned int)trash_size; i--) 
	{
		if (is_bit_set(current_byte, i) != 0) 
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
		if (is_leaf(current_node) != 0) 
		{
			fprintf(output_file, "%c", current_node->character);
			current_node = huff_tree;
		}
	}
	
}

unsigned int get_trash_size(FILE *input_file) 
{
	unsigned int trash_size = 0;
	unsigned int first_byte;
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
	unsigned int second_byte;

	fseek(input_file, 0, SEEK_SET);

	first_byte = getc(input_file); 
	second_byte = getc(input_file);

	first_byte = (first_byte << 3);
	first_byte = (first_byte >> 3);
	tree_size = ((first_byte << 8) | second_byte); //ERRADO!!1 MUDAR
	// FIRST BYTE ESTA SENDO ZERADO

	return (tree_size);
}

FILE *OpenFile(){
    printf("Type the input file name:\n");
    char name[100];
    fgets(name,100,stdin);
    int l = strlen(name);
    name[l-1] = '\0';

    return fopen(name, "rb");
}

int main()
{
	FILE *input_file = OpenFile();
	FILE *output_file; 
	
	if (input_file == NULL) 
	{
		printf("não foi possível ler o arquivo");
		return 0;
	}

	output_file = fopen("CompressedFile.txt","wb+");	
	if (output_file == NULL) 
	{
		printf("não foi possível escrever no arquivo");
		return 0; 
	}
	unsigned int trash_size = get_trash_size(input_file);
	
	unsigned int tree_size = get_tree_size(input_file);

	node_t *huff_tree = get_tree(input_file, tree_size);
	
	decompress(input_file, trash_size, tree_size, huff_tree, output_file);

	free_tree(huff_tree);
	fclose(input_file);
	fclose(output_file);
	return 0;
}