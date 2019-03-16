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

void printTrashAndTreeSize(int treeSize, long long int Setted_Bits, FILE *FileBits);

void printTreeInFile(huffmanTree *tree, int *treeSize, FILE *FileBits);

void SetBit(unsigned char *bits, unsigned char binary, int pos);

void Compressing(FILE *FileToCompress, FILE *FileBits, hash *hashTable, long long int *Setted_Bits);

void StartCompress(hash *hashTable, huffmanTree *root, FILE *FileToCompress, char name[]);

void compressMain();

long int *buildFrequency(FILE * input);

huffmanTree *buildHuffmanTree(pqueue *priorityQueue);

#endif