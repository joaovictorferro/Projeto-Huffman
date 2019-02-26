#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_HEAP_SIZE 257
#define ASCII_SIZE 256
#define DEBUG_HEAP 0

typedef struct heap_adt heap;
typedef struct huffmanTree huffmanTree;

struct huffmanTree{
  int freq;
  char element;
  huffmanTree * left;
  huffmanTree * right;
};

struct heap_adt{
  int size;
  huffmanTree * data[MAX_HEAP_SIZE];
};

void swap(huffmanTree * a, huffmanTree * b){ // Swap the nodes elements.
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

huffmanTree * deqHeapMin(heap * h){ // Removes an element from the min heap.

  if(!h->size){
    printf("underflow\n");
    return NULL;
  }
  else{
    huffmanTree * item = h->data[1];
    h->data[1] = h->data[h->size];
    h->size --;
    minHeapify(h,1);
    return item;
  }
}

void eraseHeap(heap * h){ // Deletes the haep.

  int i;

  for(i=0;i<=MAX_HEAP_SIZE;i++){
    free(h->data[i]);
  }

  free(h);
}

huffmanTree * newNode(char c, int f){ // Creates a new huffman tree node to be added in the heap.

  huffmanTree * new = (huffmanTree*)malloc(sizeof(huffmanTree));
  new->element = c;
  new->freq = f;
  new->left = NULL;
  new->right = NULL;
  return new;

}

int * buildFrequency(FILE * input){ // Creates the frequency array.

  int * frequency = (int *)calloc(ASCII_SIZE,sizeof(int));
  unsigned char currentByte;

  while(fscanf(input,"%c",&currentByte)!=EOF){
    frequency[currentByte]++;
  }

  return frequency;
}

void getFileName(char name[]){

  fgets(name,50,stdin);

  int l = strlen(name);

  name[l-1] = '\0';
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

void eraseTree(huffmanTree * tree){
  if(tree==NULL){
    free(tree);
    return;
  }
  eraseTree(tree->left);
  eraseTree(tree->right);
  free(tree);
}

void main(){

  printf("Type the input file name:\n");

  char inputFileName[50];
  getFileName(inputFileName); // Reading the input file name from the user.

  FILE * inputFile  = fopen(inputFileName,"rb"); // Opening the input file in binary read mode.

  int * frequencyArray;

  huffmanTree * huffmanRoot;

  heap * h = createHeap(); 

  if(inputFile==NULL){
    printf("ERROR: there is no file with the name typed.\n");
  }
  else{
    printf("File found.\n");
    frequencyArray = buildFrequency(inputFile);
    int i;
    huffmanTree * auxiliar;

    for(i=0;i<ASCII_SIZE;i++){
      if(frequencyArray[i]){           // Adds a new node to the heap if the frequency of the char is >= 1.
        auxiliar = newNode(i,frequencyArray[i]);
        enqHeapMin(h,auxiliar);
      }
    }

    if(DEBUG_HEAP){
      for(i=1;i<=h->size;i++){
        printf("%d %c %d\n", h->data[i]->element, h->data[i]->element, h->data[i]->freq); // Imprime os elementos da heap minima.
      }
    }

    huffmanRoot = buildHuffmanTree(h);

    printTree(huffmanRoot);
    printf("\n");
  }
  eraseTree(huffmanRoot);
  free(h);
}
