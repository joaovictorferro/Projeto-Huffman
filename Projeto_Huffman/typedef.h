# define  MAX_HEAP_SIZE  257

struct heap_adt
{
  tamanho int ;
  huffmanTree * data [MAX_HEAP_SIZE];
};

typedef  struct heap_adt heap;

/ *
	Comentar aqui
* /

struct huffmanTree
{
  int freq;
  elemento char ;
  huffmanTree * à esquerda;
  huffmanTree * certo;
};

typedef  struct huffmanTree huffmanTree;
/ *
Comentar aqui
* /