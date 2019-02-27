#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include  "tree.h"
#include  "heap.h"
#include  "types.h"

#define MAX_HEAP_SIZE 257
#define ASCII_SIZE 256

huffmanTree * newNode(char c, int f){ // Creates a new huffman tree node to be added in the heap.

  huffmanTree * new = (huffmanTree*)malloc(sizeof(huffmanTree));
  new->element = c;
  new->freq = f;
  new->left = NULL;
  new->right = NULL;
  return new;

}

huffmanTree * buildHuffmanTree(heap * h){

  huffmanTree * first_dequeued;
  huffmanTree * second_dequeued;
  int frequency;

  while(h->size > 1){                     // while the size is bigger than 1 the function will keep getting the smallest frequency nodes,
                                          // merge them into a new one, and then add again to the heap.
    first_dequeued = deqHeapMin(h);
    second_dequeued = deqHeapMin(h);

    frequency = (first_dequeued->freq) + (second_dequeued->freq);

    huffmanTree * enqueued = newNode('*',frequency);

    enqueued->left = first_dequeued;
    enqueued->right = second_dequeued;

    enqHeapMin(h,enqueued);
  }

  return h->data[1]; // the first and unique element from the heap will be the huffman root.
}

void printTree(huffmanTree * tree){

  if(tree==NULL){
    printf(" () ");
    return;
  }

  printf(" ( %d %c %d", tree-> element, tree->element, tree->freq);

  printTree(tree->left);
  printTree(tree->right);

  printf(") ");

}

void eraseTree(huffmanTree * tree)
{
  if(tree==NULL){
    free(tree);
    return;
  }
  eraseTree(tree->left);
  eraseTree(tree->right);
  free(tree);
}
