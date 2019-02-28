#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define ASCII_SIZE 256

typedef struct priority_queue pqueue;
typedef struct huffmanTree huffmanTree;
typedef struct list_adt node;

struct huffmanTree{
  int freq;
  char element;
  huffmanTree * left;
  huffmanTree * right;
};

struct list_adt{
  huffmanTree * treeNode;
  node * next;
};

struct priority_queue{
  node * head;
};

pqueue * createPriorityQueue(){
  pqueue * new = (pqueue*)malloc(sizeof(pqueue));
  new->head = NULL;
  return new;
}

void priorityEnqueue(pqueue * priorityQueue, huffmanTree * newTreeNode){

  node * new = (node*)malloc(sizeof(node));
  new->treeNode = newTreeNode;

  if(priorityQueue->head == NULL || new->treeNode->freq <= priorityQueue->head->treeNode->freq){
    new->next = priorityQueue->head;
    priorityQueue->head = new;
  }
  else{
    node * current = priorityQueue->head;

    while(current->next != NULL && current->next->treeNode->freq < new->treeNode->freq){
      current = current->next;
    }

    new->next = current->next;
    current->next = new;
  } 
}

huffmanTree * priorityDequeue(pqueue * priorityQueue){

  if(priorityQueue->head == NULL){
    printf("PRIORITY QUEUE UNDERFLOW!\n");
    return NULL;
  }
  else{
    node * auxiliar = priorityQueue->head;
    priorityQueue->head = priorityQueue->head->next;
    auxiliar->next = NULL;
    return auxiliar->treeNode;
  }
}

huffmanTree * newNode(char c, int f){ // Creates a new huffman tree node to be added in the queue.

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

huffmanTree * buildHuffmanTree(pqueue * priorityQueue){

  huffmanTree * first_dequeued;
  huffmanTree * second_dequeued;
  int frequency;

  while(priorityQueue->head->next != NULL){                    

    first_dequeued = priorityDequeue(priorityQueue);
    second_dequeued = priorityDequeue(priorityQueue);

    frequency = (first_dequeued->freq) + (second_dequeued->freq);

    huffmanTree * enqueued = newNode('*',frequency);

    enqueued->left = first_dequeued;
    enqueued->right = second_dequeued;

    priorityEnqueue(priorityQueue,enqueued);
  }

  return priorityQueue->head->treeNode;
}

void printTree(huffmanTree * tree){

  if(tree==NULL){
    printf(" () ");
    return;
  }

  printf(" ( %c ", tree->element);

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

void eraseList(node * head){

  node * aux;

  while(head!=NULL){
    aux = head;
    head = head->next;
    free(aux); 
  }
}

void main(){

  printf("Type the input file name:\n");

  char inputFileName[50];
  getFileName(inputFileName); // Reading the input file name from the user.

  FILE * inputFile  = fopen(inputFileName,"rb"); // Opening the input file in binary read mode.

  int * frequencyArray;

  huffmanTree * huffmanRoot;

  pqueue * priorityQueue = createPriorityQueue();

  node * pqueueHead;

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
        priorityEnqueue(priorityQueue,auxiliar);
      }
    }

    pqueueHead = priorityQueue->head;

    huffmanRoot = buildHuffmanTree(priorityQueue);

    printTree(huffmanRoot);
    printf("\n");
  }
  eraseTree(huffmanRoot);
  free(priorityQueue);
}
