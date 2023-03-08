#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline") // Optimization flags
#pragma GCC option("arch=native", "tune=native", "no-zeroupper")           // Enable AVX
#pragma GCC target("avx")                                                  // Enable AVX
#pragma GCC target("avx2")                                                 // Enable AVX2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <immintrin.h>

#include <time.h>
#include <omp.h>

// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}

int isIdentity(int *, int);

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    int size = atoi(argv[1]);

    int *matrix;
    posix_memalign((void **)&matrix, 32, sizeof(int) * size * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    printf("Iniciando as operacoes...\n");

    int identity = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (identity)
            {
                *(matrix + i * size + j) = i == j ? 1 : 0;
            }
            else
            {
                *(matrix + i * size + j) = createRandom(10);
            }
        }
    }

    printf("%d: Resultado: %s", identity, isIdentity(matrix, size) == 1 ? "SIM" : "NAO");

    return 0;
}

int isIdentity(int *matrix, int size)
{
    int is_identity = 1;
    omp_set_num_threads(4);

    #pragma omp parallel for shared(is_identity)
    for (int i = 0; i < size; i++)
    {
        if (!is_identity)
        {
            continue;
        }

        for (int j = 0; j < size; j++)
        {
            int identity = (i == j) == *(matrix + i * size + j);
            is_identity &= identity;
        }
    }

    return is_identity;
}