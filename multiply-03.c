#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <omp.h>

#include <time.h>

// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}

int **alloc(int , int);
int **multiply(int**, int**, int);

// MATRIX MULTIPLICATION WITH OPENMP

int threads = 1;

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

    srand(time(NULL));
    int size = atoi(argv[1]);
    int **matriz;
    matriz = alloc(size, size);

    if (argc >= 3) {
        threads = atoi(argv[2]);
    }

    omp_set_num_threads(threads);

    printf("Iniciando operações com %d threads...\n", threads);

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
    int core = 4, i, j, k;
    int **matrix = alloc(size, size);

    #pragma omp parallel for private(i,j,k) 
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
            matrix[i][j] = 0;

			for(k=0;k<size;k++)
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