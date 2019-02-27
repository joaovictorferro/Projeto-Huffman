#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include  "heap.h"
#include  "types.h"

#define MAX_HEAP_SIZE 257

huffmanTree * newNode(char c, int f);
/*
Comenta aqui
*/

huffmanTree * buildHuffmanTree(struct heap * h);

void printTree(huffmanTree * tree);

void eraseTree(huffmanTree * tree);
