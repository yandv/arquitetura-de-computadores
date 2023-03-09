#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <omp.h>

#include <time.h>

// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}

int *transpose(int*, int);
int *multiply(int*, int*, int);


// VECTOR SIZE X SIZE MULTIPLICATION MATRIX X TRANSPOSE WITH OPENMP

int threads = 1;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    srand(time(NULL));
    int size = atoi(argv[1]);

    if (argc >= 3) {
        threads = atoi(argv[2]);
    }

    int *matrix = malloc(sizeof(int) * size * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    printf("Iniciando as operacoes usando %d threads...\n", threads);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *((matrix + i * size) + j) = createRandom(100);
        }
    }

    multiply(matrix, transpose(matrix, size), size);

    return 0;
}

int* multiply(int* first, int* second, int size)
{
    int *result = malloc(sizeof(int) * size * size), i, j, k;

    #pragma omp parallel for private(i,j,k) 
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            int sum = 0;

            for (k = 0; k < size; k++)
            {
                sum += *(first + i * size + k) * *(second + j * size + k);
            }

            *((result + (i * size)) + j) = sum;
        }
    }

    return result;
}

int* transpose(int* matrix, int size)
{
    int *transposed = malloc(sizeof(int) * size * size), i, j;

    #pragma omp parallel for private(i,j) 
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            *((transposed + (j * size)) + i) = *((matrix + (i * size)) + j);
        }
    }

    return transposed;
}
