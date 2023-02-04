#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <stdlib.h>

int createRandom(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int isIdentityMatrix(int *matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i == j && *((matrix + i * size) + j) != 1) || *((matrix + i * size) + j) == 1)
            {
                return 0;
            }
        }
    }
    return 1;
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
            printf("Digite matrix %d %d: ", i, j);
            scanf("%d", ((matrix + i * size) + j));
        }
        printf("\n");
    }

    printf("Matriz definida: \n");

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d, ", ((matrix + i * size) + j));
        }
        printf("\n");
    }

    printf("\nMatrix identity: %s", isIdentityMatrix(matrix, size));

    return 0;
}
