#ifndef huff_type
#define huff_type

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_HEAP_SIZE 257

typedef struct heap_adt heap;

/*
	Comentar aqui
*/

struct heap_adt
{
  int size;
  struct huffmanTree* data[MAX_HEAP_SIZE];
};

typedef struct huffmanTree huffmanTree;
/*
Comentar aqui
*/
struct huffmanTree
{
  int freq;
  char element;
  struct huffmanTree * left;
  struct huffmanTree * right;
};


#endif