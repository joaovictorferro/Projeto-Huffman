#ifndef huff_tree
#define huff_tree

#include  "heap.h"
#include  "types.h"

#define MAX_HEAP_SIZE 257
#define ASCII_SIZE 256

huffmanTree* newNode(char c, int f);
/*
Comenta aqui
*/

huffmanTree* buildHuffmanTree(heap * h);

void printTree(huffmanTree * tree);

void eraseTree(huffmanTree * tree);

#endif