#include <stdlib.h>
#include "matrix_csr.h"
#include "error_codes.h"

int allocate_mcsr(struct mcsr_t *matrix)
{
    free_mcsr(matrix);

    matrix->an = malloc(matrix->nz * sizeof(int));
    if (!matrix->an)
        return ERR_MEM;

    matrix->ja = malloc(matrix->nz * sizeof(size_t));
    if (!matrix->ja)
    {
        free_mcsr(matrix);
        return ERR_MEM;
    }

    matrix->ia = malloc((matrix->n + 1) * sizeof(size_t));
    if (!matrix->ia)
    {
        free_mcsr(matrix);
        return ERR_MEM;
    }

    return OK;
}

void free_mcsr(struct mcsr_t *matrix)
{
    if (matrix->an)
    {
        free(matrix->an);
        matrix->an = NULL;
    }

    if (matrix->ja)
    {
        free(matrix->ja);
        matrix->ja = NULL;
    }

    if (matrix->ia)
    {
        free(matrix->ia);
        matrix->ia = NULL;
    }
}

size_t count_mcsr_mem(const struct mcsr_t *matrix)
{
    size_t mem = sizeof(*matrix);
    for (size_t i = 0; i < matrix->nz; i++)
        mem += sizeof(matrix->an[i]) + sizeof(matrix->ja[i]);
    for (size_t i = 0; i < matrix->n + 1; i++)
        mem += sizeof(matrix->ia[i]);
    return mem;
}

int read_mcsr_from_classic(struct mcsr_t *mcsr, const struct mclassic_t *mclassic)
{
    int rc = OK;
    free_mcsr(mcsr);
    mcsr->n = mclassic->n;
    mcsr->m = mclassic->m;
    mcsr->nz = 0;

    for (size_t i = 0; i < mclassic->n; i++)
    {
        for (size_t j = 0; j < mclassic->m; j++)
        {
            if (mclassic->nums[i][j] != 0)
                (mcsr->nz)++;
        }
    }

    rc = allocate_mcsr(mcsr);
    if (rc != OK)
        return rc;

    for (size_t i = 0, nz = 0; i < mclassic->n; i++)
    {
        mcsr->ia[i] = nz;
        for (size_t j = 0; j < mclassic->m; j++)
        {
            if (mclassic->nums[i][j] != 0)
            {
                mcsr->an[nz] = mclassic->nums[i][j];
                mcsr->ja[nz] = j;
                nz++;
            }
        }
    }
    mcsr->ia[mcsr->n] = mcsr->nz;
    return OK;
}

void print_mcsr_coord(const struct mcsr_t *matrix)
{
    printf("%lu %lu %lu\n", matrix->n, matrix->m, matrix->nz);
    for (size_t i = 1; i <= matrix->n; i++)
    {
        size_t start = matrix->ia[i-1], end = matrix->ia[i];
        for (size_t j = start; j < end; j++)
            printf("%lu %lu %d\n", i, matrix->ja[j] + 1, matrix->an[j]);
    }
}

void print_mcsr(const struct mcsr_t *matrix)
{
    printf("an |");
    for (size_t i = 0; i < matrix->nz; i++)
        printf(" %d", matrix->an[i]);

    printf("\nja |");
    for (size_t i = 0; i < matrix->nz; i++)
        printf(" %lu", matrix->ja[i]);

    printf("\nia |");
    for (size_t i = 0; i <= matrix->n; i++)
        printf(" %lu", matrix->ia[i]);
    printf("\n");
}

int mcsr_addition(const struct mcsr_t *a, const struct mcsr_t *b, struct mcsr_t *c)
{
    if (!a->an || !b->an)
        return ERR_MTR_UNINIT;
    if (a->n != b->n || a->m != b->m)
        return ERR_VARIABLES_RANGE;
    int rc = OK;

    c->n = a->n;
    c->m = a->m;
    c->nz = 0;
    for (size_t i = 1; i <= c->n; i++)
    {
        size_t cur_a = a->ia[i-1], cur_b = b->ia[i-1];
        size_t end_a = a->ia[i], end_b = b->ia[i];
        while (cur_a < end_a && cur_b < end_b)
        {
            size_t cur_aj = a->ja[cur_a], cur_bj = b->ja[cur_b];
            if (cur_aj <= cur_bj)
                cur_a++;
            if (cur_aj >= cur_bj)
                cur_b++;
            (c->nz)++;
        }
        (c->nz) += end_a - cur_a + end_b - cur_b;
    }

    rc = allocate_mcsr(c);
    if (rc != OK)
        return rc;

    c->ia[0] = 0;
    for (size_t i = 1, nz = 0; i <= c->n; i++)
    {
        size_t cur_a = a->ia[i-1], cur_b = b->ia[i-1];
        size_t end_a = a->ia[i], end_b = b->ia[i];

        while (cur_a < end_a && cur_b < end_b)
        {
            size_t cur_aj = a->ja[cur_a], cur_bj = b->ja[cur_b];
            if (cur_aj < cur_bj)
            {
                c->ja[nz] = cur_aj;
                c->an[nz] = a->an[cur_a++];
            }
            else if (cur_aj > cur_bj)
            {
                c->ja[nz] = cur_bj;
                c->an[nz] = b->an[cur_b++];
            }
            else
            {
                c->ja[nz] = cur_aj;
                c->an[nz] = a->an[cur_a++] + b->an[cur_b++];
            }
            nz++;
        }

        for (; cur_a < end_a; cur_a++, nz++)
        {
            c->ja[nz] = a->ja[cur_a];
            c->an[nz] = a->an[cur_a];
        }
        for (; cur_b < end_b; cur_b++, nz++)
        {
            c->ja[nz] = b->ja[cur_b];
            c->an[nz] = b->an[cur_b];
        }

        c->ia[i] = nz;
    }

    return OK;
}
