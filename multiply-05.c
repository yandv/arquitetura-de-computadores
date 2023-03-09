#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX
#pragma GCC target("avx2")  //Enable AVX2

#include <immintrin.h>
#include <avx2intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

// VECTOR

int createRandom(int upper)
{
    return rand() % upper;
}

int *transpose(int*, int);
int *multiply(int*, int*, int);

int threads = 1;

void farray_print(int *f, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ",f[i*n+j]);
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

    int size = atoi(argv[1]);

    char fileName[100] = "test/matrix-";
    strcat(fileName, argv[1]);
    strcat(fileName, ".txt");

    if (argc >= 3) {
        threads = atoi(argv[2]);
    }

    int *matrix;
    posix_memalign((void**)&matrix, 32, sizeof(int) * size * size);

    if (matrix == NULL)
    {
        printf("Erro ao alocar memoria");
        return 1;
    }

    printf("Iniciando as operacoes com %d...\n", threads);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *(matrix + i * size + j) = createRandom(10);
        }
    }

    multiply(matrix, matrix, size);
    return 0;
}

int* multiply(int* first, int* second, int size)
{
    int *result, i, j, k;
    posix_memalign((void**)&result, 32, sizeof(int) * size * size);

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j+=8)
        {
            __m256i sum = _mm256_setzero_si256();

            for (int k = 0; k < size; k++) {
                sum = _mm256_add_epi32(sum, _mm256_mullo_epi32(
                    _mm256_set1_epi32(*(first + i * size + k)),
                    _mm256_loadu_si256((__m256i*)(second + k * size + j))
                ));
            }

            _mm256_storeu_si256((__m256i*)((result + i * size) + j), sum);
        }
    }

    return result;
}

int* transpose(int* matrix, int size)
{
    int *transposed, i, j;
    posix_memalign((void**)&transposed, 32, sizeof(int) * size * size);

    for (i = 0; i < size; i+=8)
    {
        for (j = 0; j < size; j+=8)
        {
            _mm_prefetch(matrix + (j + 16 + 0) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 1) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 2) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 3) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 4) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 5) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 6) * size + i, _MM_HINT_T0);
            _mm_prefetch(matrix + (j + 16 + 7) * size + i, _MM_HINT_T0);

            __m256i I0 = _mm256_loadu_si256((__m256i*)(matrix + (j + 0) * size + i));
            __m256i I1 = _mm256_loadu_si256((__m256i*)(matrix + (j + 1) * size + i));
            __m256i I2 = _mm256_loadu_si256((__m256i*)(matrix + (j + 2) * size + i));
            __m256i I3 = _mm256_loadu_si256((__m256i*)(matrix + (j + 3) * size + i));
            __m256i I4 = _mm256_loadu_si256((__m256i*)(matrix + (j + 4) * size + i));
            __m256i I5 = _mm256_loadu_si256((__m256i*)(matrix + (j + 5) * size + i));
            __m256i I6 = _mm256_loadu_si256((__m256i*)(matrix + (j + 6) * size + i));
            __m256i I7 = _mm256_loadu_si256((__m256i*)(matrix + (j + 7) * size + i));

            __m256i T0 = _mm256_unpacklo_epi32(I0, I1);
            __m256i T1 = _mm256_unpackhi_epi32(I0, I1);
            __m256i T2 = _mm256_unpacklo_epi32(I2, I3);
            __m256i T3 = _mm256_unpackhi_epi32(I2, I3);
            __m256i T4 = _mm256_unpacklo_epi32(I4, I5);
            __m256i T5 = _mm256_unpackhi_epi32(I4, I5);
            __m256i T6 = _mm256_unpacklo_epi32(I6, I7);
            __m256i T7 = _mm256_unpackhi_epi32(I6, I7);

            I0 = _mm256_unpacklo_epi64(T0, T2);
            I1 = _mm256_unpackhi_epi64(T0, T2);
            I2 = _mm256_unpacklo_epi64(T1, T3);
            I3 = _mm256_unpackhi_epi64(T1, T3);
            I4 = _mm256_unpacklo_epi64(T4, T6);
            I5 = _mm256_unpackhi_epi64(T4, T6);
            I6 = _mm256_unpacklo_epi64(T5, T7);
            I7 = _mm256_unpackhi_epi64(T5, T7);

            T0 = _mm256_permute2x128_si256(I0, I4, 32);
            T1 = _mm256_permute2x128_si256(I1, I5, 32);
            T2 = _mm256_permute2x128_si256(I2, I6, 32);
            T3 = _mm256_permute2x128_si256(I3, I7, 32);
            T4 = _mm256_permute2x128_si256(I0, I4, 49);
            T5 = _mm256_permute2x128_si256(I1, I5, 49);
            T6 = _mm256_permute2x128_si256(I2, I6, 49);
            T7 = _mm256_permute2x128_si256(I3, I7, 49);

            _mm256_storeu_si256((__m256i*)(transposed + ((i + 0) * size) + j), T0);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 1) * size) + j), T1);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 2) * size) + j), T2);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 3) * size) + j), T3);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 4) * size) + j), T4);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 5) * size) + j), T5);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 6) * size) + j), T6);
            _mm256_storeu_si256((__m256i*)(transposed + ((i + 7) * size) + j), T7);
        }
    }

    return transposed;
}
