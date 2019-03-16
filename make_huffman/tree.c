#include "tree.h"

#define ASCII_SIZE 256

int max(int a, int b){
  return a >= b ? a : b;
}

int height(huffmanTree *tree)
{
  if(tree == NULL) return -1;
  return 1 + max( height(tree->left), height(tree->right));
}

void printTree(huffmanTree *tree){

  if(tree==NULL) return;

  printf("%c", tree->element);
  printTree(tree->left);
  printTree(tree->right);
}

int isLeaf(huffmanTree *treeNode)
{
  return (!treeNode->left && !treeNode->right);
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

huffmanTree *newNode(unsigned char c, long int f){ // Creates a new huffman tree node to be added in the queue.

  huffmanTree * new = (huffmanTree*) malloc(sizeof(huffmanTree));
  new->element = c;
  new->freq = f;
  new->left = NULL;
  new->right = NULL;
  return new;

}