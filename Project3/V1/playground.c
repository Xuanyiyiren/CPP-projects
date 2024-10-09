#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mat_mul.h"

int main()
{
    srand(12345);
    struct timeval start, end;
    double time_spent;
    size_t mat_size = 1000;
    printf("The matrix size is %ld\n", mat_size);

    // float *mat1 = (float *)malloc((mat_size * mat_size) * sizeof(float));
    // for (size_t i = 0; i < mat_size * mat_size; i++)
    //     mat1[i] = ((float)rand() * 2 - RAND_MAX) / RAND_MAX;
    float *mat1 = create_random_matrix(mat_size, mat_size);
    for (int i = 0; i < mat_size * mat_size; i++)
    {
        mat1[i] = 2 * mat1[i] - 1;
    }
    printf("Creating the frist matrix successfully ...\n");
    printf("The head of the first matrix is : \n");
    display_mat(mat1, 5, 5);
    printf("\n");

    float *mat2 = create_random_matrix(mat_size, mat_size);
    for (int i = 0; i < mat_size * mat_size; i++)
    {
        mat2[i] = 2 * mat2[i] - 1;
    }
    printf("Creating the second matrix successfully ...\n");
    printf("The head of the second matrix is : \n");
    display_mat(mat2, 5, 5);
    printf("\n");

    gettimeofday(&start, NULL);
    float *mat3 = mat_mul(mat1, mat2, mat_size, mat_size, mat_size, mat_size);
    gettimeofday(&end, NULL);
    time_spent = ((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0) * 1000;
    if (mat3)
    {
        printf("Calculating the third matrix successfully ...\n");
        printf("Time comsuming is : %f ms\n", time_spent);
        // fprintf(file, "%ld, %f\n", mat_size, time_spent);
        printf("The head of the third matrix is : \n");
        display_mat(mat3, 5, 5);
    }
    free(mat1);
    free(mat2);
    free(mat3);
    return 0;
}