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
void apqInsert(Apq* apq, int dado);
void imprime(Apq*);
int apqSearchMin(Apq*);
int apqMinDelete(Apq*);
void destroiApq(Apq*);

int main(){
    Elemento* removido;

    Apq* apq = criaAPq();

    apqInsert(apq,10);
    apqInsert(apq,20);
    apqInsert(apq,30);
    apqInsert(apq,40);
    apqInsert(apq,1);

    removido = apqMinDelete(apq);
    printf("Removido:%i\n",removido);

    imprime(apq);

    destroiApq(apq);
    
}

void destroiApq(Apq* apq){
    int dado;
    while(apq->size > 0){
        dado = apqMinDelete(apq);
        printf("Removido: %i - Size: %i\n",dado,apq->size);
    }
    free(apq);
}

Apq* criaAPq(){
    Apq* apq;
    apq = (Apq*)malloc(sizeof(Apq));
    apq->front = NULL;
    apq->rear = NULL;
    apq->size = 0;
    return apq;
}

Elemento* criaElemento(int dado){
    Elemento *elemento;
    elemento = (Elemento*)malloc(sizeof(Elemento));
    elemento->next = NULL;
    elemento->dado = dado;
    return elemento;
}

void apqInsert(Apq* apq, int dado){
    Elemento* novo;
    Elemento* pivo;
    novo = criaElemento(dado);
    if (apq->front == NULL && apq->rear == NULL){
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
    return min;
}

int apqMinDelete(Apq* apq){
    Elemento *remover,*pivo;
    int dado;
    remover = apqSearchMin(apq);
    if ((remover != NULL) && (apq->size != 0)){
        if (remover == apq->front){
            apq->front= remover->next;
            if (apq->front== NULL){
                apq->rear = NULL;
            }
            else{
                remover->next->prev = NULL;
            }
        }
        else{
            remover->prev->next = remover->next;
            if (remover->next == NULL){
                apq->rear = remover->prev;
            }
            else{
                remover->next->prev = remover->prev;
            }
        }
        dado = remover->dado;
        free(remover);
        apq->size--;
        return dado;
    }
}



void imprime(Apq* apq){
    Elemento* pivo;
    pivo = apq->front;
    printf("Dados da fila: ");
    while(pivo != NULL){
        printf("%i ",pivo->dado);
        pivo = pivo->next;
    }
    printf("\n");
}
