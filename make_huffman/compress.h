#ifndef compress_huffman
#define compress_huffman

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"
#include "p_queue.h"
#include "tree.h"
#include "utilities.h"

/*************************************************************
This source file handles the compression by using the ncessary
data structures and applying the following algorithm:

-> Read the input file in binary mode;

-> Get the charcters frequency and by adding one by one in an
array with that has the same size as the ASCII table;

-> Create Huffman Tree nodes for every frequency array member
that has a frequency bigger than 0 and enqueue them into a
minimum priority queue;

-> Build the Huffman Tree by repeating the following steps: 
- get the two smaller frequency nodes with a dequeue;
- merge them into a new node;
- the first dequeued turns into the left child;
- the second dequeued turns into the right child;
- enqueue the merged node.
It does that until there is only one node left in the queue,
who will be the Huffman Tree's root;

-> Create the new codification by recursively navegating into
the Huffman Tree and add it in a hash table;

-> Open an output file in binary write mode;

-> Print the tree in the output file by navegating it in pre-
order and, at the same time,calculates the tree size;

-> Set the output file's bits according with the new binary
codification that is stored into the hash table;

-> Calculate the trash size;

-> Print the trash and tree sizes in the first two bytes.
************************************************************/

/*
This function calculates the trash size by geting the mod from
the setted bits. Then it writes the trash and tree sizes in the
first two bytes of the output file.
*/
void printTrashAndTreeSize(int treeSize, long long int Setted_Bits, FILE *FileBits);

/*
This function prints the Huffman Tree in the output file in
pre-order. It also calculates the tree size.
*/
void printTreeInFile(huffmanTree *tree, int *treeSize, FILE *FileBits);

/*
This function sets a bit in the chosen byte position.
*/
void SetBit(unsigned char *bits, unsigned char binary, int pos);

/*
This function does the manages the setting bit process by using
the codes from the hash table to indicate in what position of a
byte the bit must be set.
*/
void Compressing(FILE *FileToCompress, FILE *FileBits, hash *hashTable, long long int *Setted_Bits);

/*
This function opens the output file in binary write mode
and adds a .huff extension to it. Then it handles when to
call the other functions above.
*/
void StartCompress(hash *hashTable, huffmanTree *root, FILE *FileToCompress, char name[]);

/*
This function  handles the whole compression process, starting
from what is necessary to start the algorothm. It opens the
intput file in binary read mode, detecting if there is a typing
error. Then it calls the build frequency, build huffman tree,
build hash and start compress functions.
*/
void compressMain();

/*
This functions navigates in the indicated file to get the
charcters frequency. It does that by adding 1 in the array
position that corresponds to that charater's ASCII code every
time that character is found. Then it returns the array.
*/
long int *buildFrequency(FILE * input);

/*
This function builds the Huffman Tree by navigating through
the given priority queue. It repeats the following process
until there's only one element left in the queue:
- get the two smaller frequency nodes with a dequeue;
- merge them into a new node;
- the first dequeued turns into the left child;
- the second dequeued turns into the right child;
- enqueue the merged node.
The remaining element is the tree root, who is returned.
*/
huffmanTree *buildHuffmanTree(pqueue *priorityQueue);

#endif
