#include "hash.h"

#define ASCII_SIZE 256

hash *createHash(int maximumSize)
{
  hash * new = (hash *) malloc(sizeof(hash));
  int i;
  for(i = 0; i < ASCII_SIZE; i++){
    new->items[i] = (helement *) malloc(sizeof(helement));
    ((helement*)new->items[i])->characterFrequency = 0;
    ((helement*)new->items[i])->binaryCode = (unsigned char *) calloc(maximumSize,sizeof(unsigned char)); 
  }
  return new;
}

void buildHash(hash *hashTable, huffmanTree *huffmanNode, int position, unsigned char *auxiliarString){

  if(isLeaf(huffmanNode)){
    auxiliarString[position] = '\0';
    strncpy(((helement*)hashTable->items[huffmanNode->element])->binaryCode,auxiliarString,position+1);
    ((helement*)hashTable->items[huffmanNode->element])->characterFrequency = huffmanNode->freq;
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
    free(((helement*)hashTable->items[i])->binaryCode);
    free(hashTable->items[i]);
  }
  free(hashTable);
}