/*
    Exercicio 2 e 3
    Ícaro Peretti
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento {
    struct sElemento *next;
    struct sElemento *prev;
    int dado;
} Elemento;

typedef struct sApq {
    struct sElemento *front;
    struct sElemento *rear;
    int size;
} Apq;

Apq* criaAPq();
void apqInsert(Apq*, int );
void imprime(Apq*);
int apqSearchMin(Apq*);
int apqMinDelete(Apq*);
void destroiApq(Apq*);
int empty(Apq*);

int main(){
    int removido,menor;
    Apq* apq = criaAPq();

    empty(apq); //Verificando antes de inserir

    printf("Inserindo elementos\n\n");
    apqInsert(apq,10);
    apqInsert(apq,20);
    apqInsert(apq,30);
    apqInsert(apq,40);
    apqInsert(apq,1);

    empty(apq); //Verificando depois de inserir
    
    menor = apqSearchMin(apq);
    printf("Menor valor:%i\n",menor);

   
    imprime(apq);

    
    removido = apqMinDelete(apq);
    printf("\nRemovido: %i\n",removido);

    removido = apqMinDelete(apq);
    printf("Removido: %i\n\n",removido);

    imprime(apq);

    destroiApq(apq);
    
    return 0;  
}

void destroiApq(Apq* apq){
    int dado;
    printf("Destruindo!\n");
    while(apq->size > 0){
        dado = apqMinDelete(apq);
        printf("Removido: %i - Size: %i\n",dado,apq->size);
    }
    free(apq);
}

Apq* criaAPq(){
    Apq* apq;
    apq = (Apq*)malloc(sizeof(Apq));
    if(apq == NULL){
        printf("Memoria nao alocada 1");
    }
    apq->front = NULL;
    apq->rear = NULL;
    apq->size = 0;
    return apq;
}

Elemento* criaElemento(int dado){
    Elemento *elemento;
    elemento = (Elemento*)malloc(sizeof(Elemento));
     if(elemento == NULL){
        printf("Memoria nao alocada 2");
    }
    elemento->next = NULL;
    elemento->dado = dado;
    return elemento;
}

void apqInsert(Apq* apq, int dado){
    Elemento* novo;
    Elemento* pivo;
    novo = criaElemento(dado);
    if ((apq->front == NULL) && (apq->rear == NULL)){
        apq->front = novo;
        apq->rear = novo;
    }
    else{
        novo->prev = apq->rear;
        apq->rear->next = novo;
        apq->rear = novo;
    }
    apq->size++;
}


int apqMinDelete(Apq* apq){
    Elemento *elemento, *min;
    int dado;
    min = apq->front;
    elemento = apq->front;
    while (elemento != NULL){
        if (elemento->dado < min->dado){
            min = elemento;
        }
        elemento = elemento->next;
    }
   
    if ((min != 0) && (apq->size > 0)){
        if (min == apq->front) {
            apq->front = min->next;
            if (apq->front == NULL){
                apq->rear = NULL;
            }
            else{
                min->next->prev = NULL;
            }
        }
        else{
            min->prev->next = min->next;
            if (min->next == NULL){
                apq->rear = min->prev;
            }
            else{
                min->next->prev = min->prev;
            }
        }
        dado = min->dado;
        free(min);
        apq->size--;
        return dado;
    }
}

int apqSearchMin(Apq* apq){
    Elemento *elemento,*min;
    min = apq->front;
    elemento = apq->front;
    while(elemento != NULL){
        if(elemento->dado < min->dado){
            min = elemento;
        }
        elemento  = elemento->next;
    }
    return min->dado;
}

int empty(Apq* apq){
    if(apq->size > 0){
       printf("Fila nao esta vazia\n");
    }else{
        printf("Fila vazia\n");
        return 0;
    }
}

void imprime(Apq* apq){
    Elemento* elemento;
    elemento = apq->front;
    printf("Dados da fila: ");
    while(elemento != NULL){
        printf("%i ",elemento->dado);
        elemento = elemento->next;
    }
    printf("\n");
}
