#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int *transpose(int*, int);
int *multiply(int*, int*, int);

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    int size = atoi(argv[1]);

    char fileName[100] = "test/matrix-";
    strcat(fileName, argv[1]);
    strcat(fileName, ".txt");

    int *matrix = malloc(sizeof(int) * size * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    FILE* file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("O arquivo %s nao existe.", fileName);
        return 1;
    }

    printf("O arquivo %s foi encontrado e aberto, iniciando as operacoes...\n", fileName);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(file, "%d", ((matrix + i * size) + j));
        }
    }

    multiply(matrix, transpose(matrix, size), size);

    return 0;
}

int* multiply(int* first, int* second, int size)
{
    int *result = malloc(sizeof(int) * size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int sum = 0;

            for (int k = 0; k < size; k++)
            {
                sum += *((first + (i * size)) + k) * *((second + (j * size)) + k);
            }

            *((result + (i * size)) + j) = sum;
        }
    }

    return result;
}

int* transpose(int* matrix, int size)
{
    int *transposed = malloc(sizeof(int) * size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *((transposed + (j * size)) + i) = *((matrix + (i * size)) + j);
        }
    }

    return transposed;
}
