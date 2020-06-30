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
void displayStack(Stack* stack);
void isBalanced(Stack*, char exp[]);
void destructStack(Stack* stack);
int main(){
   Stack* stack = newStack();
    //char exp[TAM]= "7+ {A} +- (B{CCCC}) {([M]T)U} ([{";
    //char exp[TAM]= "(A + B} )";
    char exp[TAM]= "{[A + B] - [(C - D)]";
    //char exp[TAM]= "(A + B)-{C + D}-[F+ G]";
    //char exp[TAM]= "((H) * {([J + K])})";
    //char EXP[TAM]= "(((A))))";
   printf("%s\n",exp);
   isBalanced(stack,exp);
   displayStack(stack);
   destructStack(stack);
}

void destructStack(Stack* stack){
    int i;
    printf("\nDestruindo!\n");
    while(stack->size != 0){
        pop(stack);
    }
    printf("Size:%i\n",stack->size);
    free(stack);
}

void displayStack(Stack* stack){
    Elemento *aux = stack->head;
    if (stack->size < 0){
        printf("A stack esta vazia!");
    }
    else{
        printf("Elementos na pilha: ");
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


void isBalanced(Stack* stack,char exp[]){
    int i;
    char aux;
    for( i=0; i< TAM ; i++){ 
        switch (exp[i]){
            //Se for abertura, adiciona na pilha
            case '(':
            push(stack,'(');
            break;

            case '[':
            push(stack,'[');
            break;

            case '{':
            push(stack,'{');
            break;

           //Se for fechamento remove da pilha
            case ')':
            aux= stacktop(stack);
            if(aux=='('){
                pop(stack);
            }else{
                printf("\nExpressao invalida parenteses,encerrando");
                exit(0);
            }
            break;

            case ']':
            aux= stacktop(stack);
            if(aux=='['){
                pop(stack);
            }else{
                printf("\nExpressao invalida colchetes,encerrando");
                exit(0);
            }
            break;

            case '}':
            aux= stacktop(stack);
            if(aux=='{'){
                pop(stack);
            } else{
                printf("\nExpressao invalida chaves,encerrando");
                exit(0);
            }
            break;
        }
    }
    if(stack->size == 0){
        printf("\nExpressao valida!\n");
    } else{
        printf("\nExpressao invalida!\n");
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
    printf("Inserido:%c\n",stack->head->dado);
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
    printf("Excluido:%c\n",dado);
	return dado;
}

char stacktop(Stack* stack){
    char top;
    if(stack->size != 0){
        top = stack->head->dado;
         return top;
    }else{
    	printf("A pilha esta vazia, erro de underflow");
    	exit(0); 
	}
}
