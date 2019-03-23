#ifndef p_queeu_huffman
#define p_queeu_huffman

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

/*
Structures of a priority queue and a
linked list node.
*/
typedef struct priority_queue pqueue;
typedef struct list_adt node;

struct priority_queue
{
  node * head;
};

struct list_adt
{
  void * item;
  node * next;
};

/*
This function creates a priority queue by
allocating the corresponding structures.
Then it returns the queue pointer.
*/
pqueue *createPriorityQueue();

/*
This function adds a Huffman Tree node in
the priority queue. It navigates in the queue
until the current queue element has a bigger
frequency then the one that is going to be
added and adds the element in that position.
*/
void priorityEnqueue(pqueue* priorityQueue, huffmanTree *newTreeNode);

/*
This function dequeues the first element
of the queue and returns the Huffman Tree
node pointer from the dequeued element.
*/
huffmanTree * priorityDequeue(pqueue* priorityQueue);

#endif
