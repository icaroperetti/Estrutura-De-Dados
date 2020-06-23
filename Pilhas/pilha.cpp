#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACKSIZE 5

typedef struct sElemento{ 
    struct sElemento *next;
    struct sElemento *prev;
    int dado; 
} Elemento;

typedef struct sPilha{ 
    struct sElemento *head;
    struct sElemento *tail; 
    int size;
} Pilha;

Pilha* criaPilha();
Elemento* criaElemento(int dado);
void push(Pilha* pilha,int dado);
void imprimePilha(Pilha* pilha);
bool isEmpty(Pilha* pilha);
int pop(Pilha* pilha);

int main(){
    Pilha* pilha = criaPilha();
    int removido,removido1;
    push(pilha,10);
    push(pilha,20);
    push(pilha,30);
    imprimePilha(pilha);

}

Pilha* criaPilha(){
    Pilha* pilha;
    pilha = (Pilha*)malloc(sizeof(Pilha));
    if(pilha == NULL){
        printf("Memoria nao alocada");
    }
    pilha->head = NULL;
    pilha->tail = NULL;
    pilha->size = 0;
    return pilha;
}

Elemento* criaElemento(int dado){
    Elemento* elemento;
    elemento = (Elemento*)malloc(sizeof(Elemento));
    elemento->next = NULL;
    elemento->prev = NULL;
    elemento->dado = dado;
    return elemento;
}

void push(Pilha* pilha,int dado){
    Elemento *novo = criaElemento(dado);
    if(pilha->size >= STACKSIZE){
        printf("Pilha cheia\n");
    }else{
        novo->next = pilha->head;
        pilha->head = novo;
        printf("Inserido:%i\n",novo->dado);
    }
    pilha->size++;
}

int pop(Pilha* pilha){
   
}

void imprimePilha(Pilha* pilha){
    Elemento *aux = pilha->head;
    printf("Pilha: ");
    while(aux != NULL){
        printf("%i ",aux->dado);
        aux = aux->next;
    }
    printf("\n");
}

bool isEmpty(Pilha* pilha){
    if(pilha->head == NULL){
        return true;
    }else{
        return false;
    }
}
