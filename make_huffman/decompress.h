#ifndef decompress_huffman
#define decompress_huffman 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "utilities.h"

/* structure of a tree node */
typedef struct node_tree node_t;

struct node_tree 
{
    unsigned int character;
    node_t  *left; 
	node_t  *right;
};

/* create a tree with the character and left and right trees, respectively, 
 * and returns the address for the tree created */
node_t *create_node(unsigned int character, node_t *left, node_t *right);

/* frees memory occupied by all nodes in the tree */
void free_tree(node_t *huff_tree);

/* returns TRUE if the received node is a sheet and FALSE otherwise */
int is_leaf_decompress(node_t *binary_tree);

/* returns TRUE if the byte bit is set to the received position and FALSE
 * otherwise */
int is_bit_set_decompress(unsigned int character, int position); 

/* read byte the byte of the file after the tree and write the corresponding 
 * characters according to the received huffman tree */
void decom(FILE *input_file, unsigned int trash_size, int tree_size, node_t *huff_tree, FILE *output_file);

/* returns the amount of garbage bits that is written to the first byte of the
 * received in the first 3 bits */
unsigned int get_trash_size(FILE *input_file); 

/* returns the size of the tree that is written in the 13 bits next to the trash */
unsigned int get_tree_size(FILE *input_file); 

/* returns an array with the bytes of the tree written in the file, after the two
 * first bytes, according to the size of the tree received */
unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size);

/* creates a tree that is received written in preorder in an array and returns */
node_t *build_tree(unsigned int **tree_array); 

/* returns a tree written in preorder in the tree_size bytes after the second
 * byte in file received */
node_t *get_tree(FILE *input_file, unsigned int tree_size);

/* main to initialize decompress */
void decompressMain();

#endif