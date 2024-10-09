#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mat_mul.h"

int main()
{
    clock_t start, end;
    double cpu_time_used = 0;

    size_t row1 = 3;
    size_t col1 = 4;
    float *mat1 = (float *)malloc((row1 * col1) * sizeof(float));
    for (size_t i = 0; i < row1 * col1; i++)
        mat1[i] = i;
    printf("The first matrix is : \n");
    display_mat(mat1, row1, col1);
    printf("\n");

    size_t row2 = 4;
    size_t col2 = 5;
    float *mat2 = (float *)malloc((row2 * col2) * sizeof(float));
    for (size_t i = 0; i < row2 * col2; i++)
        mat2[i] = i;
    printf("The second matrix is : \n");
    display_mat(mat2, row2, col2);
    printf("\n");

    start = clock();
    float *mat3 = mat_mul(mat1, mat2, row1, col1, row2, col2);
    end = clock();
    cpu_time_used = (end - start) / CLOCKS_PER_SEC * 1000;
    if (mat3)
    {
        size_t row3 = row1;
        size_t col3 = col2;
        printf("The third matrix is : \n");
        display_mat(mat3, row3, col3);
    }

    printf("Time comsuming is : %f ms\n", cpu_time_used);
    free(mat1);
    free(mat2);
    free(mat3);

    return 0;
}