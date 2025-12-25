#include "io_manager.h"
#include "print_menu.h"
#include "error_codes.h"

#define INPUT_DEFAUL_MODE 1
#define INPUT_COORD_MODE 2

#define OUTPUT_DEFAULT_MODE 1
#define OUTPUT_COORD_MODE 2
#define OUTPUT_CSR_MODE 3

#define CANCEL_MODE 0

#define OUTPUT_DEFAULT_MAX_SIZE 30

read_mclassic choose_input()
{
    int mode;
    if (scanf("%d", &mode) != 1)
        return NULL;
    if (mode == INPUT_DEFAUL_MODE)
        return read_mclassic_default;
    else if (mode == INPUT_COORD_MODE)
        return read_mclassic_coord;
    return NULL;
}

int input_matrixes(FILE *f_in, struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr)
{
    int rc = OK;
    print_input_submenu();
    read_mclassic read_type = choose_input();
    if (read_type)
    {
        rc = read_type(f_in, a_mclassic);
        if (rc != OK)
            return rc;

        rc = read_type(f_in, b_mclassic);
        if (rc != OK)
            return rc;

        read_mcsr_from_classic(a_mcsr, a_mclassic);
        read_mcsr_from_classic(b_mcsr, b_mclassic);
    }
    return OK;
}

void print_matrixes(struct mclassic_t *a_mclassic, struct mclassic_t *b_mclassic,
    struct mclassic_t *c_mclassic, struct mcsr_t *a_mcsr, struct mcsr_t *b_mcsr,
    struct mcsr_t *c_mcsr)
{
    print_output_submenu();
    int mode;
    if (scanf("%d", &mode) != 1)
        return;
    if (mode == OUTPUT_DEFAULT_MODE)
    {
        if (a_mclassic->nums)
        {
            if (a_mclassic->n > OUTPUT_DEFAULT_MAX_SIZE || a_mclassic->m > OUTPUT_DEFAULT_MAX_SIZE)
                printf("Matrix A is too big, chose another format\n");
            else
            {
                printf("Matrix A:\n");
                print_mclassic_default(a_mclassic);
                printf("\n");
            }
        }
        if (b_mclassic->nums)
        {
            if (b_mclassic->n > OUTPUT_DEFAULT_MAX_SIZE || b_mclassic->m > OUTPUT_DEFAULT_MAX_SIZE)
                printf("Matrix B is too big, chose another format\n");
            else
            {
                printf("Matrix B:\n");
                print_mclassic_default(b_mclassic);
                printf("\n");
            }
        }
        if (c_mclassic->nums)
        {
            if (c_mclassic->n > OUTPUT_DEFAULT_MAX_SIZE || c_mclassic->m > OUTPUT_DEFAULT_MAX_SIZE)
                printf("Matrix C is too big, chose another format\n");
            else
            {
                printf("Matrix C:\n");
                print_mclassic_default(c_mclassic);
                printf("\n");
            }
        }
    }
    else if (mode == OUTPUT_COORD_MODE)
    {
        if (a_mcsr->an)
        {
            printf("Matrix A:\n");
            print_mcsr_coord(a_mcsr);
            printf("\n");
        }
        if (b_mcsr->an)
        {
            printf("Matrix B:\n");
            print_mcsr_coord(b_mcsr);
            printf("\n");
        }
        if (c_mcsr->an)
        {
            printf("Matrix C:\n");
            print_mcsr_coord(c_mcsr);
            printf("\n");
        }
    }
    else if (mode == OUTPUT_CSR_MODE)
    {
        if (a_mcsr->an)
        {
            printf("Matrix A:\n");
            print_mcsr(a_mcsr);
            printf("\n");
        }
        if (b_mcsr->an)
        {
            printf("Matrix B:\n");
            print_mcsr(b_mcsr);
            printf("\n");
        }
        if (c_mcsr->an)
        {
            printf("Matrix C:\n");
            print_mcsr(c_mcsr);
            printf("\n");
        }
    }
}
