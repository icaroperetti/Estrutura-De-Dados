#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct sQueue{
  struct sElemento *front;
  struct sElemento *rear;
  int size;
} Queue;

typedef struct sElemento{
  struct sElemento *next;
  struct sElemento *prev;
  int dado;
} Elemento;

Queue* criaFila();
void insereNaFila(Queue* queue, int dado);
Elemento* criaElemento(int dado);
void escreveFila(Queue* queue);


int main(){
  Queue *queue = criaFila();

  insereNaFila(queue,20);
  insereNaFila(queue->front,25);
  escreveFila(queue);
}

Queue* criaFila(){
  Queue *queue;
  queue = (Queue*)malloc(sizeof(Queue));
  if(queue == NULL){
    printf("Nao foi possivel alocar memoria");
    return 0;
  }
  queue->front = NULL;
  queue->rear = NULL;
  queue->size = 0;
  return queue;
}

Elemento* criaElemento(int dado){
  Elemento* elemento;
  elemento = (Elemento*) malloc (sizeof(Elemento));
  if(elemento == NULL){
    printf("Nao foi possivel alocar memoria");
    return 0;
  }
  elemento->next = NULL;
  elemento->prev = NULL;
  elemento->dado = dado;
  return elemento;
}

void insereNaFila(Queue *queue, int dado){
  Elemento *novo;
  novo = criaElemento(dado);
  if (queue->size < MAX){
    queue->front = novo;
    queue->rear = novo;
  }
  else{
    if (queue->size > 0){
      novo->prev = queue->front;
      queue->front->next = novo;
      novo->next = NULL;
      queue->rear = novo;
    }
    else{
      novo->prev = queue->rear;
      novo->next = NULL;
      queue->rear->next = novo;
      queue->rear = novo;
    }
  }
  queue->size++;
}

void escreveFila(Queue* queue){
    Elemento* elemento;
    elemento = queue->front;
    printf("Valores inseridos:");
    while(queue->size > 0){
        printf("%i -> ", elemento->dado);
        elemento = elemento->next;
    }
}
