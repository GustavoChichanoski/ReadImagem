#include "../include/matriz.h"

int   positionMatrizVector(int *size,int *pos);
int  *positionVectorMatriz(int position,int *size);
void  create_matriz(int height,int width,int *matrix);
void  printMatriz(int *matrix,int *size);

void testeMatriz()
{
    int *matA, *matB, *matC;
    int size_a[2] = {2,3};
    int size_b[2] = {3,2};
    int size_c[2] = {3,3};
    printf("Create Matriz\n");
    create_matriz(2,3,matA);
    create_matriz(3,2,matB);
    printf("Preencher matriz\n");
    matA[0] = 4; matA[1] = 1;
    matA[2] = 2; matA[3] = 1;
    matA[4] = 3; matA[5] = 1;
    matB[0] = 4; matB[1] = 2; matB[2] = 3;
    matB[3] = 1; matB[4] = 1; matB[5] = 1;
    printf("Multiplicar Matriz\n");
    multiplyMatriz(matA,matB,matC,size_a,size_b);
    printMatriz(matC,size_c);
}

void printMatriz(int *matrix,int *size)
{
    printf("Matriz:\n");
    for (int y = 0;y < size[1];y++)
    {
        printf("\t");
        for(int x = 0;x < size[0];x++)
        {
            printf("[%d][%d] : %d",y,x,matrix[y*size[0] + x]);
        }
    }
}

/*  Function to calculate position of matriz in vector
    inputs : int size[2] - [Height , Width]
             int pos[2]  - [Pos_y  , Pos_x]
    return : int position */
int positionMatrizVector(int *size,int *pos)
{
    return pos[1]*size[0] + pos[0];
}

/* Function  */
int *positionVectorMatriz(int position,int *size)
{
    size[1] = position / size[0];
    size[0] = position % size[0];
    return size;
}

void create_matriz(int height,int width,int *matrix)
{
    matrix = (int *) realloc (matrix,height*width*sizeof(int));
    if(matrix == NULL)
    {
        printf("Socorro o malloc retornou NULL\n");
        exit(EXIT_FAILURE);
    }
}

void multiplyMatriz(int *first,int *second,int *result,int *size_f,int *size_s)
{
    int x = 0, y = 0; // Position first matrix
    int i = 0, j = 0; // Position second matrix
    create_matriz(size_f[1],size_s[0],result);
    for (x = 0;x < size_f[1];x++)
    {
        for (y = 0;y < size_s[0];y++)
        {
            int soma = 0;
            for (i = 0;i < size_f[1];i++)
            {
                for (j = 0;j < size_s[0];j++)
                {
                    soma += first[y*size_f[0] + x] * second[i*size_s[0] + j];
                }
            }
            printf("[%d][%d] : %d",x,y,soma);
            result[x,y] = soma;
        }
    }
}