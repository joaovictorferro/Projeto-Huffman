#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct graph_adt Graph;
typedef struct stack_adt Stack;
typedef struct list_adt node;

struct list_adt{
  int n;
  node * next;
};

struct stack_adt{
  node * top;
};

struct graph_adt{
  node ** adjList;
  short * visited;
  int vertices;
};

node* addListCres(node *head, int x){

  node *new = (node*)malloc(sizeof(node));
  new->n = x;
  new->next = NULL;
  
  if(head==NULL){
    new->next = head;
    return new;
  }

  node * aux = head;
  node * previous = NULL;

  while(aux!=NULL){
    if(aux->n > x)break;
    previous = aux;
    aux = aux->next;
  }

  new->next = aux;

  if(previous==NULL){
    return new;
  }

  new->next = aux;
  previous->next = new;
  return head;
}

void eraseList(node *head){

  node *aux;

  while(head!=NULL){
    aux = head;
    head = head->next;
    free(aux); 
  }
}

Stack * createStack(){
  Stack * new = (Stack*)malloc(sizeof(Stack));
  new->top = NULL;
  return new;
}

void push(Stack * stack, int item){
  node * new = (node*)malloc(sizeof(node));
  new->n = item;
  new->next = stack->top;
  stack->top = new;
}

int pop(Stack * stack){
  if(stack->top==NULL){
    printf("Underflow\n");
    return -1;
  }
  int aux = stack->top->n;
  node * current = stack->top;
  stack->top = stack->top->next;
  free(current);
  return aux;
}

void eraseStack(Stack * stack){
  int aux;
  while(stack->top!=NULL){
    aux = pop(stack);
  }
  free(stack);
}

Graph * createGraph(int V){

 Graph * new = (Graph*)malloc(sizeof(Graph));
 new->adjList = (node**)calloc(V,sizeof(node*));
 new->visited = (short*)calloc(V,sizeof(short));
 new->vertices = V;

 return new;
}

void addEdge(Graph * graph, int v1, int v2){

  graph->adjList[v1] = addListCres(graph->adjList[v1],v2);

}

void dfs(Graph * graph, int source, Stack * stack){
  graph->visited[source] = 1;
  node * list = graph->adjList[source];

  while(list != NULL){
    if(!graph->visited[list->n]){
      dfs(graph,list->n,stack);
    }
    list = list->next;
  }

  push(stack,source);
}

void printStack(Stack * stack){
  node * list = stack->top;

  while(list!=NULL){
    printf("%d ", list->n);
    list = list->next;
  }
  printf("\n");
}

void topologicalSort(Graph * graph, Stack * stack){
  int i;

  for(i=0;i<graph->vertices;i++){
    if(!graph->visited[i]){
      dfs(graph,i,stack);
    }
  }
}

void eraseGraph(Graph * graph){
  int i;

  for(i=0;i<graph->vertices;i++){
    eraseList(graph->adjList[i]);
  }
  free(graph->visited);
  free(graph);
}

void main(){

  int V = 8;

  Graph * graph = createGraph(V);

  addEdge(graph,0,1);
  addEdge(graph,0,2);
  addEdge(graph,0,3);
  addEdge(graph,1,6);
  addEdge(graph,2,5);
  addEdge(graph,3,5);
  addEdge(graph,5,6);

  Stack * stack = createStack();

  topologicalSort(graph,stack);

  printf("Topological Sort result:\n");
  printStack(stack);

  eraseStack(stack);
  eraseGraph(graph);
}