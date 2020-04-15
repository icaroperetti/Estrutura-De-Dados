#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*
    Estrutura de Dados
    Lista Simplesmente Encadeada
    ALuno: Ícaro Peretti
*/

typedef struct sPessoa{
    int idade;
    //char nome[50];
}Pessoa;

typedef struct sElemento {
    struct sElemento *next;
    Pessoa *pessoa;
} Elemento;

typedef struct sLista {
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Lista;

Lista* criaLista();
Pessoa* criaPessoa();
Elemento* criaElemento(Pessoa*);
void insereDados(Pessoa*);
void insereLista(Lista*,Elemento*,Elemento*);
void imprimeLista(Lista*);
int remove(Lista*,Elemento*);


int main(){
    Lista *lista = criaLista();
    if(lista == NULL){
        printf("Memoria nao alocada");
    }
    Pessoa *novaPessoa;
    Elemento *novoElemento;
    Elemento *pivo = (Elemento*) malloc (sizeof(Elemento));
    pivo = NULL;

    int op = 0;

    while(op != 6){
        printf("Selecione uma opcao:\n");
        printf("1 - Inserir\n");
        printf("2 - Imprimir lista completa\n");
        printf("3 - Remover elemento\n");
        printf("6 - Finalizar\n");
        scanf("%i", &op);
        if(op == isalpha(op)){
            printf("Por favor digite um numero!");
            break;
        }
        if(op  == 6){
            printf("Programa Finalizado!");
            break;
        }
        else if(op == 1){
            novaPessoa = criaPessoa();
            novoElemento = criaElemento(novaPessoa);
            insereLista(lista,pivo,novoElemento);
        }
        else if(op == 2 ){
            imprimeLista(lista);
        } 
        else if(op == 3){
           Elemento* elemento;
           elemento = remove(lista,pivo);
           imprimeLista(lista);
        }
    }
    
    free(novoElemento);
    free(novaPessoa);
    free(lista);
    novaPessoa = NULL;
    novoElemento = NULL;
    pivo = NULL;
    lista = NULL;
    return 0;
}

Lista* criaLista(){
  Lista *lista = (Lista*) malloc (sizeof(Lista));
  lista->head=NULL;
  lista->tail=NULL;
  lista->size=0;
  return lista;
}

Pessoa* criaPessoa(){
    Pessoa* pessoa = NULL;

    pessoa = (Pessoa*) malloc (sizeof(Pessoa));
    insereDados(pessoa);
    return pessoa;
}

void insereDados(Pessoa* pessoa){
    int cont = 0;
    printf("Digite a idade:");
    scanf("%i",&pessoa->idade);
}

Elemento* criaElemento(Pessoa* pessoa){
    Elemento *elemento = NULL;

    elemento = (Elemento*) malloc (sizeof(Elemento));
    elemento->pessoa = pessoa;
    elemento->next = NULL;

    return elemento;
}

void insereLista(Lista* lista, Elemento* pivo, Elemento* novo) {
    if(pivo == NULL) {
        if(lista->size == 0) {
            lista->tail = novo;
            lista->head = novo;
        } else {
            novo->next = lista->head;
            lista->head = novo;
        }
    } else {
        if(pivo->next == NULL) {
            lista->tail = novo;
        } else {      
            novo->next = pivo->next;
            pivo->next = novo;
        }
    }
    lista->size++;
}

void imprimeLista(Lista *lista) {
    Elemento *pivo;
    if(lista->size != 0){
        pivo = lista->head;
        printf("\nIdades na lista:\n");
        while( pivo != NULL){
        printf("%i\n", pivo->pessoa->idade);
        pivo = pivo->next;
        }
    }else{
        printf("Lista Vazia!\n");
    }  
}

int remove(Lista* lista,Elemento* pivo){
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

