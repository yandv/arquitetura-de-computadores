#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include <time.h>

// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}

int *multiply(int *first, int *second, int size)
{
    int *matrix = malloc(sizeof(int) * size * size);

    int test[5][5];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int result = 0;

            for (int k = 0; k < size; k++)
            {
                result += *((first + (i * size)) + k) * *((second + (k * size)) + j);
            }

            *((matrix + (i * size)) + j) = result;
        }
    }

    return matrix;
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

    int *matrix = malloc(sizeof(int) * size * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *((matrix + i * size) + j) = createRandom(10);
        }
    }

    multiply(matrix, matrix, size);
    return 0;
}
