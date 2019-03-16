#define ASCII_SIZE 256

typedef struct huffmanTree huffmanTree;

struct huffmanTree
{
  long int freq;
  unsigned char element;
  void * left, *right;
};