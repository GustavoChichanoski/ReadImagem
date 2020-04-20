#include "../include/operacaoMatriz.h"

void testeMatriz()
{
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
}

void printMatriz(Matriz mat)
{
    printf("Matriz: [%d][%d]\n",mat.row,mat.column);
    for (int position = 0;position < mat.row * mat.column;position++)
    {
        int x = position % mat.column;
        int y = position / mat.column;
        if(x == 0 && y != 0){printf("\n");}
        printf("  ");
        printf("[%d][%d] : [%d] ", y, x, position);
        printf("%d",mat.mat[position]);
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
    Matriz res;
    res = create_matriz(mat.column,mat.row);
    printf("res = [%d][%d]",res.row,res.column);
    for(int pos = 0;pos < res.row * res.column;pos++)
    {
        int row      = pos / res.column;
        int column   = pos % res.column;
        res.mat[pos] = mat.mat[column*mat.column + row];
    }
    return res;
}

Matriz multiplyMatriz(Matriz first,Matriz second)
{
    int row = 0, column = 0, i = 0, sum = 0;
    Matriz result;
    result = create_matriz(first.row,second.column);
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

Matriz create_matriz(int row,int column)
{
    Matriz matrix;
    matrix.column = column;
    matrix.row    = row;
    matrix.mat    = (int *) malloc(column * row * sizeof(int));
    if(matrix.mat == NULL)
    {
        printf("Socorro o malloc retornou NULL\n");
        exit(EXIT_FAILURE);
    }
    return matrix;
}

Matriz hadamart(Matriz erro,Matriz dS)
{
    if(erro.row == dS.row && erro.column == erro.column)
    {
        for (int pos = 0;pos < dS.column*dS.row;pos++)
        {
            erro.mat[pos] = erro.mat[pos] * dS.mat[pos];
        }
        return erro;
    } else {
        printf("Matrizes de dimensões distintas\nErro");
        printMatriz(erro);
        printf("Ds ");
        printMatriz(dS);
        exit(EXIT_FAILURE);
    }
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