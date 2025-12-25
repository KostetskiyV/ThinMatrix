#define _GNU_SOURCE

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "matrix_classic.h"
#include "matrix_csr.h"
#include "print_menu.h"
#include "matrix_manager.h"
#include "io_manager.h"
#include "error_codes.h"

#define END_MODE 0
#define INPUT_MODE 1
#define READ_TXT_MODE 2
#define PRINT_MODE 3
#define ADDITION_MODE 4

#define MATRIX_TXT_SOURCE "matrix.txt"

double calc_elapsed_time(const struct timespec *beg,
                         const struct timespec *end) {
    return ((end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 +
        (end->tv_nsec - beg->tv_nsec)) /
        1000.0 / 1000.0 / 1000.0;
}

int main(void)
{
    struct timespec start, end;
    int rc = OK;
    FILE *f_in;
    struct mclassic_t a_mclassic, b_mclassic, c_mclassic;
    struct mcsr_t a_mcsr, b_mcsr, c_mcsr;
    config(&a_mclassic, &b_mclassic, &c_mclassic, &a_mcsr, &b_mcsr, &c_mcsr);

    while (rc == OK)
    {
        int mode;
        print_menu();
        if (rc == OK && scanf("%d", &mode) != 1)
            rc = ERR_IO;
        if (rc == OK)
        {
            if (mode == END_MODE)
                break;

            switch (mode)
            {
                case INPUT_MODE:
                    rc = input_matrixes(stdin, &a_mclassic, &b_mclassic, &a_mcsr, &b_mcsr);
                    break;
                case READ_TXT_MODE:
                    f_in = fopen(MATRIX_TXT_SOURCE, "r");
                    if (!f_in)
                        rc = ERR_OPEN;
                    else
                    {
                        rc = input_matrixes(f_in, &a_mclassic, &b_mclassic, &a_mcsr, &b_mcsr);
                        fclose(f_in);
                    }
                    break;
                case PRINT_MODE:
                    print_matrixes(&a_mclassic, &b_mclassic, &c_mclassic, &a_mcsr, &b_mcsr, &c_mcsr);
                    break;
                case ADDITION_MODE:
                    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                    rc = mclassic_addition(&a_mclassic, &b_mclassic, &c_mclassic);
                    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

                    if (rc == OK)
                    {
                        size_t summem = count_mclassic_mem(&a_mclassic) + count_mclassic_mem(&b_mclassic) + count_mclassic_mem(&c_mclassic);
                        printf("Classic Matrix:\n");
                        printf("\tMemory cost: %lu Bytes\n", summem);
                        printf("\tTime: %lf s\n", calc_elapsed_time(&start, &end));
                    }

                    if (rc == OK)
                    {
                        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                        rc = mcsr_addition(&a_mcsr, &b_mcsr, &c_mcsr);
                        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                    }
                    if (rc == OK)
                    {
                        size_t summem = count_mcsr_mem(&a_mcsr) + count_mcsr_mem(&b_mcsr) + count_mcsr_mem(&c_mcsr);
                        printf("CSR Matrix:\n");
                        printf("\tMemory cost: %lu Bytes\n", summem);
                        printf("\tTime: %lf s\n", calc_elapsed_time(&start, &end));
                    }

                    break;
                default:
                    rc = ERR_MODE;
                    break;
            }
        }
    }

    free_matrixes(&a_mclassic, &b_mclassic, &c_mclassic, &a_mcsr, &b_mcsr, &c_mcsr);

    if (rc == ERR_IO)
        printf("Ошибка формата данных\n");
    else if (rc == ERR_RANGE)
        printf("Ошибка диапазона данных\n");
    else if (rc == ERR_MODE)
        printf("Несуществующий пункт меню\n");
    else if (rc == ERR_OPEN)
        printf("Ошибка открытия файла\n");
    else if (rc == ERR_MEM)
        printf("Out of memory!\n");
    else if (rc == ERR_MTR_UNINIT)
        printf("Матрицы неинициализированны!\n");
    else if (rc == ERR_VARIABLES_RANGE)
        printf("Размеры матриц не совпадают!\n");

    return rc;
}