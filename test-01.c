#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX
#pragma GCC target("avx2")  //Enable AVX2

#include <immintrin.h>
#include <avx2intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void farray_print(float *f, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%f ",f[i*n+j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    int size = atoi(argv[1]);

    char fileName[100] = "test/matrix-";
    strcat(fileName, argv[1]);
    strcat(fileName, ".txt");

    FILE* file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    float *matrix = NULL;
    posix_memalign((void**)&matrix, 32, sizeof(float) * size * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(file, "%f", ((matrix + i * size) + j));
        }
    }

    printf("O arquivo %s foi encontrado e aberto, iniciando as operacoes...\n", fileName);

    float c = 3;
    __m256 C = _mm256_broadcast_ss(&c); // splat c across all SIMD lanes


    for (int i=0; i < size; i++) {
        //b[i]=a[i]*c;
        for (int j=0; j < size; j+=8) {
            __m256 A = _mm256_load_ps((matrix + i * size) + j);
            __m256 B = _mm256_mul_ps(A, C);
            _mm256_store_ps((matrix + i * size) + j, B);
        }
    }
	return 0;
}