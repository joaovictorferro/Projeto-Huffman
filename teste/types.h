#define MAX_HEAP_SIZE 257

struct heap_adt
{
  int size;
  huffmanTree * data[MAX_HEAP_SIZE];
};

typedef struct heap_adt heap;

/*
	Comentar aqui
*/

struct huffmanTree
{
  int freq;
  char element;
  huffmanTree * left;
  huffmanTree * right;
};

typedef struct huffmanTree huffmanTree;
/*
Comentar aqui
*/