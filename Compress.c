#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define ASCII_SIZE 256

typedef struct priority_queue pqueue;
typedef struct huffmanTree huffmanTree;
typedef struct list_adt node;
typedef struct hash_table hash;
typedef struct hash_element helement;

// FUNÇÕES
int max(int a, int b);

hash *createHash(int maximumSize);
void buildHash(hash *hashTable, huffmanTree *huffmanNode, int position, unsigned char *auxiliarString);
void eraseHash(hash * hashTable);

pqueue *createPriorityQueue();
void priorityEnqueue(pqueue *priorityQueue, huffmanTree *newTreeNode);
huffmanTree *priorityDequeue(pqueue *priorityQueue);

int height(huffmanTree *tree);
int isLeaf(huffmanTree *treeNode);
huffmanTree *newNode(char c, int f);
long int *buildFrequency(FILE * input);
huffmanTree *buildHuffmanTree(pqueue *priorityQueue);
void printTree(huffmanTree *tree);
void eraseTree(huffmanTree *tree);

int max(int a, int b);
void eraseList(node * head);
FILE *OpenFile();

// v ------ DATATYPE ------ v

struct hash_element{
  unsigned char * binaryCode;
  long int characterFrequency;
};

struct hash_table{
  helement * items[ASCII_SIZE];
};

struct huffmanTree{
  long int freq;
  unsigned char element;
  huffmanTree * left, *right;
};

struct list_adt{
  huffmanTree * treeNode;
  node * next;
};

struct priority_queue{
  node * head;
};

// ^ ------ DATATYPE ------ ^

void Compressing(FILE *FileToCompress, FILE *FileBits, hash *hashTable, *Seted_Bits){
  unsigned char character, bits;

  while( fscanf(FileToCompress, "%c", &character) != EOF ){
    printf("funcinaaaa\n");
  }

}

void StartCompress(hash *hashTable){
  // FILE *FileToCompress = OpenFile();
  // FILE *FileBits = fopen("File_With_Bits_Only.txt", "w");

  int Seted_Bits = 0;
  // Compressing(FileToCompress, FileBits, hashTable, &Seted_Bits);
  printf("funcina\n");

  fclose(FileToCompress);
  fclose(FileBits);
}

void main(){

  FILE *inputFile = OpenFile(); // Opening the input file in binary read mode.
  long int * frequencyArray;
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

    int rootHeight = height(huffmanRoot);

    hash * hashTable = createHash(rootHeight+1);

    unsigned char auxiliarString[rootHeight+1];

    buildHash(hashTable,huffmanRoot,0,auxiliarString);

    for(i=0;i<ASCII_SIZE;i++){
      if(hashTable->items[i]->characterFrequency){
        printf("%c %s\n", i, hashTable->items[i]->binaryCode);
      }
    }

    // eraseHash(hashTable);
    // eraseTree(huffmanRoot);
    // free(priorityQueue);
    fclose(inputFile);
    StartCompress(hashTable);
  }
}

// v ------- HASH -------- v 

hash *createHash(int maximumSize){
  hash * new = (hash *)malloc(sizeof(hash));
  int i;
  for(i = 0; i < ASCII_SIZE; i++){
    new->items[i] = (helement *) malloc(sizeof(helement));
    new->items[i]->characterFrequency = 0;
    new->items[i]->binaryCode = (unsigned char *) calloc(maximumSize,sizeof(unsigned char)); 
  }
  return new;
}

void buildHash(hash *hashTable, huffmanTree *huffmanNode, int position, unsigned char *auxiliarString){

  if(isLeaf(huffmanNode)){
    auxiliarString[position] = '\0';
    strncpy(hashTable->items[huffmanNode->element]->binaryCode,auxiliarString,position+1);
    hashTable->items[huffmanNode->element]->characterFrequency = huffmanNode->freq;
    return;
  }
  if(huffmanNode->left!=NULL){
    auxiliarString[position] = '0';
    buildHash(hashTable,huffmanNode->left,position+1,auxiliarString);
  }
  if(huffmanNode->right!=NULL){
    auxiliarString[position] = '1';
    buildHash(hashTable,huffmanNode->right,position+1,auxiliarString);
  }

}

void eraseHash(hash * hashTable){
  int i;
  for(i=0;i<ASCII_SIZE;i++){
    free(hashTable->items[i]->binaryCode);
    free(hashTable->items[i]);
  }
  free(hashTable);
}

// ^ ------- HASH ------- ^

// v ------- P_QUEUE ------- v

pqueue *createPriorityQueue(){
  pqueue * new = (pqueue*)malloc(sizeof(pqueue));
  new->head = NULL;
  return new;
}

void priorityEnqueue(pqueue *priorityQueue, huffmanTree *newTreeNode){

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

huffmanTree *priorityDequeue(pqueue *priorityQueue){

  if(priorityQueue->head == NULL){
    printf("PRIORITY QUEUE UNDERFLOW!\n");
    return NULL;
  }
  else{
    node * auxiliar = priorityQueue->head;
    priorityQueue->head = priorityQueue->head->next;
    auxiliar->next = NULL;
    huffmanTree * returnNode = auxiliar->treeNode;
    free(auxiliar);
    return returnNode;
  }
}

// ^ ------- P_QUEUE ------- ^

// v ------- TREE -------- v

int height(huffmanTree *tree){
  if(tree==NULL) return -1;
  return 1 + max(height(tree->left),height(tree->right));
}

int isLeaf(huffmanTree *treeNode){
  return (!treeNode->left && !treeNode->right);
}

huffmanTree *newNode(char c, int f){ // Creates a new huffman tree node to be added in the queue.

  huffmanTree * new = (huffmanTree*)malloc(sizeof(huffmanTree));
  new->element = c;
  new->freq = f;
  new->left = NULL;
  new->right = NULL;
  return new;

}

long int *buildFrequency(FILE * input){ // Creates the frequency array.

  long int * frequency = (long int *)calloc(ASCII_SIZE,sizeof(long int));
  unsigned char currentByte;
  FILE * auxiliar = input;

  while(fscanf(auxiliar,"%c",&currentByte)!=EOF){
    frequency[currentByte]++;
  }

  return frequency;
}

huffmanTree *buildHuffmanTree(pqueue *priorityQueue){

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

void printTree(huffmanTree *tree){

  if(tree==NULL) return;

  printf("%c", tree->element);
  printTree(tree->left);
  printTree(tree->right);
}

void eraseTree(huffmanTree *tree){
  if(tree==NULL){
    free(tree);
    return;
  }
  eraseTree(tree->left);
  eraseTree(tree->right);
  free(tree);
}

// ^ ------- TREE -------- ^

int max(int a, int b){
  return a >= b ? a : b;
}

void eraseList(node * head){
  node * aux;

  while(head!=NULL){
    aux = head;
    head = head->next;
    free(aux); 
  }
}

FILE *OpenFile(){
    printf("Type the input file name:\n");
    char name[100];
    fgets(name,100,stdin);
    int l = strlen(name);
    name[l-1] = '\0';

    return fopen(name, "rb");
}