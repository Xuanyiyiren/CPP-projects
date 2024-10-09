// mat_mul.c
#include <stdio.h>
#include <stdlib.h>
#include "mat_mul.h"

void display_mat(const float *mat, size_t row, size_t col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%f\t", mat[i * col + j]);
        }
        printf("\n");
    }
}

float *mat_mul(float *mat1, float *mat2, size_t row1, size_t col1, size_t row2, size_t col2)
{
    if (col1 != row2)
    {
        fprintf(stderr, "Shape do not match!");
        return NULL;
    }
    float *mat_out = (float *)malloc((row1 * col2) * sizeof(float));
    float temp = 0;
    for (size_t i = 0; i < row1; i++)
    {
        for (size_t j = 0; j < col2; j++)
        {
            temp = 0;
            // printf("mat3[%ld][%ld] / mat3[]= ", i, j);
            for (size_t k = 0; k < col1; k++)
            {
                // printf("%f * %f + ", mat1[i * col1 + k], mat2[k * col2 + j]);
                temp += mat1[i * col1 + k] * mat2[k * col2 + j];
            }
            // printf(" = %f , stored in mat[%ld]\n", temp, i * col1 + j);
            mat_out[i * col2 + j] = temp;
        }
    }
    return mat_out;
}