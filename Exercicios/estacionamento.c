#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXQUEUE 5

typedef struct sEstacionamento{
  struct sCarro *front;
  struct sCarro *rear;
  int size;
} Estacionamento;

typedef struct sCarro{
  struct sCarro *next;
  struct sCarro *prev;
  int placa;
  int deslocamento;
} Carro;

typedef struct sEspera{
  struct sCarro *front;
  struct sCarro *rear;
  int size;
} Espera;


Carro* criaCarro(int);
Estacionamento* criaEstacionamento();
Espera* criaEspera();
void insereCarro(Estacionamento*,Espera*, int);
void imprimeEstacionamento(Estacionamento*);
void addEspera(Espera* ,Carro* );
void imprimeEspera(Espera* );
int removeCarro(Estacionamento* ,Espera*,int);
void imprimeDeslocamento(Estacionamento*);
int removeCarroEspera(Espera* esp,int placa);

int main(){
    //srand(time(NULL));
    int placa,removido;
    Estacionamento *est= criaEstacionamento();
    Espera *espera = criaEspera();

    insereCarro(est,espera,10);
    insereCarro(est,espera,20);
    insereCarro(est,espera,30);
    insereCarro(est,espera,40);
    insereCarro(est,espera,50);
    
    insereCarro(est,espera,60);
    insereCarro(est,espera,70);

    removido = removeCarro(est,espera,10);
    printf("Removido:%i\n",removido);

    removido = removeCarro(est,espera,20);
    printf("Removido:%i\n",removido);

    imprimeEstacionamento(est);
    imprimeEspera(espera);
}

Carro* criaCarro(int placa){
    //placa = rand() %100 + 100;
    Carro *carro =(Carro*)malloc(sizeof(Carro));
    carro->placa= placa;
    carro->deslocamento = 0;
    return carro;
}

Estacionamento* criaEstacionamento(){
    Estacionamento *estacionamento;
    estacionamento = (Estacionamento*)malloc(sizeof(Estacionamento));
    if (estacionamento == NULL){
        printf("Memoria nao alocada 1");
    }
    estacionamento->front = NULL;
    estacionamento->rear = NULL;
    estacionamento->size = 0;
    return estacionamento;
}


Espera *criaEspera(){
    Espera *espera = (Espera*)malloc(sizeof(Espera));
    if (espera == NULL){
        printf("Memoria nao alocada 2");
    }
    espera->front = NULL;
    espera->rear = NULL;
    espera->size = 0;
    return espera;
}

void insereCarro(Estacionamento *est,Espera* espera ,int placa){
    Carro *novoCarro = criaCarro(placa);
    if(est->size < MAXQUEUE){
        printf("Possuem %i vagas\n", MAXQUEUE - est->size);
        if (est->size == 0){
        est->front = novoCarro;
        est->rear = novoCarro;
    }
    else{
        novoCarro->prev = est->rear;
        est->rear->next = novoCarro;
        est->rear = novoCarro;
    }
    est->size++;
    printf("Carro estacionado\n\n");
    }
    else{
        printf("Estacionamento cheio!\n");
        addEspera(espera,novoCarro);
    }
}

void addEspera(Espera *espera,Carro *carro){
    if (espera->size == 0){
        espera->front = carro;
        espera->rear = carro;
    }
    else{
        carro->prev = espera->rear;
        espera->rear->next = carro;
        espera->rear = carro;
    }
    espera->size++;
}

int removeCarro(Estacionamento *est,Espera* esp,int placa){
    Carro *antigo, *removeDaEspera;
    antigo = est->front;
    int i, dado;
    if (est->size > 0){
        if (antigo == est->front){
            est->front = antigo->next;
            if (est->front == NULL){
                est->rear = NULL;
            }
            else{
                antigo->next->prev = NULL;
            }
        }
        else{
            antigo->prev->next = antigo->next;
        }
    }
    dado = antigo->placa;
    free(antigo);
    est->size--;
    return dado;
}


void imprimeEstacionamento(Estacionamento* estacionamento){
    Carro *aux;
    int i = 0;
    aux = estacionamento->front;
    printf("\nQuantidade de carros no estacionamento: %i\n", estacionamento->size);
    printf("Placas:");
    for( i = 0; i < estacionamento->size; i++){
        printf("%i ", aux->placa);
        aux = aux->next;
    }
    printf("\n\n");
}

void imprimeEspera(Espera* espera){
    Carro *aux;
    aux = espera->front;
    int i = 0;
    printf("Quantidade de carros em espera:%i\n", espera->size);
    printf("Placas dos carros em espera: ");
    for(i = 0; i< espera->size;i++){
        printf("%i ",aux->placa);
        aux = aux->next;
    }
}
