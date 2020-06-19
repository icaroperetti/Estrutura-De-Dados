/*
    Exercicio 1
    Icaro Peretti
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUE 10

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

Carro* buscaCarro(Estacionamento* ,int );
Estacionamento* criaEstacionamento();
Carro* criaCarro(int);
void insereCarro(Estacionamento* ,Estacionamento* ,int );
void addEspera(Estacionamento* ,int);
void removeCarro(Estacionamento* ,Estacionamento* ,int );
void imprime(Estacionamento* );
void destroiEstacionamentoeEspera(Estacionamento* ,Estacionamento* );

int main(){
	int placa;
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
	insereCarro(estacionamento,espera,7);
	insereCarro(estacionamento,espera,8);
	insereCarro(estacionamento,espera,9);
	insereCarro(estacionamento,espera,10);

	insereCarro(estacionamento,espera,11);
	

    	removeCarro(estacionamento,espera,2);
	removeCarro(estacionamento,espera,8);
	removeCarro(estacionamento,espera,9);
	removeCarro(estacionamento,espera,10);

	imprime(estacionamento);
	destroiEstacionamentoeEspera(estacionamento,espera);
	
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
        printf("Carro adicionado a espera:%i\n",placa);
        espera->size++;
}

void removeCarro(Estacionamento* estacionamento,Estacionamento* espera,int placa){
	Carro *carro,*aux;
	int auxPlaca;
	int deslocamentos;

	carro = buscaCarro(estacionamento,placa);
	if(carro > 0){
		aux = carro->prev;
		auxPlaca = carro->placa;
		deslocamentos = carro->deslocamentos;
		while(aux > 0){
			aux->deslocamentos++;
			aux = aux->prev;	
		}
		if(carro == estacionamento->front){
			estacionamento->front = carro->next;
			if(estacionamento->size == 1){
				estacionamento->rear = NULL;
			}else{
				
				carro->next->prev = NULL;
			}		
		}else if(carro == estacionamento->rear){
			
			estacionamento->rear = carro->prev;
			carro->prev->next = NULL;
			
		}else{
			carro->prev->next = carro->next;
			carro->next->prev = carro->prev;
		}
		estacionamento->size--;
        printf("\nCarro %i deixou o estacionamento\nDeslocamentos:%i\n",placa,deslocamentos+1);
        free(aux);
	}else{
		carro = buscaCarro(espera,placa);
		if(carro > 0){
			if(carro == espera->front){
			espera->front = carro->next;
			
			if(espera->size == 1){
				espera->rear = NULL;
			}else{
				carro->next->prev = NULL;
			}

			}else if(carro == espera->rear){
			
			espera->rear = carro->prev;
			carro->prev->next = NULL;
			
			}else{
			
			carro->prev->next = carro->next;
			carro->next->prev = carro->prev;
			
			}
			espera->size--;
			free(carro);
			
		}else{
			printf("Carro nao encontrado");
		}	
	}
	
	if(estacionamento->size < MAXQUEUE && espera->size > 0){
		auxPlaca = espera->front->placa;
		removeCarro(estacionamento,espera,auxPlaca);
		insereCarro(estacionamento,espera,auxPlaca);
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

void imprime(Estacionamento* estacionamento){
	Carro* carro;
	carro = estacionamento->front;
	printf("Carros no estacionamento:");
	while(carro != NULL){
		printf(" %i ",carro->placa);
		carro = carro->next;
	}
}

void destroiEstacionamentoeEspera(Estacionamento *est, Estacionamento *espera){
    Carro *carro;
    while(est->size != 0){
        carro = est->front;
        est->front = carro->next;
        if(est->front==NULL){
            est->rear=NULL;
        }else{
            carro->next->prev=NULL;
        }
	free(carro);
        est->size--;
        printf("\nRemovido: %i - Size estacionamento:%i", carro->placa,est->size);
    }
    
    while(espera->size != 0){
        carro = espera->front;
        espera->front = carro->next;
        if(espera->front==NULL){
            espera->rear=NULL;
        }else{
            carro->next->prev=NULL;
        }
	free(carro);
        espera->size--;
        printf("Removido:%i - Size espera:%i", carro->placa, espera->size);
    }    
    free(est);
    free(espera);
}
