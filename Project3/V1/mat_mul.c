// mat_mul.c
#include <stdio.h>
#include <stdlib.h>
#include "mat_mul.h"

void display_mat(const float *mat, size_t row, size_t col)
{
    if (mat == NULL)
    {
        fprintf(stderr, "display_mat(): The input ptr cannot be NULL!\n");
        return;
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%f\t", mat[i * col + j]);
        }
        printf("\n");
    }
}

float *create_random_matrix(size_t row, size_t col)
{
    size_t mat_size = row * col;
    float *mat = (float *)malloc(mat_size * sizeof(float));
    for (size_t i = 0; i < mat_size; i++)
        mat[i] = (float)rand() / RAND_MAX;
    if (mat == NULL)
        fprintf(stderr, "Create an empty matrix?\n");
    return mat;
}

float *create_increasing_matrix(size_t row, size_t col)
{
    size_t mat_size = row * col;
    float *mat = (float *)malloc(mat_size * sizeof(float));
    for (size_t i = 0; i < mat_size; i++)
        mat[i] = (float)i;
    if (mat == NULL)
        fprintf(stderr, "Create an empty matrix?\n");
    return mat;
}

float *create_identity_matrix(size_t mat_length)
{
    size_t mat_size = mat_length * mat_length;
    float *mat = (float *)malloc(mat_size * sizeof(float));
    for (size_t i = 0; i < mat_size; i++)
        mat[i] = 0.f;
    for (size_t i = 0; i < mat_length; i++)
        mat[i * mat_length + i] = 1.f;
    if (mat == NULL)
        fprintf(stderr, "Create an empty matrix?\n");
    return mat;
}

float *mat_mul(float *mat1, float *mat2, size_t row1, size_t col1, size_t row2, size_t col2)
{
    if (mat1 == NULL)
    {
        fprintf(stderr, "mat_mul(): The frist input ptr cannot be NULL!\n");
        return NULL;
    }
    if (mat1 == NULL)
    {
        fprintf(stderr, "mat_mul(): The second input ptr cannot be NULL!\n");
        return NULL;
    }
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

void swap_tow_float(float *a, float *b)
{
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void mat_transpose(float *mat, size_t row, size_t col)
{
    size_t swap_times = 0;
    printf("[%ld, %ld]\n", row, col);
    for (size_t j = 0; j < col; j++)
    {
        for (size_t i = 0; i < row; i++)
        {
            if ((j * row + i) < (i * col + j))
            {
                swap_times++;
                printf("Swap from : [%ld, %ld]<->[%ld]\n", i, j, i * col + j);
                printf("Swap to   : [%ld, %ld]<->[%ld]\n", j, i, j * row + i);
                printf("\n");
                // printf("After this swap : the matrix is : \n");
                // display_mat(mat);
                swap_tow_float(mat + j * row + i, mat + i * col + j);
            }
        }
    }
    printf("Swap %ld times.\n", swap_times);
}

float *mat_transposed(float *mat, size_t row, size_t col)
{
    float *new_mat = (float *)malloc(row * col * sizeof(float));
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            new_mat[j * row + i] = mat[i * col + j];
        }
    }
    return new_mat;
}