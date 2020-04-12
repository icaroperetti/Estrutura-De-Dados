#include <stdio.h>
#include <stdlib.h>


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
void insere(Lista *lista, Elemento *pivo, int valor);
int remove(Lista *lista, Elemento *pivo);
void imprimeLista(Lista *lista);


int main(){
  Lista *lista = criaLista();
  insere(lista,NULL,10);
    buscaLista();
    insere(lista,NULL,10);
    //insere(lista,lista->head,20);
    //insere(lista,lista->tail,30);
    //insere(lista,lista->head->next,25);
    //remove(lista,NULL);
    //remove(lista,lista->tail);
    //remove(lista,lista->head);
    imprimeLista(lista);
}

Lista* criaLista(){
  Lista *lista = (Lista*) malloc (sizeof(Lista));
  lista->head=NULL;
  lista->tail=NULL;
  lista->size=0;
  return lista;
}

void insere(Lista *lista, Elemento *pivo, int valor){
  Elemento *novo = (Elemento*) malloc (sizeof(Elemento));
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

int remove(Lista *lista, Elemento *pivo){
  Elemento *antigo = (Elemento*) malloc (sizeof(Elemento));
  if(lista->size == 0){
    return 1; //retorna lista vazia 
  }
  if(pivo == NULL){
    antigo = lista->head;
    lista->head = lista->head->next;

    if(lista->head==NULL){
      lista->tail = NULL; 
    }
  }else{
    if(pivo->next==NULL){
      return 2; //retorna fim da lista
    }
    antigo = pivo->next;
    pivo->next = pivo->next->next;

    if(pivo->next==NULL){
      lista->tail = pivo;
    }
  }
  free(antigo);
  lista->size--;
}

void imprimeLista(Lista *lista){
    Elemento *aux=(Elemento*) malloc (sizeof(Elemento));
    aux=lista->head;
    int i=0;
    for(i=0; i<lista->size; i++){
        printf("%i ",aux->dado);
        aux=aux->next;
    }
} 

