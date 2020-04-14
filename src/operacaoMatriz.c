#include "../include/operacaoMatriz.h"

void testeMatriz()
{
    Matriz matA, matB, matC;
    matA.row = 2; matA.column = 3;
    matB.row = 3; matB.column = 2;
    matC.row = 3; matC.column = 3;
    printf("Create Matriz\n");
    matA = create_matriz(2,3);
    matB = create_matriz(3,2);
    matC = create_matriz(3,3);
    printf("Preencher matriz\n");
    matA.mat[0] = 2; matA.mat[1] = 1;
    matA.mat[2] = 2; matA.mat[3] = 1;
    matA.mat[4] = 2; matA.mat[5] = 1;
    matB = transposed(matA);
    printf("Multiplicar Matriz\n");
    printMatriz(matA);
    printMatriz(matB);
    matC = multiplyMatriz(matA, matB);
    printMatriz(matC);
    matC = hadamart(matC,matC);
    printMatriz(matC);
    matA = multConst(matC,2);
    printMatriz(matC);
}

void printMatriz(Matriz mat)
{
    printf("Matriz: [%d][%d]\n",mat.row,mat.column);
    for (int y = 0;y < mat.row;y++)
    {
        for(int x = 0; x < mat.column; x++)
        {
            printf("  ");
            printf("[%d][%d] : ", y, x);
            printf("%d",mat.mat[y*mat.column + x]);
        }
        printf("\n");
    }
    printf("\n");
}

/*  Function to calculate position of matriz in vector
    inputs : 
        int size[2] - [Height , Width]
        int pos[2]  - [Pos_y  , Pos_x]
    return : 
        int position */
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

Matriz somaMatrizes(Matriz a,Matriz b)
{
    for(int i = 0;i < a.row*a.column;i++)
    {
        a.mat[i] = a.mat[i] + b.mat[i];
    }
    return a;
}

Matriz transposed(Matriz mat)
{
    int row = 0, column = 0;
    Matriz result;
    result = create_matriz(mat.column,mat.row);
    for(row = 0;row < mat.row;row++)
    {
        for(column = 0;column < mat.column;column++)
        {
            mat.mat[column*mat.row + row] = mat.mat[row*mat.column + column];
        }
    }
    return mat;
}

Matriz multiplyMatriz(Matriz first,Matriz second)
{
    int row = 0, column = 0, i = 0, sum = 0;
    Matriz result;
    result = create_matriz(first.row,first.column);
    if(first.column != second.row)
    {
        printf("MatA com colunas diferentes de MatB");
        exit(EXIT_FAILURE);
    }
    for (row = 0; row < first.row; row++)
    {
        for (column = 0; column < second.column; column++)
        {
            int sum = 0;
            for (i = 0;i < first.column;i++)
            {   
                int f = first.mat[row * first.column + i];
                int s = second.mat[i * second.column + column];
                sum += f*s;
            }
            result.mat[row*second.column + column] = sum;
        }
    }
    printf("\n");
    return result;
}

Matriz create_matriz(int height,int width)
{
    Matriz matrix;
    matrix.column = width;
    matrix.row = height;
    matrix.mat = (int *) malloc(height*width*sizeof(int));
    if(matrix.mat == NULL)
    {
        printf("Socorro o malloc retornou NULL\n");
        exit(EXIT_FAILURE);
    }
    return matrix;
}

Matriz hadamart(Matriz erro,Matriz dS)
{
    for (int pos = 0;pos < dS.column*dS.row;pos++)
    {
        erro.mat[pos] = erro.mat[pos] * dS.mat[pos];
    }
    return erro;
}

Matriz multConst(Matriz mat,int constant)
{
    for(int pos = 0;pos < mat.column*mat.row;pos++)
    {
        mat.mat[pos] = mat.mat[pos]*constant;
    }
    return mat;
}

Matriz divConst(Matriz mat,int constant)
{
    for(int pos = 0;pos < mat.column*mat.row;pos++)
    {
        mat.mat[pos] = mat.mat[pos] / constant;
    }
    return mat;
}