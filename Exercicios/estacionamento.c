#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUE 5

typedef struct sCarro{
	struct sCarro *next;
	struct sCarro *prev;
	int deslocamentos;
	int placa;
}Carro;


typedef struct sEstacionamento{
	struct sCarro *front;
	struct sCarro *rear;
	int size;
}Estacionamento;

Carro* buscaCarro(Estacionamento* est,int placa);
Estacionamento* criaEstacionamento();
Carro* criaCarro(int placa);
void insereCarro(Estacionamento* estacionamento,Estacionamento* espera,int placa);
void addEspera(Estacionamento* espera,int placa);
void removeCarro(Estacionamento* estacionamento,Estacionamento* espera,int placa);

int main(){
    Estacionamento* estacionamento;
	estacionamento = criaEstacionamento();
	
	Estacionamento* espera;
	espera = criaEstacionamento();

    insereCarro(estacionamento,espera,1);
	insereCarro(estacionamento,espera,2);
    insereCarro(estacionamento,espera,3);
	insereCarro(estacionamento,espera,4);
    insereCarro(estacionamento,espera,5);
	insereCarro(estacionamento,espera,6);

    removeCarro(estacionamento,espera,1);


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


Carro* criaCarro(int placa){
	
	Carro* carro;
	carro = (Carro*)malloc(sizeof(Carro*));
	carro->deslocamentos = 0;
	carro->placa = placa;
	carro->next = NULL;
	carro->prev = NULL;	
	return carro;
	
}	

void insereCarro(Estacionamento* estacionamento,Estacionamento* espera,int placa){
	
	Carro* novo_carro;
	novo_carro = criaCarro(placa);
	
	if(estacionamento->size < MAXQUEUE){
		if(estacionamento->rear == NULL){
			estacionamento->front = novo_carro;
			estacionamento->rear = novo_carro;	
			
		}else{
			novo_carro->prev = estacionamento->rear;
			estacionamento->rear->next = novo_carro;
			estacionamento->rear = novo_carro;
		}
        printf("Carro estacionado:%i\n",placa);
        estacionamento->size++;
    }else{
        addEspera(espera,placa);
    }
}

void addEspera(Estacionamento* espera,int placa){
    Carro* novo_carro;
    novo_carro = criaCarro(placa);
    if(espera->rear == NULL){
			espera->front = novo_carro;
			espera->rear = novo_carro;
		}else{
			novo_carro->prev = espera->rear;
			espera->rear->next = novo_carro;
			espera->rear = novo_carro;	
		}
        printf("Carro adicionado a espera:%i",placa);
        espera->size++;
}

void removeCarro(Estacionamento* estacionamento,Estacionamento* espera,int placa){
	Carro *carro;
	Carro *aux;
	int placa_aux;
	int numDeslocamentos;

	carro = buscaCarro(estacionamento, placa);

	if (carro != NULL){

		aux = carro->prev;
		placa_aux = carro->placa;
		numDeslocamentos = carro->deslocamentos;

		while (aux != NULL){

			aux->deslocamentos++;

			aux = aux->prev;
		}

		if (carro == estacionamento->front){

			estacionamento->front = carro->next;

			if (estacionamento->size == 1){

				estacionamento->rear = NULL;
			}
			else{

				carro->next->prev = NULL;
			}
		}
		else if (carro == estacionamento->rear){

			estacionamento->rear = carro->prev;
			carro->prev->next = NULL;
		}
		else{

			carro->prev->next = carro->next;
			carro->next->prev = carro->prev;
		}
		estacionamento->size--;
		printf("Carro saiu:%i\nDeslocamento:%i", placa, numDeslocamentos + 1);
	}
}

Carro* buscaCarro(Estacionamento* est,int placa){
	Carro* carro;
	carro = est->front;
	while(carro != NULL){
		if(carro->placa == placa ){
			return carro;
		}
		carro = carro->next;
	}
	
}
