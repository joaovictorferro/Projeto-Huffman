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
huffmanTree *newNode(unsigned char c, long int f);
long int *buildFrequency(FILE * input);
huffmanTree *buildHuffmanTree(pqueue *priorityQueue);
void printTree(huffmanTree *tree);
void eraseTree(huffmanTree *tree);

int max(int a, int b);
void eraseList(node * head);
FILE *OpenFile(char name[]);

void printTrashAndTreeSize(int treeSize, long long int Setted_Bits, FILE *FileBits);
void printTreeInFile(huffmanTree *tree, int *treeSize, FILE *FileBits);
void SetBit(unsigned char *bits, unsigned char binary, int pos);
void Compressing(FILE *FileToCompress, FILE *FileBits, hash *hashTable, long long int *Setted_Bits);
void StartCompress(hash *hashTable, huffmanTree *root, FILE *FileToCompress, char name[]);

void compressMain();
void decompressMain();

void header();
void options();

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
  void * item;
  node * next;
};

struct priority_queue{
  node * head;
};

// ^ ------ DATATYPE ------ ^

void main(){

  int choice, loop = 1;
  
  while(loop){

    system("clear || cls");
    header();
    options();

    scanf("%d", &choice);
    getchar();

    switch (choice){

      case 1:
        compressMain();
        break;

      case 2:
        //decompressMain();
        break;

      case 3:
        loop = 0;
        break;

      default:
        break;
    }
  }
}

// v ------- HASH -------- v 

hash *createHash(int maximumSize){
  hash * new = (hash *) malloc(sizeof(hash));
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
  pqueue * new = (pqueue*) malloc(sizeof(pqueue));
  new->head = NULL;
  return new;
}

