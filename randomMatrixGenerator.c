#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int createRandom(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
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

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Erro ao passar argumentos");
        return 1;
    }

    int size = atoi(argv[1]);
    srand(time(NULL));

    FILE* file = fopen("matrix.txt", "w");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    printf("Matrix de tamanho %d criada com sucesso", size);

    int **matriz = alloc(size, size);

    if (matriz == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    fprintf(file, "%d\n", size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matriz[i][j] = i == j ? 1 : 0;
            fprintf(file, "%d ", matriz[i][j]);
        }
        fprintf(file, "\n");
    }


    return 0;
}