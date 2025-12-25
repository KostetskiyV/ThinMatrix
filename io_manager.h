#ifndef IO_MANAGER_H__
#define IO_MANAGER_H__

#include <stdio.h>
#include "matrix_classic.h"
#include "matrix_csr.h"

typedef int (*read_mclassic)(FILE *f, struct mclassic_t *matrix);

read_mclassic choose_input();

int input_matrixes(FILE *f_in, struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr);

void print_matrixes(struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mclassic_t *c_mclassic, struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr,
    struct mcsr_t *c_mcsr);

#endif
