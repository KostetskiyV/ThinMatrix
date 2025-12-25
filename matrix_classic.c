#include <stdlib.h>
#include "matrix_classic.h"
#include "error_codes.h"

int allocate_mclassic(struct mclassic_t *matrix)
{
    free_mclassic(matrix);

    int *data = calloc(matrix->n * matrix->m, sizeof(int));
    if (!data)
        return ERR_MEM;

    matrix->nums = malloc(matrix->n * sizeof(int*));
    if (!matrix->nums)
    {
        free_mclassic(matrix);
        return ERR_MEM;
    }
    for (size_t i = 0; i < matrix->n; i++)
        matrix->nums[i] = &(data[i * matrix->m]);

    return OK;
}

void free_mclassic(struct mclassic_t *matrix)
{
    if (matrix->nums)
    {
        free(*(matrix->nums));
        free(matrix->nums);
    }
    matrix->nums = NULL;
}

size_t count_mclassic_mem(const struct mclassic_t *matrix)
{
    size_t mem = sizeof(*matrix);
    for (size_t i = 0; i < matrix->n; i++, mem += sizeof(matrix->nums[i]))
    {
        for (size_t j = 0; j < matrix->m; j++)
            mem += sizeof(matrix->nums[i][j]);
    }
    return mem;
}

int read_mclassic_default(FILE *f, struct mclassic_t *matrix)
{
    int rc = OK;
    if (f == stdin)
        printf("Введите размеры матрицы (n m):\n");
    if (fscanf(f, "%lu%lu", &(matrix->n), &(matrix->m)) != 2)
        return ERR_IO;
    if (matrix->n == 0 || matrix->m == 0)
        return ERR_RANGE;

    rc = allocate_mclassic(matrix);
    if (rc != OK)
        return rc;

    if (f == stdin)
        printf("Введите матрицу (%lu строк по %lu элементов):\n", matrix->n, matrix->m);
    for (size_t i = 0; i < matrix->n; i++)
    {
        for (size_t j = 0; j < matrix->m; j++)
        {
            if (fscanf(f, "%d", &(matrix->nums[i][j])) != 1)
                return ERR_IO;
        }
    }
    
    return OK;
}

int read_mclassic_coord(FILE *f, struct mclassic_t *matrix)
{
    int rc = OK;
    size_t k;
    if (f == stdin)
        printf("Введите размеры матрицы и количество ненулевых элементов (n m k):\n");
    if (fscanf(f, "%lu%lu%lu", &(matrix->n), &(matrix->m), &k) != 3)
        return ERR_IO;
    if (matrix->n == 0 || matrix->m == 0 || k > matrix->n * matrix->m)
        return ERR_RANGE;

    rc = allocate_mclassic(matrix);
    if (rc != OK)
        return rc;

    if (f == stdin)
        printf("Введите координаты и значения %lu ненулевых элементов:\n", k);
    for (size_t i = 0; i < k; i++)
    {
        size_t n, m;
        int val;
        if (fscanf(f, "%lu%lu%d", &n, &m, &val) != 3)
            return ERR_IO;
        if (n == 0 || m == 0 || n > matrix->n || m > matrix->m || matrix->nums[n-1][m-1] != 0 || val == 0)
            return ERR_RANGE;
        matrix->nums[n-1][m-1] = val;
    }
    
    return OK;
}

void print_mclassic_default(const struct mclassic_t *matrix)
{
    printf("%lu %lu\n", matrix->n, matrix->m);
    for (size_t i = 0; i < matrix->n; i++)
    {
        for (size_t j = 0; j < matrix->m; j++)
            printf("%d ", matrix->nums[i][j]);
        printf("\n");
    }
}

int mclassic_addition(const struct mclassic_t *a, const struct mclassic_t *b, struct mclassic_t *c)
{
    if (!a->nums || !b->nums)
        return ERR_MTR_UNINIT;
    if (a->n != b->n || a->m != b->m)
        return ERR_VARIABLES_RANGE;
    int rc = OK;

    c->n = a->n;
    c->m = a->m;
    rc = allocate_mclassic(c);
    if (rc != OK)
        return rc;

    for (size_t i = 0; i < c->n; i++)
    {
        for (size_t j = 0; j < c->m; j++)
            c->nums[i][j] = a->nums[i][j] + b->nums[i][j];
    }

    return OK;
}