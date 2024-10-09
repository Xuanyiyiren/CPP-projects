// mat_mul.h
#ifndef __MAT_MUL__
#define __MAT_MUL__
#include <stddef.h> // Include this header for size_t

// Function to display a matrix
void display_mat(const float *mat, size_t row, size_t col);

// Function to create a randomly initilized matrix, with every element random from 0 to 1
float *create_random_matrix(size_t row, size_t col);

// Function to create a matrix whose elements are 0, 1, 2, ...
float *create_increasing_matrix(size_t row, size_t col);

// create an identity matrix with shape (mat_length, mat_length)
float *create_identity_matrix(size_t mat_length);

// Function to multiply two matrices
float *mat_mul(float *mat1, float *mat2, size_t row1, size_t col1, size_t row2, size_t col2);

// Function to swap two float pointers;
void swap_tow_float(float *a, float *b);

// Function to transpose a matrix not in-place
float *mat_transposed(float *mat, size_t row, size_t col);

#endif // MATRIX_OPERATIONS_H
