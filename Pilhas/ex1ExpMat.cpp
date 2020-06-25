#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100


typedef struct sElemento {
    struct sElemento *next; 
    char dado;
} Elemento;

typedef struct sStack {
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Stack;

Stack* newStack();
Elemento* createElement(char);
void push(Stack* stack,char);
char pop(Stack* stack);
char stacktop(Stack* stack);
void imprimePilha(Stack* stack);
void isBalanced(char exp[]);

int main(){
   Stack* stack = newStack();
   char exp[TAM]= "(((A))))";
   printf("%s\n",exp);
   isBalanced(exp);
}

void imprimePilha(Stack* stack){
    Elemento *aux = stack->head;
    if (stack->size < 0){
        printf("A stack esta vazia!");
    }
    else{
        printf("Pilha: ");
        while (aux != NULL){
            printf("%c", aux->dado);
            aux = aux->next;
        }
        printf("\n");
    }
}


Stack* newStack(){
    Stack* stack;
    stack = (Stack*)malloc(sizeof(Stack));
    if(stack == NULL){
        printf("Memoria nao alocada1");
    }
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    return stack;
}


void isBalanced(char exp[]){
    Stack* stack; 
    int i;
    char aux;
    for(i=0;i < TAM;i++){
         if (exp[i] == '(' || exp[i] == '{' || exp[i] == '['){
            push(stack, exp[i]);
         }
         else{
             if(exp[i] == ')'){
                aux = stacktop(stack);
                if(aux == '('){
                    pop(stack);
                }
                else{
                    printf("Expressao invalida parenteses\n");
                }
             }
             else{
                 if(exp[i] == '}'){
                     aux = stacktop(stack);
                     if(aux == '{'){
                         pop(stack);
                     }
                     else{
                         printf("Expressao invalida chaves\n");
                     }
                 }
                 else{
                     if(exp[i] == ']'){
                         aux = stacktop(stack);
                         if(aux == '['){
                             pop(stack);
                         }
                         else{
                             printf("Expressao invalida colchetes\n");
                         }
                     }
                 }
             }
         }
    }
    if(stack->size == 0){
        printf("Expressao valida");
    } 
    else{
        printf("Expressao invalida");
    }
}


Elemento* createElement(char dado){
    Elemento* elemento;
    elemento = (Elemento*)malloc(sizeof(Elemento));
    if(elemento == NULL){
        printf("Memoria nao alocada2");
    }
    elemento->next = NULL;
    elemento->dado =dado;
    return elemento;
}

void push(Stack* stack,char dado){
    Elemento* novo = createElement(dado);
    novo->next = stack->head;
    stack->head = novo;
    stack->size++;
}

char pop(Stack* stack){
    Elemento* remove;
    remove = stack->head;
    char dado;
    if(stack->size == 0){
        printf("Fila esta vazia");
    }else{
        stack->head = remove->next;
        remove->next = NULL;
    }
    dado = remove->dado;
    free(remove);
    stack->size--;
	return dado;
}

char stacktop(Stack* stack){
    char top;
    if(stack->head != NULL){
        top = stack->head->dado;
    }
    return top;
}

