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
int filaVazia(Queue*);
int removeDaFila(Queue*);
void destroiFila(Queue*);

int main(){
  Queue *queue = criaFila();
  int removido;

  insereNaFila(queue,20);
  insereNaFila(queue,25);
  insereNaFila(queue,30);
  insereNaFila(queue,35);
  printf("Size:%i\n",queue->size);
  //removido = removeDaFila(queue);
  //printf("Removido: %i\n",removido);
  escreveFila(queue);
  destroiFila(queue);
  
}

void destroiFila(Queue* queue){
    Elemento *elemento;
    elemento = queue->front;
    while(queue->size > 0){
        removeDaFila(queue);
    }
    printf("\nSize:%i",queue->size);
    free(queue);
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

//Função para verificar se a fila está vazia
int filaVazia(Queue* queue){
	if(queue->front == NULL && queue->rear == NULL){
    return 1;
  }else{
    return 0;
  }
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
  if(queue->front == NULL && queue->rear == NULL){
    queue->front = novo;
    queue->rear = novo;
  }else{
   novo->prev = queue->rear;
   queue->rear->next = novo;
   queue->rear = novo;
  } 
  queue->size++;
}

int removeDaFila(Queue* queue){
  int dado;
  Elemento *antigo;
  if(queue->size == 0){
    printf("A fila esta vazia");
    return 0;
  }
  antigo = queue->front;
  queue->front = queue->front->next;
  dado = antigo->dado;
  free(antigo);
  queue->size--;
  return dado;
}

void escreveFila(Queue* queue){
   Elemento* aux;
    aux = queue->front;
    printf("Inseridos: ");
    for(int i = 0; i < queue->size; i++){
        printf("%i ", aux->dado);
        aux = aux->next;
    }
}
