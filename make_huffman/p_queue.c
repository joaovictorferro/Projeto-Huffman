#include "p_queue.h"

pqueue *createPriorityQueue()
{
  pqueue * new = (pqueue*) malloc(sizeof(pqueue));
  new->head = NULL;
  return new;
}

void priorityEnqueue(pqueue *priorityQueue, huffmanTree *newTreeNode){

  node * new = (node*) malloc(sizeof(node));
  new->item = newTreeNode;

  if(priorityQueue->head == NULL || ((huffmanTree*)new->item)->freq <= ((huffmanTree*)priorityQueue->head->item)->freq){
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

huffmanTree * priorityDequeue(pqueue *priorityQueue){

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
