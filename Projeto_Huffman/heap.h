#ifndef huff_heap
#define huff_heap

#include  "tree.h"
#include  "types.h"

#define MAX_HEAP_SIZE 257
#define ASCII_SIZE 256
void swap(huffmanTree * a, huffmanTree * b);
/*
comentar
*/

heap * createHeap();

int parentIndex(heap * h, int i);

int leftIndex(heap * h, int i);

int rightIndex(heap * h, int i);

void enqHeapMin(heap * h, huffmanTree * new);

void minHeapify(heap * h, int i);

huffmanTree * deqHeapMin(heap * h);

void eraseHeap(heap * h);

#endif