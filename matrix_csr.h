#ifndef MATRIX_CSR_H__
#define MATRIX_CSR_H__

#include <stddef.h>
#include "matrix_classic.h"

struct mcsr_t
{
    size_t n;  // Количество строк
    size_t m;  // Количество столбцов
    size_t nz;  // Количество ненулевых элементов
    int *an;  // Массив ненулевых элементов
    size_t *ja;  // Горизонтальные индексы ненулевых элементов
    size_t *ia;  // Индекс начала каждой из строк
};

int allocate_mcsr(struct mcsr_t *matrix);
void free_mcsr(struct mcsr_t *matrix);
size_t count_mcsr_mem(const struct mcsr_t *matrix);

int read_mcsr_from_classic(struct mcsr_t *mcsr, const struct mclassic_t *mclassic);

void print_mcsr_coord(const struct mcsr_t *matrix);
void print_mcsr(const struct mcsr_t *matrix);

int mcsr_addition(const struct mcsr_t *a, const struct mcsr_t *b, struct mcsr_t *c);

#endif