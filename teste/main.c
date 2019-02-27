#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include "heap.h"
#include "tree.h"
#include "types.h"

int * buildFrequency(FILE * input)
{

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

void main()
{

  printf("Type the input file name:\n");

  char inputFileName[50];
  getFileName(inputFileName); // Reading the input file name from the user.

  FILE * inputFile  = fopen(inputFileName,"rb"); // Opening the input file in binary read mode.

  int * frequencyArray;

  huffmanTree * huffmanRoot;

  heap * h = createHeap(); 

  if(inputFile==NULL)
  {
    printf("ERROR: there is no file with the name typed.\n");
  }
  else{
    printf("File found.\n");
    frequencyArray = buildFrequency(inputFile);
    int i;
    huffmanTree * auxiliar;

    for(i=0;i<ASCII_SIZE;i++)
    {
      if(frequencyArray[i])
      {           // Adds a new node to the heap if the frequency of the char is >= 1.
        auxiliar = newNode(i,frequencyArray[i]);
        enqHeapMin(h,auxiliar);
      }
    }

    if(DEBUG_HEAP){
      for(i=1;i<=h->size;i++)
      {
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