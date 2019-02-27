#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include  "tree.h"
#include  "types.h"

#define MAX_HEAP_SIZE 257

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