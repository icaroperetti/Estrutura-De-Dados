#include <stdio.h>
#include <stdlib.h>

/*
    Estrutura de Dados 1
    Lista Simplesmente Encadeada
    Aluno: Icaro Peretti
*/

typedef struct sElemento{
  struct sElemento *next;
  int dado;
} Elemento;

typedef struct sLista{
  struct sElemento *head;
  struct sElemento *tail;
  int size;
} Lista;

Lista* criaLista();
Elemento* criaElemento();
void insereLista(Lista* , Elemento*, int);
Elemento* remove(Lista*, Elemento*);
Elemento* buscaLista(Lista*, int );
void imprimeLista(Lista*);


int main(){
  Lista *lista = criaLista();
  Elemento *elemento = criaElemento();
	insereLista(lista,lista->head,5);
	insereLista(lista,lista->tail,50);
	insereLista(lista,lista->head->next,15);
  //remove(lista,lista->tail);
  //remove(lista,lista->head);
  // remove(lista,NULL);
  elemento = buscaLista(lista, 15);
  printf("Encontrado:%i\n", elemento->dado);
  imprimeLista(lista);

}

Lista* criaLista(){
  Lista *lista = (Lista*) malloc(sizeof(Lista));
  lista->head=NULL;
  lista->tail=NULL;
  lista->size=0;
  return lista;
}

Elemento* criaElemento(){
  Elemento *elemento;
  elemento = (Elemento*) malloc (sizeof(Elemento));
  return elemento;
}

void insereLista(Lista *lista, Elemento *pivo, int valor){
  Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
  novo->dado = valor;
  if(pivo == NULL){
    if(lista->size == 0){
      lista->tail= novo; 
    }
    novo->next = lista->head;
    lista->head = novo;
  }else{
    if(pivo->next==NULL){
      lista->tail = novo;
    }
    novo->next = pivo->next;
    pivo->next = novo;
  }
  lista->size++;
}

Elemento* remove(Lista *lista, Elemento *pivo){
  Elemento *antigo = (Elemento*) malloc (sizeof(Elemento));
  if(lista->size == 0){
    return NULL; //Vazia
  }
  if(pivo == NULL){
    antigo = lista->head;
    lista->head = lista->head->next;

    if(lista->head==NULL){
      lista->tail = NULL; 
    }
  }else{
    if(pivo->next==NULL){
      return NULL; //Fim
    }
    antigo = pivo->next;
    pivo->next = pivo->next->next;

    if(pivo->next==NULL){
      pivo = lista->tail;
    }
  }
  free(antigo);
  lista->size--;
  return antigo;
}


Elemento* buscaLista(Lista *lista, int dado){
  Elemento *pivo = (Elemento*)malloc(sizeof(Elemento));
  pivo=lista->head;
  int i = 0;
  for ( i = 0; i < lista->size; i++){
    if(pivo->dado == dado){
      return pivo;
    }
    pivo = pivo->next;
  }
  return NULL; 
}

void imprimeLista(Lista *lista){
	Elemento *aux=(Elemento*)malloc(sizeof(Elemento));
	aux=lista->head;
	int i=0;
  printf("Lista completa:");
	for(i=0;i<lista->size;i++){
		printf("%i ",aux->dado);
		aux=aux->next;
	}
}

