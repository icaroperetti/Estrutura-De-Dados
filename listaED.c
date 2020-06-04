#include <stdio.h>
#include <stdlib.h>

/*
    Estrutura de Dados 1
    Lista Duplamente Encadeada
    ALuno: Ícaro Peretti
*/

typedef struct sElemento{
  struct sElemento *next;
  struct sElemento *prev;
  int *dado;
} Elemento;

typedef struct sLista{
  struct sElemento *head;
  struct sElemento *tail;
  int size;
} Lista;


Lista* criaLista(); 
Elemento* criaElemento(int); 
void insereNaLista(Lista*, Elemento*, int); 
int removeDaLista(Lista*, Elemento*); 
void escreveLista(Lista* lista); 
Elemento* buscaNaLista(Lista*, int dado); 
void destroiLista(Lista* lista);
Elemento* buscaNaListaTail(Lista* lista, int dado);

int main(){
  int removido;
  Elemento* pivo;
  Lista *lista1;
  lista1 = criaLista();
  if(lista1 == NULL){
    printf("Erro na criação da lista");
    return 0;
  }


  insereNaLista(lista1,NULL,5);
  insereNaLista(lista1,lista1->head,10);
  insereNaLista(lista1,lista1->head->next,15);
  insereNaLista(lista1,lista1->tail,20);

  pivo = buscaNaLista(lista1,20);
  printf("Busca head:\n Encontrado: %i\n",pivo->dado);

  pivo = buscaNaListaTail(lista1,15);
  printf("Busca tail:\n Encontrado: %i\n", pivo->dado);
  //insereNaLista(lista1,pivo,12);
  escreveLista(lista1);

  //removido = removeDaLista(lista1,lista1->tail);
  //printf("\nExcluido:%i\n", removido);
  
  destroiLista(lista1);
}

void destroiLista(Lista* lista){
  int dado;
  while(lista->size > 0){
    dado = removeDaLista(lista,lista->tail);
    printf("Dado excluido:%i - Size: %i\n",dado,lista->size);
  }
  free(lista);
}

Lista* criaLista(){
    Lista* lista = (Lista*) malloc (sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;

    return lista;
}


Elemento* criaElemento(int dado){
    Elemento* elemento;
    elemento = (Elemento*) malloc (sizeof(Elemento));

    elemento->next = NULL;
    elemento->dado = dado;

    return elemento;
}


void insereNaLista(Lista* lista, Elemento* pivo, int dado){
    Elemento* novo;
    novo = criaElemento(dado);
    if(novo == NULL){
      return -1;
    }

    novo->dado = dado;

    if((pivo == NULL)&&(lista->size > 0)){
        printf("O pivo deve ser NULL na insercao do primeiro elemento");
        exit(0);
    }

    if(lista->size == 0){
      lista->head = novo;
      lista->tail = novo;
    }
    else{
      novo->next = pivo->next;
      novo->prev = pivo;

      if(pivo->next == NULL){
        lista->tail = novo;
      }
      else{
        pivo->next->prev = novo;
      }
      pivo->next = novo;
    }
    lista->size++;
}

int removeDaLista(Lista* lista, Elemento* pivo){
    int dado;
   if((pivo != NULL) && (lista->size != 0)){
    if(pivo == lista->head){
      lista->head = pivo->next;
      if(lista->head == NULL){
        lista->tail = NULL;
      }else {
        pivo->next->prev = NULL;
      }
    }else {
      pivo->prev->next = pivo->next;
      if(pivo->next == NULL){
        lista->tail = pivo->prev;
      }else {
        pivo->next->prev = pivo->prev;
      }
    }
    dado = pivo->dado;
    free(pivo);
    lista->size--;
    return dado;
  }
}

void escreveLista(Lista* lista){
  Elemento* elemento;
  elemento = lista->head;
  printf("Lista completa:");
  while(elemento != NULL){
    printf("%i -> ",elemento->dado);
    elemento = elemento->next;
  }
  printf("NULL\n");
}

Elemento* buscaNaLista(Lista* lista, int dado){
  Elemento* elemento;
  elemento = lista->head;

  while(elemento != NULL){
    if(elemento->dado == dado){
      return elemento;
    }
    elemento = elemento->next;
  }
  printf("Elemento nao encontrado!");
  return NULL;
}

Elemento* buscaNaListaTail(Lista* lista, int dado){
   Elemento* elemento;
   elemento = lista->tail;

  while(elemento != NULL){
    if(elemento->dado == dado){
      return elemento;
    }
    elemento = elemento->prev;
  }
  printf("Elemento nao encontrado!");
  return NULL;
}
