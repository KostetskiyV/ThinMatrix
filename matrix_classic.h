#ifndef MATRIX_CLASSIC_H__
#define MATRIX_CLASSIC_H__

#include <stdio.h>
#include <stddef.h>

struct mclassic_t
{
    int **nums;  // Массив элементов
    size_t n;  // Количество строк
    size_t m;  // Количество столбцов
};

int allocate_mclassic(struct mclassic_t *matrix);
void free_mclassic(struct mclassic_t *matrix);
size_t count_mclassic_mem(const struct mclassic_t *matrix);

int read_mclassic_default(FILE *f, struct mclassic_t *matrix);
int read_mclassic_coord(FILE *f, struct mclassic_t *matrix);

void print_mclassic_default(const struct mclassic_t *matrix);

int mclassic_addition(const struct mclassic_t *a, const struct mclassic_t *b, struct mclassic_t *c);

#endif