void priorityEnqueue(pqueue *priorityQueue, huffmanTree *newTreeNode){

  node * new = (node*) malloc(sizeof(node));
  new->item = newTreeNode;

  if(priorityQueue->head == NULL || ((huffmanTree*)new->item)->freq <= ((huffmanTree*)priorityQueue->head->item-)>freq){
    new->next = priorityQueue->head;
    priorityQueue->head = new;
  }
  else{
    node * current = priorityQueue->head;

    while(current->next != NULL && ((huffmanTree*)current->next->item)->freq < ((huffmanTree*)new->item)->freq){
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
    huffmanTree * returnNode = (huffmanTree*)auxiliar->item;
    free(auxiliar);
    return returnNode;
  }
}

// ^ ------- P_QUEUE ------- ^

// v ------- TREE -------- v

int height(huffmanTree *tree){
  if(tree == NULL) return -1;
  return 1 + max( height(tree->left), height(tree->right));
}

int isLeaf(huffmanTree *treeNode){
  return (!treeNode->left && !treeNode->right);
}

huffmanTree *newNode(unsigned char c, long int f){ // Creates a new huffman tree node to be added in the queue.

  huffmanTree * new = (huffmanTree*) malloc(sizeof(huffmanTree));
  new->element = c;
  new->freq = f;
  new->left = NULL;
  new->right = NULL;
  return new;

}

long int *buildFrequency(FILE * input){ // Creates the frequency array.

  long int * frequency = (long int *) calloc(ASCII_SIZE, sizeof(long int));
  unsigned char currentByte;
  FILE * auxiliar = input;

  while(fscanf(auxiliar,"%c",&currentByte) != EOF){
    frequency[currentByte] ++;
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

  return (huffmanTree*)priorityQueue->head->item;
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

FILE *OpenFile(char name[]){
    printf("Type the input file name:\n");
    fgets(name,100,stdin);
    int l = strlen(name);
    name[l-1] = '\0';

    return fopen(name, "rb");
}

// v ------ COMPRESS ------ v

void printTreeInFile(huffmanTree *tree, int *treeSize, FILE *FileBits){

  if(tree == NULL) return;

  (*treeSize) ++;

  if( isLeaf(tree) ){
    if(tree->element == '*' || tree->element == '\\'){
      unsigned char aux = '\\';
      fprintf(FileBits, "%c", aux);
      (*treeSize)++;
    }

    fprintf(FileBits, "%c", tree->element);
    return;
  }

  fprintf(FileBits,"%c", tree->element);

  printTreeInFile(tree->left, treeSize, FileBits);
  printTreeInFile(tree->right, treeSize, FileBits);
}

void SetBit(unsigned char *bits, unsigned char binary, int pos){
  if(binary == '1'){
    unsigned char mask = 1 << (8 - pos);
    *bits = mask | *bits;
  }
}

void Compressing(FILE *FileToCompress, FILE *FileBits, hash *hashTable, long long int *Setted_Bits){
  unsigned char character, bits = 0;

  while( fscanf(FileToCompress, "%c", &character) != EOF ){

    int i = 0;
    while( hashTable->items[character]->binaryCode[i] != '\0' ){

      (*Setted_Bits) ++;
      SetBit(&bits, hashTable->items[character]->binaryCode[i], 
             (*Setted_Bits) % 8 == 0 ? 8 : (*Setted_Bits) % 8 );

      if( (*Setted_Bits) % 8 == 0 ){ //Byte is setted
        fprintf(FileBits, "%c", bits);
        bits = 0;
      }

      i++;
    }

  }

  if( (*Setted_Bits) % 8 ){
    fprintf(FileBits, "%c", bits);
    bits = 0;
  }

}

void printTrashAndTreeSize(int treeSize, long long int Setted_Bits, FILE *FileBits){
  unsigned char first = 0, second = 0;
  int pos, trash = 8 - (Setted_Bits % 8);

  if (trash == 8) trash = 0;
  
  for(pos = 0; pos < 3; pos++){
    if( trash % 2 ){
      unsigned char mask = 1 << (pos + 5);
      first = mask | first;
    }
    trash /= 2;
  }

  for(pos = 0; pos < 8; pos++){
    if( treeSize % 2 ){
      unsigned char mask = 1 << pos;
      second = mask | second;
    } 
    treeSize /= 2;
  }

  for(pos = 0; pos < 5; pos ++){
    if( treeSize % 2 ){
      unsigned char mask = 1 << pos;
      first = mask | first;
    }
    treeSize /= 2;
  }

  fprintf(FileBits, "%c%c", first, second);
}

void StartCompress(hash *hashTable, huffmanTree *root, FILE *FileToCompress, char name[]){
  rewind(FileToCompress);
  strcat(name,".huff");
  FILE *FileBits = fopen(name, "wb");
  fseek(FileBits, 2*sizeof(unsigned char), SEEK_SET);

  int treeSize = 0;
  printTreeInFile(root, &treeSize, FileBits);

  long long int Setted_Bits = 0;
  Compressing(FileToCompress, FileBits, hashTable, &Setted_Bits);
  rewind(FileBits);

  printTrashAndTreeSize(treeSize, Setted_Bits, FileBits);

  fclose(FileToCompress);
  fclose(FileBits);
}

void compressMain(){

  char name[100];
  FILE *inputFile = OpenFile(name); // Opening the input file in binary read mode.
  long int * frequencyArray;
  huffmanTree * huffmanRoot;
  pqueue * priorityQueue = createPriorityQueue();
  node * pqueueHead;

while(1){
    if(inputFile==NULL){
      printf("ERROR: there is no file with the name typed. Type again the file's name.\n");
      inputFile = OpenFile(name);
    }
    else{
      printf("File found.\n");
      frequencyArray = buildFrequency(inputFile);
      int i;
      huffmanTree * auxiliar;

      for(i = 0; i < ASCII_SIZE; i++){
        if(frequencyArray[i]){           // Adds a new node to the heap if the frequency of the char is >= 1.
          auxiliar = newNode( i, frequencyArray[i]);
          priorityEnqueue(priorityQueue,auxiliar);
        }
      }

      pqueueHead = priorityQueue->head;

      huffmanRoot = buildHuffmanTree(priorityQueue);

      free(priorityQueue);

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

      StartCompress(hashTable, huffmanRoot, inputFile, name);
      eraseHash(hashTable);
      eraseTree(huffmanRoot);

      printf("ok\n");
      return;
    }
  }
}

// ^ ------ COMPRESS ------ ^

// V ------ INTERFACE ------ V

void header(){
  printf("|------------------------------------------------------------------------------------------------|\n");
  printf("| **     **  **    **  ********   ********       **       **               **        ****     ** |\n");
  printf("| **     **  **    **  **         **           ** **    ** **            ** **       ** **    ** |\n");
  printf("| **     **  **    **  **         **          **    ** **   **          **   **      **  **   ** |\n");
  printf("| *********  **    **  ********   ********   **      **      **        *********     **   **  ** |\n");
  printf("| **     **  **    **  **         **        **                **      **       **    **    ** ** |\n");
  printf("| **     **  **    **  **         **       **                  **    **         **   **     **** |\n");
  printf("| **     **  ********  **         **      **                    **  **           **  **       ** |\n");
  printf("|                                                                                                |\n");
  printf("|                       Joao Victor - Lucas Massa - William Philippe                             |\n"); 
  printf("|------------------------------------------------------------------------------------------------|\n");
}

void options(){
  printf("Choose an option by typing the corresponding number:\n");
  printf("(1) -> COMPRESS.\n");
  printf("(2) -> DECOMPRESS.\n");
  printf("(3) -> EXIT PROGRAM.\n");
}
