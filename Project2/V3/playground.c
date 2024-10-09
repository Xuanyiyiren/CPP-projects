#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mat_mul.h"

int main()
{
    srand(12345);
    FILE *file;
    struct timeval start, end;
    double time_spent;
    file = fopen("testlog.csv", "w");
    fprintf(file, "Matrix_size, Time_Comsuming(ms)\n");
    size_t mat_size = 0;
    // printf("Please input the matrix size(Bigger then 5): ");
    // // int sca_check = scanf("%ld", &mat_size);
    // if (sca_check != 1)
    // {
    //     fprintf(stderr, "Do not get your iuput!\n");
    //     return -1;
    // }
    for (mat_size = 100; mat_size <= 2000; mat_size += 100)
    {
        printf("The matrix size is %ld\n", mat_size);

        float *mat1 = (float *)malloc((mat_size * mat_size) * sizeof(float));
        for (size_t i = 0; i < mat_size * mat_size; i++)
            mat1[i] = ((float)rand() * 2 - RAND_MAX) / RAND_MAX;
        printf("Creating the frist matrix successfully ...\n");
        // printf("The head of first matrix is : \n");
        // display_mat(mat1, 5, 5);
        // printf("\n");

        float *mat2 = (float *)malloc((mat_size * mat_size) * sizeof(float));
        for (size_t i = 0; i < mat_size * mat_size; i++)
            mat2[i] = (float)rand() / RAND_MAX;
        printf("Creating the second matrix successfully ...\n");
        // printf("The head of second matrix is : \n");
        // display_mat(mat2, 5, 5);
        // printf("\n");

        gettimeofday(&start, NULL);
        float *mat3 = mat_mul(mat1, mat2, mat_size, mat_size, mat_size, mat_size);
        gettimeofday(&end, NULL);
        time_spent = ((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0) * 1000;
        if (mat3)
        {
            printf("Calculating the third matrix successfully ...\n");
            printf("Time comsuming is : %f ms\n", time_spent);
            fprintf(file, "%ld, %f\n", mat_size, time_spent);
            // printf("The third matrix is : \n");
            // display_mat(mat3, 5, 5);
        }
        free(mat1);
        free(mat2);
        free(mat3);
    }
    return 0;
}