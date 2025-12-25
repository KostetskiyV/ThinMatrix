#ifndef MATRIX_MANAGER_H__
#define MATRIX_MANAGER_H__

#include "matrix_classic.h"
#include "matrix_csr.h"

void config(struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mclassic_t *c_mclassic, struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr,
    struct mcsr_t *c_mcsr);

void free_matrixes(struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mclassic_t *c_mclassic, struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr,
    struct mcsr_t *c_mcsr);

#endif
