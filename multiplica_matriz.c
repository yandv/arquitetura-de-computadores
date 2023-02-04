#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <stdlib.h>

int createRandom(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int *multiply(int *first, int *second, int size)
{
    int *matrix = malloc(sizeof(int) * size * size);

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
    srand(time(NULL));
    int size;

    printf("Insira o tamanho da matriz\n::");
    scanf("%d", &size);

    printf("\nMatriz de tamanho %d\n", size);

    int *matrix = malloc(sizeof(int) * size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *((matrix + i * size) + j) = createRandom(0, 10);
        }
    }

    printf("Printando matrix: \n");

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", *((matrix + i * size) + j));
        }

        printf("\n");
    }

    printf("\nPrintando multiplicação: \n");

    int *result = multiply(matrix, matrix, size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", *((result + i * size) + j));
        }

        printf("\n");
    }

    return 0;
}
