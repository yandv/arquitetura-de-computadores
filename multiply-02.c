#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}

// MATRIX

int **alloc(int , int);
int **multiply(int**, int**, int);

void print(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    int size = atoi(argv[1]);
    int **matriz;
    matriz = alloc(size, size);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            matriz[i][j] = createRandom(10);
        }
    }

    multiply(matriz, matriz, size);
    return 0;
}

int **multiply(int **first, int **second, int size)
{
    int **matrix = alloc(size, size);

	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
            matrix[i][j] = 0;

			for(int k=0;k<size;k++)
			{
                matrix[i][j] += first[i][k] * second[k][j];
			}
		}
	}

    return matrix;
}

int **alloc(int linha, int coluna)
{
    int **matriz = malloc(linha * sizeof(int*));

    if(matriz == NULL)
    {
        printf("Não foi possível alocar matriz");
        return 0;
    }

    for(int i = 0; i < linha; i++)
    {
        matriz[i] = malloc(coluna * sizeof(int*)); 
    }

    return matriz;
}