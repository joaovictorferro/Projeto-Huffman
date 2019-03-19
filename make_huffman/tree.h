#ifndef tree_huffman
#define tree_huffman 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct huffmanTree huffmanTree;

struct huffmanTree
{
  long int freq;
  unsigned char element;
  huffmanTree * left, *right;
};

int max(int a, int b);

int height(huffmanTree *tree);

int isLeaf(huffmanTree *treeNode);

void printTree(huffmanTree *tree);

void eraseTree(huffmanTree *tree);

huffmanTree *newNode(unsigned char c, long int f);

#endif
