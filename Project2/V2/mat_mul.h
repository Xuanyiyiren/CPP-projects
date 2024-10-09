// mat_mul.h
#ifndef __MAT_MUL__
#define __MAT_MUL__

#include <stddef.h> // Include this header for size_t

// Function to display a matrix
void display_mat(const float *mat, size_t row, size_t col);

// Function to multiply two matrices
float *mat_mul(float *mat1, float *mat2, size_t row1, size_t col1, size_t row2, size_t col2);

#endif // MATRIX_OPERATIONS_H
