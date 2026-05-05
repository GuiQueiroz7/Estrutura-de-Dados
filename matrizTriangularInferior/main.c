#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define matrix_index(m, i, j) (i) < (j)? 0.0f: m[i][j]
#define set_matrix_index(m, i, j, v) (i) < (j)? 0.0f: (m[i][j] = v)

float** alocaMatrizTriangularInferior(int linhas){
    float **mat = (float **) malloc(sizeof(float*) * linhas);
    for (int i = 0; i < linhas; i++)
        mat[i] = (float *) malloc(sizeof(float) * (i+1));
    return mat;
}
void liberaMatriz(float **mat, int linhas){
    for (int i = 0; i < linhas; i++)
        free(mat[i]);
    free(mat);
}

float getElementoMI(float **mat, int i, int j){
    if (i < j)
        return 0.0f;
    else
        return mat[i][j];
}

void setElementoMI(float **mat, const int i, const int j, const float value){
    assert(i >= j);
    mat[i][j] = value;
}
void imprimeMatriz(float **mat, int linhas, float (*el)(float **, int, int)){
  int colunas = linhas;
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        float valor = el(mat, i, j);
        printf("%5.2f, ",valor);
    }
    printf("\n");
  }
}

int main(){
    float **matriz = alocaMatrizTriangularInferior(4);

    matriz[0][0] = 1;
    matriz[1][0] = 2; matriz[1][1] = 3;
    matriz[2][0] = 4; matriz[2][1] = 5; matriz[2][2] = 6;
    matriz[3][0] = 7; matriz[3][1] = 8; matriz[3][2] = 9; matriz[3][3] = 10;

    imprimeMatriz(matriz, 4, &getElementoMI);

    liberaMatriz(matriz, 4);
    return 0;
}
