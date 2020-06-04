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

int main(){
  int removido;
  Lista *lista1;
  lista1 = criaLista();


  insereNaLista(lista1,NULL,5);
  insereNaLista(lista1,lista1->head,15);
  insereNaLista(lista1,lista1->tail,10);
  insereNaLista(lista1,lista1->head->next,20);
  //Elemento* pivo = buscaNaLista(lista1,5);
  //insereNaLista(lista1,pivo,12);
  escreveLista(lista1);
  removido = removeDaLista(lista1,lista1->tail);
  printf("\nExcluido:%i\n", removido);
  escreveLista(lista1);

  
  
  destroiLista(lista1);

}

void destroiLista(Lista* lista){
  int dado;
  while(lista->size > 0){
    removeDaLista(lista,lista->head);
    removeDaLista(lista,lista->head->next);
    removeDaLista(lista,lista->tail);
  }
  printf("Size: %i\n",lista->size);
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

    novo->dado = dado;

    if((pivo== NULL)&&(lista->size > 0)){
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
    //Elemento* antigo;
 
   if((pivo != NULL) && (lista->size != 0)){
    if(pivo == lista->head){
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
  while(elemento != NULL){
    printf("%i -> ",elemento->dado);
    elemento = elemento->next;
  }
  printf("NULL\n");
}
/*
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
*/
