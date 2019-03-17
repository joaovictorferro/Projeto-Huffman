#ifndef decompress_huffman
#define decompress_huffman 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "utilities.h"

typedef struct node_tree node_t;

struct node_tree 
{
    unsigned int character;
    void  *left; 
	void  *right;
};

node_t *create_node(unsigned int character, node_t *left, node_t *right);

void free_tree(node_t *huff_tree);

int is_leaf_decompress(node_t *binary_tree);

int is_bit_set_decompress(unsigned int character, int position); 

void decom(FILE *input_file, unsigned int trash_size, int tree_size, node_t *huff_tree, FILE *output_file);

unsigned int get_trash_size(FILE *input_file); 

unsigned int get_tree_size(FILE *input_file); 

unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size);

node_t *build_tree(unsigned int **tree_array); 

node_t *get_tree(FILE *input_file, unsigned int tree_size);

int decompressMain();

#endif