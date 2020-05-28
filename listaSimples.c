#include <stdio.h>
#include <stdlib.h>

/*
    Estrutura de Dados 1
    Lista Simplesmente Encadeada
    ALuno: Ícaro Peretti
*/

typedef struct sElemento{
  struct sElemento *next;
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

int main(){
  int removido;
  Lista *lista1;
  lista1 = criaLista();


  insereNaLista(lista1,NULL,5);
  insereNaLista(lista1,lista1->tail,10);
  insereNaLista(lista1,lista1->head,15);
  Elemento* pivo = buscaNaLista(lista1,5);
  insereNaLista(lista1,pivo,12);
  escreveLista(lista1);


  //printf("Pivo: %i\n",pivo->dado);
  //insereNaLista(lista1,pivo,7);

  //escreveLista(lista1);

  //printf("Tamanho da lista:%i\n",lista1->size);
  //printf("Head:%i\n",lista1->head->dado);

  removido = removeDaLista(lista1,NULL);
  printf("\nExcluido:%i\n", removido);
  escreveLista(lista1);
  
 destroiLista(lista1);

  //printf("Tamanho da Lista:%i", lista1->size);
}

void destroiLista(Lista* lista){
  int dado;
  while(lista->size > 0){
    dado = removeDaLista(lista,NULL);
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

	if(pivo == NULL){
        if(lista->size == 0){
            lista->tail = novo;
        }
        novo->next = lista->head;
        lista->head = novo;
    }else{
        if(pivo->next == NULL){
            lista->tail = novo;
        }
        novo->next = pivo->next;
        pivo->next = novo;
    }
    lista->size++;
}

int removeDaLista(Lista* lista, Elemento* pivo){
    int dado;
    Elemento* antigo;

    if(lista->size == 0){
        return -1; 
    }
    if(pivo == NULL){
        antigo = lista->head;
        lista->head = lista->head->next;
    if(lista->head==NULL){
      lista->tail = NULL; 
    }
  }else{
    if(pivo->next==NULL){
      return -2; 
    }
    antigo = pivo->next;
    pivo->next = pivo->next->next;

    if(pivo->next==NULL){
      pivo = lista->tail;
    }
  }
  dado = antigo->dado;
  free(antigo);
  lista->size--;
  return dado;
}

void escreveLista(Lista* lista){
  Elemento* elemento;
  elemento = lista->head;

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
  return NULL;
}
