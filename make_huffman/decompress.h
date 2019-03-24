#ifndef decompress_huffman
#define decompress_huffman 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "utilities.h"

/*
Structure of a tree node.
*/
typedef struct node_tree node_t;

struct node_tree 
{
    unsigned int character;
    node_t  *left; 
	node_t  *right;
};

/* 
This function creates a tree with the character
and left and right trees, respectively, and
returns the pointer for the tree created.
*/
node_t *create_node(unsigned int character, node_t *left, node_t *right);

/*
This function frees memory allocated to avoid
memory leak.
*/
void free_tree(node_t *huff_tree);

/*
This funciotn identifies if a node is a leaf
and returns 1 for positive and 0 for a negstive
result. 
*/
int is_leaf_decompress(node_t *binary_tree);

/*
This function identifies if a bit from a given
byte position is set and returns 1 for positive
or 0 for a negative result.
*/
int is_bit_set_decompress(unsigned int character, int position); 

/*
This function reads the file byte by byte starting
from the second byte. Then it writes the corresponding 
characters according to the received huffman tree in
output file.
*/
void decom(FILE *input_file, unsigned int trash_size, int tree_size, node_t *huff_tree, FILE *output_file);

/*
This function gets the trash size information from the
first file's byte and returns it.
*/
unsigned int get_trash_size(FILE *input_file); 

/*
This function gets the tree size information from the
first two file's bytes and returns it.
*/
unsigned int get_tree_size(FILE *input_file); 

/*
This function gets the tree pre-order string starting
from the third file's byte and returns it.
*/
unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size);

/*This funtion recursively builds the Huffmen Tree that
is received written in pre-order in the file and returns
the root's pointer.
*/
node_t *build_tree(unsigned int **tree_array); 

/*
This function handles the tree building process and
returns the root's pointer.
*/
node_t *get_tree(FILE *input_file, unsigned int tree_size);

/*
This function handles the hole decompress process. 
*/
void decompressMain();

#endif
