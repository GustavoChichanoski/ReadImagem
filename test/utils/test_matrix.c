#include "../include/utils/matriz.h"

void main(){
    Matriz matA, matB, matC;
    printf("Create Matriz\n");
    matA = create_matriz(3,2);
    printf("Preencher matriz [%d][%d]\n",matA.row,matA.column);
    for (int pos = 0;pos < 6;pos++)
    {matA.mat[pos] = pos;}
    matB = transposed(matA);
    printf("Multiplicar Matriz\nMatA ");
    printMatriz(matA);
    printf("MatB ");
    printMatriz(matB);
    matC = multiplyMatriz(matA, matB);
    printf("Multiplicacao ");
    printMatriz(matC);
    matC = hadamart(matC,matC);
    printf("Hadamart ");
    printMatriz(matC);
    matA = multConst(matC,2);
    printf("Multiplicacao constante ");
    printMatriz(matC);
    return 0;
}
