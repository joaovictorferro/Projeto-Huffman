#ifndef p_queeu_huffman
#define p_queeu_huffman

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

typedef struct priority_queue pqueue;
typedef struct list_adt node;

struct priority_queue
{
  void * head;
};

struct list_adt
{
  void * item;
  void * next;
};


pqueue *createPriorityQueue();

void priorityEnqueue(pqueue* priorityQueue, huffmanTree *newTreeNode);

huffmanTree * priorityDequeue(pqueue* priorityQueue);

#endif