#ifndef hash_huffman
#define hash_huffman

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

#define ASCII_SIZE 256

/*
Structures of a hash and a hash element.
*/
typedef struct hash_table hash;
typedef struct hash_element helement;

struct hash_table{
  helement * items[ASCII_SIZE];
};

struct hash_element{
  void * binaryCode;
  long int characterFrequency;
};

/*
This function creates a hash table by allocating
the corresponding structures above. The binary code
from the hash element will be allocated with the
maximum size indicated. Then it returns the hash pointer.
*/
hash *createHash(int maximumSize);

/*
This function builds a new codification for the
characters that are in the file. It does that by
recursively navigating in the Huffman Tree and
handling a string. It puts a 0 in the string's current
position when going to the left node's child or a 1
when going to the right child. When it arrives in a leaf
the string formed is copied to the corresponding
element in the hash table and the recursion stops.
*/
void buildHash(hash *hashTable, huffmanTree *huffmanNode, int position, unsigned char *auxiliarString);

/*
This functions frees the memory allocated
to avoid memory leak.
*/
void eraseHash(hash * hashTable);

#endif
