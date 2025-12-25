#include "matrix_manager.h"

void config(struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mclassic_t *c_mclassic, struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr,
    struct mcsr_t *c_mcsr)
{
    a_mclassic->n = 0;
    a_mclassic->m = 0;
    a_mclassic->nums = NULL;

    b_mclassic->n = 0;
    b_mclassic->m = 0;
    b_mclassic->nums = NULL;

    c_mclassic->n = 0;
    c_mclassic->m = 0;
    c_mclassic->nums = NULL;

    a_mcsr->n = 0;
    a_mcsr->m = 0;
    a_mcsr->nz = 0;
    a_mcsr->an = NULL;
    a_mcsr->ja = NULL;
    a_mcsr->ia = NULL;

    b_mcsr->n = 0;
    b_mcsr->m = 0;
    b_mcsr->nz = 0;
    b_mcsr->an = NULL;
    b_mcsr->ja = NULL;
    b_mcsr->ia = NULL;

    c_mcsr->n = 0;
    c_mcsr->m = 0;
    c_mcsr->nz = 0;
    c_mcsr->an = NULL;
    c_mcsr->ja = NULL;
    c_mcsr->ia = NULL;
}

void free_matrixes(struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mclassic_t *c_mclassic, struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr,
    struct mcsr_t *c_mcsr)
{
    free_mclassic(a_mclassic);
    free_mclassic(b_mclassic);
    free_mclassic(c_mclassic);

    free_mcsr(a_mcsr);
    free_mcsr(b_mcsr);
    free_mcsr(c_mcsr);
}
