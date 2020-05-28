#include <stdio.h>
#include <stdlib.h>

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

int main(){

Lista* lista_de_inteiros;
lista_de_inteiros = criaLista();

insereNaLista(lista_de_inteiros,NULL,1);
insereNaLista(lista_de_inteiros,lista_de_inteiros->tail,5);
insereNaLista(lista_de_inteiros,lista_de_inteiros->head,10);
escreveLista(lista_de_inteiros);

Elemento* pivo = buscaNaLista(lista_de_inteiros,10);
printf("Pivo: %i\n",pivo->dado);
insereNaLista(lista_de_inteiros,pivo,7);

escreveLista(lista_de_inteiros);

//printf("Tamanho da lista:%i\n",lista_de_inteiros->size);
//printf("Head:%i\n",lista_de_inteiros->head->dado);

int dado = removeDaLista(lista_de_inteiros,NULL);
//dado = removeDaLista(lista_de_inteiros,NULL);
//dado = removeDaLista(lista_de_inteiros,NULL);
//dado = removeDaLista(lista_de_inteiros,NULL);
printf("\nExcluido:%i\n", dado);
printf("Tamanho da Lista:%i", lista_de_inteiros->size);


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
