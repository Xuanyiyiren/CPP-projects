#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mat_mul.h"

int main()
{
    srand(12345);
    size_t row = 3, col = 5;
    float *mat = create_increasing_matrix(row, col);
    printf("The frist Matrix : \n");
    display_mat(mat, row, col);

    float *mat_t = mat_transposed(mat, row, col);
    printf("The transposed Matrix : \n");
    display_mat(mat_t, col, row);

    free(mat);
    free(mat_t);

    // float *idd = create_identity_matrix(col);
    // printf("The identity Matrix : \n");
    // display_mat(idd, col, col);

    // float *result = mat_mul(mat, idd, row, col, col, col);
    // printf("The result Matrix : \n");
    // display_mat(result, row, col);

    // free(idd);
    // free(result);
}