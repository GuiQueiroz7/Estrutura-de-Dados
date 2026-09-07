#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _idNode {
    char* id;
    float value;
    struct _idNode* next;
};

typedef struct _idNode idNode;

idNode *tabelaSimbolos = NULL;//A lista é global para conseguir ser acessada por todas as funcoes

idNode* alocaNo(char *id, float value){
    idNode *no = malloc(sizeof(idNode));
    if (no == NULL) {   //Falhou alocação de elemento
        printf("Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }
    no->id = strdup(id);
    no->value = value;
    no->next = NULL;
    return no;
}

void liberaNo(idNode *no){
    free(no->id);
    free(no);
}

void insereNo(idNode* no){ //Essa funcao adiciona o no no final da lista sem verificar nada
    no->next = tabelaSimbolos;
    tabelaSimbolos = no;
}

void insereNoSemRepeticao(idNode* no){ //Essa funcao faz uma verificacao para nao inserir valores com o mesmo nome e quando acha iguais,, substiui o antigo pelo atual
    if (tabelaSimbolos == NULL) //Caso a Lista esteja vazia
        tabelaSimbolos = no;
    else {
        idNode* aux  = tabelaSimbolos->next;
        idNode* prev = tabelaSimbolos;
        if (strcmp(no->id, tabelaSimbolos->id) == 0) { //Caso o elemento a ser substituido seja o primeiro da lista
            no->next = aux;
            liberaNo(tabelaSimbolos);
            tabelaSimbolos = no;
        }
        else {
            while (aux != NULL ) { //Caso o elemento a ser trocado esteja no meio da lista ele realiza a substituicao e libera o elemento
                if (strcmp(no->id, aux->id) == 0) {
                    prev->next = no;
                    no->next = aux->next;
                    liberaNo(aux);
                    return;
                }
                prev = prev->next;
                aux  = aux->next;
            }
            //Se não encontra na lista, insere no final
            prev->next = no;
            no->next = NULL;
        }
    }
}

void insereNoOrdenado(idNode* no){ //Essa funcao faz uma verificacao para inserir os valores em ordem alfabetica
    if (tabelaSimbolos == NULL) //Trata caso a Lista esteja vazia
        tabelaSimbolos = no;
    else {
        idNode* aux  = tabelaSimbolos->next;
        idNode* prev = tabelaSimbolos;
        if (strcmp(no->id, tabelaSimbolos->id) < 0){//Trata caso o item a inserir tenha q ir antes do primeiro
            no->next = prev;
            tabelaSimbolos = no;
        }
        else {
            while (aux != NULL ){
                if (strcmp(no->id, aux->id) == 0) {//Trata caso o item a inserir seja igual algum outro
                    insereNoSemRepeticao(no);
                    return;
                }else if (strcmp(no->id, aux->id) < 0){//Trata caso o item a  inserir seja antes de algum item no meio da Lista
                    prev->next = no;
                    no->next = aux;
                    return;
                }
                prev = prev->next;
                aux  = aux->next;
            }
            prev->next = no;//Aloca o no final da lista caso ele seja de fato o ultimo em ordem alfabetica
            no->next = NULL;
        }
    }
}

int removeElemento(char* id){ //Funcao que remove algum elemento da lista
    idNode *aux = tabelaSimbolos;
    idNode *prev = NULL;

    //Primeiro trata caso o primeiro elemento seja o elemento a ser removido
    if (strcmp(tabelaSimbolos->id, id) == 0){
        tabelaSimbolos = tabelaSimbolos->next;
        liberaNo(aux);
        return 1;
    }

    prev = tabelaSimbolos;
    aux = tabelaSimbolos->next;

    //Loop que trata caso o elemento a ser removido seja qualquer outra posicao da lista
    while (aux != NULL) {
        if (strcmp(aux->id, id) == 0){
            prev->next = aux->next;
            liberaNo(aux);
            return 1;
        }
        prev = aux;
        aux = aux->next;
    }
    return 0;
}

void liberaTabela(){ //Funcao que apaga a Lista Inteira
    idNode *aux = tabelaSimbolos;
    idNode *prox = NULL;
    while (aux != NULL){
        prox = aux->next;
        liberaNo(aux);
        aux = prox;
    }
    tabelaSimbolos = NULL;
}

void imprimeTabelaSimbolos(){ //Funcao que imprime a lista toda
    idNode *aux = tabelaSimbolos;
    printf("-------------------- STATUS --------------------\n");
    while (aux != NULL){
       printf("ID = %25s value = %10.2f\n", aux->id, aux->value);
       aux = aux->next;
    }
    printf("------------------------------------------------\n");
}

int main(){
    //Realizando testes de criacao e manipulacao da lista

    idNode *temp = alocaNo("x", 640.0f);
    insereNoSemRepeticao(temp);
    temp = alocaNo("y", 480.0f);
    insereNoSemRepeticao(temp);
    temp = alocaNo("speed", 8.0f);
    insereNoSemRepeticao(temp);
    printf("Tabela inicial\n");
    imprimeTabelaSimbolos();

    temp = alocaNo("y", 360.0f);
    insereNoSemRepeticao(temp);
    printf("Tabela apos inserir sem repetir o valor de um novo 'y' na Lista\n");
    imprimeTabelaSimbolos();

    removeElemento("x");
    printf("Tabela apos remover 'x' da Lista\n");
    imprimeTabelaSimbolos();

    temp = alocaNo("bcc", 15.0f);
    insereNoOrdenado(temp);
    printf("Tabela apos adicionar alfabeticamente 'bcc' na Lista\n");
    imprimeTabelaSimbolos();

    return 0;
}
