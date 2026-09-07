#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define matrix_index(m, i, j) (i) < (j)? 0.0f: m[i][j]
#define set_matrix_index(m, i, j, v) (i) < (j)? 0.0f: (m[i][j] = v)

float** alocaMatrizTriangularSuperior(int linhas){
    float **mat = (float **) malloc(sizeof(float*) * linhas);
    for (int i = 0; i < linhas; i++)
        mat[i] = (float *) malloc(sizeof(float) * (linhas-i));
    return mat;
}

void liberaMatriz(float **mat, int linhas){
    for (int i = 0; i < linhas; i++)
        free(mat[i]);
    free(mat);
}

float getElementoMS(float **mat, int i, int j){
    if (i > j)
        return 0.0f;
    else
        return mat[i][j-i];
}

void setElementoMS(float **mat, const int i, const int j, const float value){
    assert(i <= j);
    mat[i][j-i] = value;
}

void imprimeMatriz(float **mat, int linhas, float (*el)(float **, int, int))
{
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < linhas; j++) {
        float valor = el(mat, i, j);
        printf("%5.2f, ",valor);
    }
    printf("\n");
  }
}

int main(){
    float **matriz = alocaMatrizTriangularSuperior(4);

    setElementoMS(matriz, 0, 0, 1);  setElementoMS(matriz, 0, 1, 2);
    setElementoMS(matriz, 0, 2, 4);  setElementoMS(matriz, 0, 3, 7);
    setElementoMS(matriz, 1, 1, 3);  setElementoMS(matriz, 1, 2, 5);
    setElementoMS(matriz, 1, 3, 8);
    setElementoMS(matriz, 2, 2, 6);  setElementoMS(matriz, 2, 3, 9);
    setElementoMS(matriz, 3, 3, 10);

    imprimeMatriz(matriz, 4, &getElementoMS);

    printf("Muda o elemento do local [0][3], antes era: %5.2f\n", getElementoMS(matriz, 0, 3));
    setElementoMS(matriz, 0, 3, 5);
    printf("Apos a alteracao a matriz fica\n");
    imprimeMatriz(matriz, 4, &getElementoMS);
    printf("O elemento do local [0][3], agora e: %5.2f", getElementoMS(matriz, 0, 3));
    return 0;
}
