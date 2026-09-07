#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <stdbool.h>

//Struct que faz a estrutura de cada no do Deque
struct _noDeque {
    int valor;
    struct _noDeque* next;
    struct _noDeque* prev;
};
typedef struct _noDeque noDeque;

//Struct que faz a estrutura geral do Deque, que aponta pro inicio e pro fim do Deque
struct _Deque{
    noDeque* front;
    noDeque* rear;
};
typedef struct _Deque Deque;

//Funcao que cria o Deque no geral
Deque* criaDeque(){
    Deque* ret = malloc(sizeof(Deque));
    if(ret == NULL){ //If para verificar se a alocacao do deque nao de erro de memoria
        printf("Erro de alocacao de memoria para o deque");
        exit(0);
    }
    //Inicializa o Deque vazio
    ret->front = NULL;
    ret->rear = NULL;
    return ret;
}

//Funcao que destroi o Deque completamente
void destroiDeque(Deque* deq){
    if(deq != NULL){
        noDeque* curr = deq->front;
        while (curr != NULL){ //While para passar por todos os elementos do Deque e destrui-los individualmente
            noDeque* prox = curr->next;
            destroiNo(curr);
            curr=prox;
        }
        free(deq);
    }
}

//Funcao que verifica se o Deque esta vazio
bool isEmptyDeque(Deque* deq){
    return (deq == NULL);
}

//Funcao que imprime o Deque
void printDeque(Deque* deq){
    noDeque* curr = deq->front;
    printf("Iniciando a impressao do Deque:\n");
    while (curr != NULL){ //While para printar o elemento atual e passar para o proximo
        printf("%d,", curr->valor);
        curr = curr->next;
    }
    printf("\nFim do deque\n");
}

//Funcao que insere o nó no inicio do Deque
void insereFrenteDeque(Deque* deq, noDeque* no){
    if(deq->front == NULL){ //Verifica caso o Deque esteja vazio, caso sim inicia o Deque e adiciona o nó
        deq->rear = no;
    }else{ //Caso nao esteja vazio
        no->next = deq->front; //Aponta o nó recebido para o antigo incio do Deque
        deq->front->prev = no; //Aponta o antigo inicio do Deque para o nó recebido
        deq->front = no; //Atualiza o inicio do Deque para o nó recebido
    }
}

//Funcao que insere o nó no final do Deque
void insereFimDeque(Deque* deq, noDeque* no){
    if(deq->front == NULL){ //Verifica caso o Deque esteja vazio, caso sim inicia o Deque e adiciona o nó
        deq->front = no;
        deq->rear = no;
    }else{ //Caso nao esteja vazio
        no->prev = deq->rear; //Aponta o nó recebido para o antigo final do Deque
        deq->rear->next = no; //Aponta o antigo final do Deque para o nó recebido
        deq->rear = no; //Atualiza o final do Deque para o nó recebido
    }
}

//Funcao que remove o primeiro elemento do Deque
noDeque* removeFrenteDeque(Deque* deq){
    if (deq->front == NULL) //Se o Deque esta vazio, nao tem o que remover
        return NULL;

    noDeque* ret = deq->front; //cria um no para receber o primeiro elemento do Deque
    deq->front = deq->front->next; //aponta o inicio do Deque para o segundo elemento do Deque

    if (deq->front != NULL)
        deq->front->prev = NULL;//Se o Deque nao ficou vazio, entao remove o apontador para o elemento anterior do primeiro elemento do deque, pois ele nao tem elemento anterior
    else
        deq->rear = NULL; //Se ficou fazio, entao nao existe ultimo elemento tambem

    return ret;//Retorna o antigo inicio do Deque
}

//Funcao que remove o ultimo elemento do Deque
noDeque* removeFimDeque(Deque* deq){
    noDeque* ret = deq->rear; //Cria um no para receber o ultimo elemento do Deque
    deq->rear = deq->rear->prev; //Aponta o final do Deque para o penultimo elemento do Deque
    deq->rear->next = NULL; //Remove o apontador para o elemento posterior do ultimo elemento do deque, pois ele nao tem elemento posterior sendo o ultimo
    return ret;//Retorna o antigo final do Deque
}

//Funcao que retorna um nó para adicionar no Deque
noDeque* alocaNo(int valor){
    noDeque* novo = malloc(sizeof(noDeque));//Reserva a memoria para um nó
    novo->valor = valor;//Atribui valor ao nó
    novo->next = NULL;
    novo->prev = NULL;

    return novo;//Retorna o nó
}

//Funcao que destroi um nó
void destroiNo(noDeque* no){
    if (no != NULL) {
        free(no->valor);//Libera o valor do nó recebido
        free(no);//Libera o nó
    }
}

int main(){
    setlocale(LC_ALL, "");
    Deque* deque1 = criaDeque();//Cria um deque para manipular
    noDeque* no = NULL;//Cria uum nó para manipular os nós do Deque

    //CRIACAO DE UM DEQUE DE 3 ELEMENTOS
    no = alocaNo(10);
    insereFimDeque(deque1, no);
    no = alocaNo(20);
    insereFimDeque(deque1, no);
    no = alocaNo(5);
    insereFrenteDeque(deque1, no);

    //IMPRIME O DEQUE
    printDeque(deque1);

    //REMOVE O PRIMEIRO ELEMENTO DO DEQUE
    no = removeFrenteDeque(deque1);
    if(no){
        printf("Valor removido: %d\n", no->valor);
        free(no);
    }

    //IMPRIME O DEQUE POS REMOCAO
    printDeque(deque1);

    return 0;
}
