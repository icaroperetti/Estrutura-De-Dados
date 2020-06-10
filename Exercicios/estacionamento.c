/*
Estacionamento de Scratchemup contém uma única alameda que guarda até dez carros. 
Os carros entram pela extremidade sul do estacionamento e saem pela extremidade norte. 
Se chegar um cliente para retirar um carro que não esteja estacionado na posição do extremo-norte, 
todos os carros ao norte do carro serão deslocados para fora, o carro sairá do estacionamento 
e os outros carros voltarão à mesma ordem em que se encontravam inicialmente. 
Sempre que um carro deixa o estacionamento, todos os carros ao sul são deslocados para frente, 
de modo que, o tempo inteiro, todos os espaços vazios estão na parte sul do estacionamento.
Escreva um programa que leia um grupo de linhas de entrada. 
Cada linha contém um 'C, de chegada, e um 'P', de partida, além de um número de placa de licenciamento. 
Presume-se que os carros chegarão e partirão na ordem especificada pela entrada. 
O programa deve imprimir uma mensagem cada vez que um carro chegar ou partir.
Quando um carro chegar, a mensagem deverá especificar se existe 
ou não vaga para o carro dentro do estacionamento. Se não existir vaga, o carro esperará pela 
vaga ou até que uma linha de partida seja lida para o carro. Quando houver espaço disponível, 
outra mensagem deverá ser impressa. 
Quando um carro partir, 
a mensagem deverá incluir o número de vezes que o carro foi deslocado dentro do estacionamento,
incluindo a própria partida, mas não a chegada. E
sse número será 0 se o carro for embora a partir da linha de espera.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXQUEUE 10

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


Carro* criaCarro(int placa);
Estacionamento* criaEstacionamento();
Espera* criaEspera();
void insereCarro(Estacionamento*, int);
void imprimeEstacionamento(Estacionamento* estacionamento);


int main(){
   Estacionamento *est= criaEstacionamento();
    Espera *espera = criaEspera();
    insereCarro(est,10);
    imprimeEstacionamento(est);
}

Carro* criaCarro(int placa){
    Carro *carro = (Carro*)malloc(sizeof(Carro));
    carro->placa= placa;
    carro->deslocamento=0;
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
    espera->size=0;
    return espera;
}

void insereCarro(Estacionamento *est, int placa){
    Carro *novo_carro = criaCarro(placa);
    if (est->front == NULL && est->rear == NULL){
        est->front = novo_carro;
        est->rear = novo_carro;
    }
    else{
        novo_carro->prev = est->rear;
        est->rear->next = novo_carro;
        est->rear = novo_carro;
    }
    est->size++;
}

void imprimeEstacionamento(Estacionamento* estacionamento){
    Carro* aux = (Carro*)malloc(sizeof(Carro));
    aux = estacionamento->front;
    printf("\nCarros no estacionamento %i\n", estacionamento->size);
    for(int i = 0; i < estacionamento->size; i++){
        printf("Placa:%i ", aux->placa);
        aux = aux->next;
    }
}
