#ifndef tree_huffman
#define tree_huffman 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

/*
Structure from
*/
typedef struct huffmanTree huffmanTree;

struct huffmanTree
{
  long int freq;
  unsigned char element;
  huffmanTree * left, *right;
};

/*
This function returns the biggest
value that was passed in the arguments.
*/
int max(int a, int b);

/*
This function recursively calculates
and returns the height of a tree node.
*/
int height(huffmanTree *tree);

/*
This function identifies if the node
passed as an argument is a leaf and
returns 1 for a positive and 0 for a
negative answer.
*/
int isLeaf(huffmanTree *treeNode);

/*
This function prints the tree in
pre-order in the terminal.
*/
void printTree(huffmanTree *tree);

/*
This function frees the allocated
memory to avoid memory leak.
*/
void eraseTree(huffmanTree *tree);

/*
This function creates a new Huffman
Tree node and returns its pointer.
*/
huffmanTree *newNode(unsigned char c, long int f);

#endif
