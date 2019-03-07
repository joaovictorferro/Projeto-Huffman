#include <stdio.h> 
#include <string.h> 
#include "tree.h"

/* apaga arvore*/
void free_binary_tree(node_t *huff_tree) 
{
	if (huff_tree != NULL) 
	{
		free_binary_tree(huff_tree->left);
		free_binary_tree(huff_tree->right);
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

/* lê byte a byte do arquivo após a árvore e escreve os caracteres correspon-
 * dentes de acordo com a árvore de huffman recebida */
void decompress(FILE *input_file, unsigned int trash_size, int tree_size, node_t *huff_tree, FILE *output_file) 
{
	/* se a árvore é de tamanho ZERO, não há o que ser feito, então a função é
	 * interrompida */
	if (tree_size == 0) 
	{
		return;
	}

	node_t *current_node = huff_tree;

	unsigned int current_byte; /* byte corrente no arquivo de entrada */
	unsigned int character; /* character da sequencia de bits encontrada */
	unsigned int last_byte; /* último byte do arquivo, antes de EOF */
	int bytes_total; /* total de bytes no arquivo */
	int bytes; /* índice de bytes do arquivo */
	int i; /* índice para laço */

	/* vai até o fim do arquivo e recebe o penúltimo byte (o último será EOF)
	 * e depois recebe o número do byte atual do arquivo (EOF), que será a
	 * quantidade de bytes total do arquivo */
	fseek(input_file, -1, SEEK_END);
	last_byte = getc(input_file);
	bytes_total = ftell(input_file);

	/* volta para o início do arquivo, logo após a árvore que está escrita */
	fseek(input_file, (2+tree_size),0);

	/* para cada byte lido, verifica bit a bit se está setado e, se estiver
	 * anda uma vez para a direita na árvore de huffman, se não, anda uma vez
	 * para a esquerda na árvore de huffman até que se encontre um nó folha da
	 * árvore. quando um nó folha é encontrado, o caracter do nó é escrito no
	 * arquivo de saída e a leitura do restante do byte é continuada, até que
	 * se chegue ao antepenúltimo byte do arquivo (o penúltimo será escrito
	 * depois, respeitando o tamanho do lixo, e o último é EOF e não deve ser
	 * escrito) */
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
			/* se o bit não estiver setado, anda para a esquerda na árvore */
			else {
				if (current_node->left != NULL)
					current_node = current_node->left;
			}
			/* se uma folha for encontrada na árvore, escreve o caracter dela
			 * no arquivo de saída */
			if (is_leaf(current_node) != 0) 
			{
				fprintf(output_file, "%c", current_node->character);
				current_node = huff_tree;
			}
		}
		/* recebe o próximo byte */
		current_byte = getc(input_file);
	}

	/* os últimos bits serão recebitos somente até o tamanho do lixo, no últi-
	 * mo byte do arquivo */
	for (i = 7; i >= (signed int)trash_size; i--) 
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
	fseek(input_file, 0, SEEK_SET); /* volta ao início do arquivo */
	first_byte = getc(input_file); /* recebe o primeiro byte do arquivo */
	trash_size = (unsigned int)(first_byte >> 5);
	/* anda 5 bits para pega os 3 bits referentes ao tamanho do lixo*/ 
	return (trash_size); /* retorna o tamanho do lixo */
}

unsigned int get_tree_size(FILE *input_file) 
{
	unsigned int tree_size;
	unsigned char first_byte;
	unsigned int second_byte;

	fseek(input_file, 0, SEEK_SET); /* volta ao início do arquivo */

	/* recebe os dois primeiros bytes do arquivo */
	first_byte = getc(input_file); 
	second_byte = getc(input_file);

	/* apaga os três primeiros bits do primeiro byte, pois só interessa os 5 bits restantes */
	first_byte = (first_byte << 3);
	first_byte = (first_byte >> 3);

	/* o tamanho da árvore é a união entre os 5 últimos bits do primeiro byte e o segundo byte */
	/* isso e uma soma de bytes*/
	tree_size = ((first_byte << 8) | second_byte);

	return (tree_size); /* retorna o valor que estava escrito */
}

int main()
{
	FILE *input_file;
	FILE *output_file; 

	input_file = fopen("teste.txt","rb");
	
	if (input_file == NULL) 
	{
		printf("não foi possível ler o arquivo");
		return 0;
	}

	output_file = fopen("saida.txt","wb+");	
	if (output_file == NULL) 
	{
		printf("não foi possível escrever no arquivo");
		return 0; 
	}
	/* receber o tamanho do lixo escrito nos três primeiros bits */
	unsigned int trash_size = get_trash_size(input_file);

	/* receber o tamanho da árvore escrito nos 13 bits após o tamanho do lixo */
	unsigned int tree_size = get_tree_size(input_file);

	/* criar uma árvore de huffman de acordo com a que está escrita no arquivo */
	node_t *huff_tree = get_tree(input_file, tree_size);
	
	/* descomprimir o arquivo de entrada de acordo com a árvore criada */
	decompress(input_file, trash_size, tree_size, huff_tree, output_file);

	/* libera a memória alocada para a árvore */
	free_binary_tree(huff_tree);
	fclose(input_file);
	fclose(output_file);
	return 0;
}