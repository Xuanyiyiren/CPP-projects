#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mat_mul.h"

int main()
{
    srand(12345);

    clock_t start, end;
    double cpu_time_used = 0;

    size_t mat_size = 0;
    printf("Please input the matrix size(Bigger then 5): ");
    int sca_check = scanf("%ld", &mat_size);
    if (sca_check != 1)
    {
        fprintf(stderr, "Do not get your iuput!\n");
        return -1;
    }
    printf("The matrix size is %ld", mat_size);

    float *mat1 = (float *)malloc((mat_size * mat_size) * sizeof(float));
    for (size_t i = 0; i < mat_size * mat_size; i++)
        mat1[i] = ((float)rand() * 2 - RAND_MAX) / RAND_MAX;
    printf("The head of first matrix is : \n");
    display_mat(mat1, 5, 5);
    printf("\n");

    float *mat2 = (float *)malloc((mat_size * mat_size) * sizeof(float));
    for (size_t i = 0; i < mat_size * mat_size; i++)
        mat2[i] = (float)rand() / RAND_MAX;
    printf("The head of second matrix is : \n");
    display_mat(mat2, 5, 5);
    printf("\n");

    start = clock();
    float *mat3 = mat_mul(mat1, mat2, mat_size, mat_size, mat_size, mat_size);
    end = clock();
    cpu_time_used = (end - start) / CLOCKS_PER_SEC * 1000;
    if (mat3)
    {
        printf("The third matrix is : \n");
        display_mat(mat3, 5, 5);
    }

    printf("Time comsuming is : %f ms\n", cpu_time_used);
    free(mat1);
    free(mat2);
    free(mat3);

    return 0;
}