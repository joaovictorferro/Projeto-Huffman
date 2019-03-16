#include "compress.h"

#define ASCII_SIZE 256

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

  while(((node*)priorityQueue->head)->next != NULL){                    

    first_dequeued = priorityDequeue(priorityQueue);
    second_dequeued = priorityDequeue(priorityQueue);

    frequency = (first_dequeued->freq) + (second_dequeued->freq);

    huffmanTree * enqueued = newNode('*',frequency);

    enqueued->left = first_dequeued;
    enqueued->right = second_dequeued;

    priorityEnqueue(priorityQueue,enqueued);
  }

  return (huffmanTree*)((node*)priorityQueue->head)->item;
}

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
    while(((unsigned char *)((helement*)hashTable->items[character])->binaryCode)[i] != '\0' ){

      (*Setted_Bits) ++;
      SetBit(&bits, ((unsigned char *)((helement*)hashTable->items[character])->binaryCode)[i], 
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

while(1)
  {
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
        if(((helement*)hashTable->items[i])->characterFrequency){
          printf("%c %s\n", i, (unsigned char *)((helement*)hashTable->items[i])->binaryCode);
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