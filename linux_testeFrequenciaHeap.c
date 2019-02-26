#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 257

typedef struct heap_adt heap;
typedef struct list info;

struct list{
  int freq;
  char elemento;
};

struct heap_adt{
  int size;
  info * data[MAX];
};

void swap(info * a, info * b){ // Faz a troca dos elementos do no da heap minima.
  char caux; // char auxiliar 
  int faux;  // inteiro auxiliar.

  caux = a->elemento;
  a->elemento = b->elemento; // Troca a char elemento.
  b->elemento = caux;

  faux = a->freq;
  a->freq = b->freq; // Troca o int freq.
  b->freq = faux;
}

heap * createHeap(){ // Cria a heap.

  heap * new = (heap*)malloc(sizeof(heap));
  new->size = 0;
  return new;
}

int parentIndex(heap * h, int i){ // Calcula o indice do no pai.
  return (i>>1);
}

int leftIndex(heap * h, int i){ // Calcula o indice do filho da esquerda.
  return (i<<1);
}

int rightIndex(heap * h, int i){ // Calcula o indice do filho da direita.
  return ((i<<1)+1);
}

void enqHeap(heap * h, info * new){ // Adiciona um elemento na heap minima.

  if(h->size>=MAX){
    printf("overflow\n");
    return;
  }
  else{
    h->data[++h->size] = new;

    int keyIndex = h->size;
    int parent = parentIndex(h,h->size);

    while(parent >= 1 && h->data[keyIndex]->freq < h->data[parent]->freq){
      swap(h->data[keyIndex],h->data[parent]);
      keyIndex = parent;
      parent = parentIndex(h,keyIndex);
    }
  }
}

void minHeapify(heap * h, int i){ // Mantem a propriedade de heap minima apos se remover um elemento.
  int smallest;
  int left = leftIndex(h,i);
  int right = rightIndex(h,i);

  if(left <= h->size && h->data[left]->freq < h->data[i]->freq){
    smallest = left;
  }
  else{
    smallest = i;
  }
  if(right <= h->size && h->data[right]->freq < h->data[smallest]->freq){
    smallest = right;
  }

  if(h->data[i]->freq != h->data[smallest]->freq){
    swap(h->data[i],h->data[smallest]);
    minHeapify(h,smallest);
  }
}

info * deqHeap(heap * h){ // Remove um elemento da heap minima.

  if(!h->size){
    printf("underflow\n");
    return NULL;
  }
  else{
    info * item = h->data[1];
    h->data[1] = h->data[h->size];
    h->size --;
    minHeapify(h,1);
    return item;
  }
}

void eraseHeap(heap * h){ // Deleta a heap.

  int i;

  for(i=0;i<=MAX;i++){
    free(h->data[i]);
  }

  free(h);
}

info * newInfo(char c, int f, heap * h){ // Cria um novo ponteiro a ser adicionado na heap minima.

  info * new = (info*)malloc(sizeof(info));
  new->elemento = c;
  new->freq = f;
  return new;

}

void main(){

  char nome[20];
  char arquivo[20];
  unsigned char c;

  int frequencia[256] = {0}; // array que salva as frequencias de acordo com a ASCII.

  heap * h = createHeap();

  //printf("Digite o nome do arquivo:\n");

 // fgets(arquivo,20,stdin);

  FILE * fp;

  fp = fopen("teste.txt","r"); // abre o arquivo no modo leitura "r".
  rewind(fp);                  // DEVE-SE MUDAR O NOME DO ARQUIVO, NO PRIMEIRO ARGUMENTO
                               //  DA FOPEN, DE ACORDO COM AQUELE QUE SE DESEJA ABRIR.

  if(fp==NULL){
    printf("ERRO!\n");
  }
  else{
    c = fgetc(fp);
    while(!feof(fp)){
      frequencia[(int)c]++;
      c = fgetc(fp);
    }

    fclose(fp);

    int i; // indice.
    info * aux; // ponteiro auxiliar.

    for(i=11;i<256;i++){
      if(frequencia[i]){
        aux = newInfo(i,frequencia[i],h); // Cria o novo no.
        enqHeap(h,aux); // Adiciona o no na heap minima.
      }
    }

    for(i=1;i<=h->size;i++){
      printf("%d %c %d\n", h->data[i]->elemento, h->data[i]->elemento, h->data[i]->freq); // Imprime os elementos da heap minima.
    }

    eraseHeap(h);
  }
}