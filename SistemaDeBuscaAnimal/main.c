#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _no {
    char texto[50];
    struct _no *sim;
    struct _no *nao;
};
typedef struct _no no;

no *criaNo(char texto[50], no *sim, no *nao){
    no *n = (no *)malloc(sizeof(no));
    if(n == NULL){
        printf("Memoria esgotada\n");
        exit(0);
    }
    strcpy(n->texto, texto);
    n->sim = sim;
    n->nao = nao;
    return n;
}

no *iniciaArvore(){
    no *salmao = criaNo("Salmao", NULL, NULL);
    no *gato = criaNo("Gato", NULL, NULL);

    no *ehUmPeixe = criaNo("Eh um peixe?", salmao, gato);

    return ehUmPeixe;
}

void procuraAnimal(no *arvore){
    char resposta;
    if(arvore->sim == NULL && arvore->nao==NULL){//Verifica se caiu em uma folha
        printf("Seu animal é um %s?", arvore->texto);
        scanf(" %c", &resposta);
        if(resposta == 'S'){//Se acerta o animal retorna o acerto
            printf("Então seu animal é um %s\n", arvore->texto);
        }else{//Se nao
            char texto[50];
            getchar();
            no *animalAntigo = criaNo(arvore->texto, NULL, NULL);//guarda o animal do no em um nova folha
            //Verifica qual animal era procurado
            printf("Nao achamos seu animal, qual era ele?\n");
            fgets(texto, sizeof(texto), stdin);
            texto[strcspn(texto, "\n")] = '\0';
            no *novoAnimal = criaNo(texto, NULL, NULL);//cria uma folha para o animal certo

            //Verifica qual pergunta leva a esse animal
            printf("Qual pergunta leva a esse animal?\n");
            fgets(texto, sizeof(texto), stdin);
            texto[strcspn(texto, "\n")] = '\0';

            strcpy(arvore->texto, texto);//coloco a pergunta que leva ao animal certo
            arvore->sim = novoAnimal;//aponta para o animal certo
            arvore->nao = animalAntigo;//aponta para o animal errado
        }
    }else{//Se nao é uma folha é um nó, logo é uma pergunta para decisao do animal
        printf("%s [S/N]", arvore->texto);
        scanf(" %c", &resposta);
        if(resposta == 'S')
            procuraAnimal(arvore->sim);
        else{
            procuraAnimal(arvore->nao);
        }
    }
}

void imprimePreOrdem(no *n){
    if(n !=NULL){
        printf("%s, ", n->texto);
        imprimePreOrdem(n->sim);
        imprimePreOrdem(n->nao);
    }
}

int main() {
    no *achaAnimal = iniciaArvore();
    char resposta;

    do{
        procuraAnimal(achaAnimal);

        printf("Deseja procurar um animal denovo?[S/N]");
        scanf(" %c", &resposta);
    }while(resposta!='N');

    printf("Arvore em pre-ordem\n");
    imprimePreOrdem(achaAnimal);
    return 0;
}
