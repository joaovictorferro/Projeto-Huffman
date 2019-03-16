#ifndef hash_huffman
#define hash_huffman

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

#define ASCII_SIZE 256

typedef struct hash_table hash;
typedef struct hash_element helement;

struct hash_table{
  void * items[ASCII_SIZE];
};

struct hash_element{
  void * binaryCode;
  long int characterFrequency;
};

hash *createHash(int maximumSize);

void buildHash(hash *hashTable, huffmanTree *huffmanNode, int position, unsigned char *auxiliarString);

void eraseHash(hash * hashTable);

#endif