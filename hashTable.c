
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define M 13

typedef struct sElemento{
	struct sElemento *next;
	struct sElemento *prev;
	char nome[MAX];
}Elemento;

typedef struct sBucket{
  struct sElemento *head;
  struct sElemento *tail;
  struct sBucket *next;
  struct sBucket *prev;
  int key;
  int size;
} Bucket;

typedef struct sHash{
	struct sBucket *head;
	struct sBucket *tail;
	int size;
}Hash;

Elemento* criaElemento(char *nome){
	int i, size=0;
	
	
	Elemento* elemento = (Elemento*)malloc(sizeof(Elemento));
	elemento->next = NULL;
  	elemento->prev = NULL;
	
	for(i=0;i<strlen(nome);i++){
		if(nome[i]!=10){
			size++;	
		}
	}
	
	
	for(i=0;i<size;i++){
		elemento->nome[i]=nome[i];
	}
	
	return elemento;
}

Hash* criaHash(){
  Hash* hash = (Hash*)malloc(sizeof(Hash));
  hash->head = NULL;
  hash->tail = NULL;
  hash->size = 0;
  return hash;
}

Bucket* criaBucket(int chave){
    Bucket* bucket = (Bucket*)malloc(sizeof(Bucket));
    bucket->head = NULL;
    bucket->tail = NULL;
    bucket->next = NULL;
    bucket->prev = NULL;
    bucket->key = chave;
    bucket->size = 0;
    return bucket;
}

int gerarChave(char* nome){
  int chave = (int) nome[0];
  return chave % M;
}

Bucket* inserirHash(Hash* hash,int chave){
  Bucket* pivo = hash->tail;
  Bucket* novaLista = criaBucket(chave);

  if(pivo == NULL && hash->size != 0){
		printf("Nao e possivel inserir um valor na posicao NULL quando a lista nao esta vazia.");
		return 0;
	}
	
	if(hash->size == 0){
		hash->head = novaLista;
		hash->tail = novaLista;
	}else{
		novaLista->next = pivo->next;
		novaLista->prev = pivo;
		if(pivo->next == NULL){
			hash->tail = novaLista;
		}else{
			pivo->next->prev = novaLista;
		}
		pivo->next = novaLista;
	}
	hash->size++;
}

void atribuirHash(){
  Bucket* novaLista;
  int i;
  for(i=0;i < M;i++){
      novaLista = inserirHash(novaLista,i);
  }
}

void inserirElemento(Bucket* bucket,char* nome){
  Elemento* novoNome = criaElemento(nome);
  if((bucket->head == NULL) && (bucket->tail == NULL)){
    bucket->head = novoNome;
    bucket->tail = novoNome;
  }else{
   novoNome->prev = bucket->tail;
   bucket->tail->next = novoNome;
   bucket->tail = novoNome;
  } 
  bucket->size++;
}

void inserirNome(Hash* hash,char* dado){
   Bucket* aux;
   aux = hash->head;
   int chave = gerarChave(dado);
   while (aux != NULL){
    if(chave == aux->key){
      inserirElemento(aux,dado);
    }
    aux = aux->next;
   }
}

void imprimirTabela(Hash* hash){
	Bucket *aux = hash->head;
	Elemento *auxNomes;
	int totalNomes=0;

  while (aux != NULL){
    printf("--------------------------------------------------------------\n");
	printf("Chave: %i  Qnt de nomes: %i\n", aux->key, aux->size);
    auxNomes = aux->head;
    
	while (auxNomes != NULL){
      printf("%s\n",auxNomes->nome);
      auxNomes = auxNomes->next;
    }
    totalNomes += aux->size;
    aux = aux->next;
  }
  printf("Total de nomes: %i \n\n", totalNomes);
}

void autoInsercao(Hash *hash){
	char nome[MAX];
  FILE *file;
  file = fopen("nomes.txt", "r");
  if (file == NULL){
    printf("Arquivo nao encontrado.\n");
  }
  else{
    printf("Inserindo arquivo...\n");
    while(!feof(file)){
	    
		fgets(nome, MAX, file);
		
		inserirNome(hash, nome);
  	}
	printf("Insercao feita com sucesso!\n");
	}
  fclose(file);
}

Elemento* buscarNome(Hash* hash,char* nome){
  	int encontrou_nome=0;
	Bucket* aux;
	aux = hash->head;
	Elemento* elemento;
	int comparaChave;
	comparaChave = gerarChave(nome);
	while(aux != NULL){
		if(aux->key == comparaChave){
			elemento = aux->head;
			while(elemento != NULL){
				if(strcmp(elemento->nome, nome) == 0){
					printf("%s encontrado na chave %i\n", elemento->nome,aux->key);
          			encontrou_nome=1;
					return elemento;
				}
				elemento = elemento->next;
			}
			break;
		}
		aux = aux->next;
	}
}

Elemento* removerElemento(Bucket* bucket,Elemento* elemento){
  if((elemento != NULL) && (bucket->size != 0)){
		if(elemento == bucket->head) {
			bucket->head = elemento->next;
			if(bucket->head == NULL){
				bucket->tail = NULL;
			}else {
				bucket->next->prev = NULL;
			}
		}else{
			elemento->prev->next = elemento->next;
			if(elemento->next == NULL){
				bucket->tail = elemento->prev;
			}else {
				elemento->next->prev = elemento->prev;
			} 
		}
		free(elemento);
		bucket->size--;
  }
}

void removerNome(Hash* hash,char* nome){
  	Bucket* aux;
	aux = hash->head;
	int comparaChave = gerarChave(nome);
	Elemento* remover;
	
	while(aux != NULL){
		if(comparaChave == aux->key){
		 remover = buscarNome(hash, nome);
      	removerElemento(aux,remover);
      	printf("%s removido\n",remover->nome);
		}
		aux = aux->next;
	}
}



int main(){
	
  char nome[MAX];
  Hash* hash = criaHash();
  atribuirHash(hash);
  int op;
  

  for(;;){
  	printf("--------------------------------------\n");
    printf("0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Inserir arquivo\n4 - Remover\n5 - Buscar\n");
    printf("--------------------------------------\n");
		scanf("%i",&op);

    if(op == 0 || op < 0){
      printf("Programa finalizado");
      exit(0);
    }
    if(op == 1){
      printf("Insira o nome:");
	  scanf(" %[^\n]", &nome);
      inserirNome(hash,nome);
      
      system("cls");
      printf("Nome inserido com sucesso\n");
    }
    if(op == 2){
      system("cls");
      imprimirTabela(hash);
    }
    if(op == 3){
    	system("cls");
      autoInsercao(hash);
    }
    if(op == 4){
      printf("Insira o nome a ser removido:");
	    scanf(" %[^\n]", &nome);
	    system("cls");
      removerNome(hash,nome);
    }
    if(op == 5){
      printf("Insira o nome a ser buscado:");
	    scanf(" %[^\n]", &nome);
	    system("cls");
      	buscarNome(hash,nome);
			  
		
    }
  }
}

