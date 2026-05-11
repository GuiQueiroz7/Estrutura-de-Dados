#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <stdbool.h>

//Struct que estrutura cada no da Fila
struct _noFila {
    int valor;
    struct _noFila* next;
};
typedef struct _noFila noFila;

//Funcao que insere um nó na Fila
void insereFila(noFila** filapp, int v){
    noFila* novo = malloc(sizeof(noFila));//Aloca o espaco para o nó
    novo->valor = v;//Atribui valor ao nó
    novo->next = NULL;

    if (*filapp == NULL)//Se a fila esta vazia, o no é adicionado direto
        *filapp = novo;
    else {//Se a fila nao esta vazia
        noFila* curr = *filapp;//cria um apontador para a fila
        while (curr->next != NULL)
            curr = curr->next;//Encontro o ultimo elemento da fila
        curr->next = novo;//Adiciono o nó depois do ultimo elemento
    }
}

//Funcao que verifica se a Fila está vazia
bool isEmptyFila(noFila* fila){
    return (fila == NULL);
}

//Funcao que retorna o primeiro da Fila
noFila* removePrimeiroElemento(noFila** filapp){
    assert(*filapp != NULL);
    noFila* ret = *filapp;
    *filapp = (*filapp)->next;
    return ret;
}

//Funcao que imprime a Fila
void imprimeFila(noFila* fila){
    noFila* aux = fila;
    while(aux != NULL){//Enquanto o no aux eh diferente de NULO entao imprime o valor de aux
        printf("%d, ", aux->valor);
        aux = aux->next;
    }
    printf("\n");
}

//Testa todas as funcoes de implementacao da Fila
void testaFila(noFila** filapp){
    insereFila(filapp, 1);
    imprimeFila(*filapp);
    insereFila(filapp, 2);
    imprimeFila(*filapp);
    insereFila(filapp, 3);
    imprimeFila(*filapp);

    while (!isEmptyFila(*filapp)){//Apaga toda a fila
        noFila* aux = removePrimeiroElemento(filapp);
        printf("No removido --> %d\n", aux->valor);
        free(aux);
    }
}

int main(){
    setlocale(LC_ALL, "");

    noFila* fila1 = NULL;
    noFila* fila2 = NULL;
    testaFila(&fila1);
    testaFila(&fila2);

    return 0;
}
