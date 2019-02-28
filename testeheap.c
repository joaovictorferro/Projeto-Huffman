#include "heap.h"

void swap(huffmanTree * a, huffmanTree * b)
{ // Swap the nodes elements.
  char caux; // auxiliar char.
  int faux;  // auxiliar int.

  caux = a->element;
  a->element = b->element; // char element swap.
  b->element = caux;

  faux = a->freq;
  a->freq = b->freq; // int freq swap.
  b->freq = faux;
}

heap * createHeap(){ // Creates a heap.

  heap * new = (heap*)malloc(sizeof(heap));
  new->size = 0;
  return new;
}

int parentIndex(heap * h, int i){ // Calculates the parent node index.
  return (i>>1);
}

int leftIndex(heap * h, int i){ // Calculates the left son index.
  return (i<<1);
}

int rightIndex(heap * h, int i){ // Calculates the right son index.
  return ((i<<1)+1);
}

void enqHeapMin(heap * h, huffmanTree * new){ // Adds an element to the min heap.

  if(h->size>=MAX_HEAP_SIZE){
    printf("overflow\n");
    return;
  }
  else{
    h->data[++h->size] = new;

    int keyIndex = h->size;
    int parent = parentIndex(h,h->size);

    while(parent >= 1 && h->data[keyIndex]->freq < h->data[parent]->freq){
      swap(h->data[keyIndex],h->data[parent]);
      keyIndex = parent;
      parent = parentIndex(h,keyIndex);
    }
  }
}

void minHeapify(heap * h, int i){ // Maintains the min heap property.
  int smallest;
  int left = leftIndex(h,i);
  int right = rightIndex(h,i);

  if(left <= h->size && h->data[left]->freq < h->data[i]->freq){
    smallest = left;
  }
  else{
    smallest = i;
  }
  if(right <= h->size && h->data[right]->freq < h->data[smallest]->freq){
    smallest = right;
  }

  if(h->data[i]->freq != h->data[smallest]->freq){
    swap(h->data[i],h->data[smallest]);
    minHeapify(h,smallest);
  }
}

huffmanTree * deqHeapMin(heap * h)
{ 

  if(!h->size){
    printf("underflow\n");
    return ;
  }
  else{
    huffmanTree * item = h->data[1];
    h->data[1] = h->data[h->size];
    h->size --;
    minHeapify(h,1);
    return item;
  }
}

void eraseHeap(heap * h)
{

  int i;

  for(i=0;i<=MAX_HEAP_SIZE;i++){
    free(h->data[i]);
  }

  free(h);
}