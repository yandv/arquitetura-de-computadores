#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>
// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}


int isIdentity(int**, int);

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    int size = atoi(argv[1]);

    int **matrix = (int**)malloc(sizeof(int*) * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    printf("Iniciando as operacoes...\n");

    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int*)malloc(sizeof(int) * size);

        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = i == j ? 1 : 0;
        }
    }

    printf("Resultado: %s", isIdentity(matrix, size) == 1 ? "SIM" : "NAO");

    return 0;
}

int isIdentity(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {

                if (matrix[i][j] != 1)
                {
                    return 0;
                }
            }
            else
            {
                if (matrix[i][j] != 0)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}