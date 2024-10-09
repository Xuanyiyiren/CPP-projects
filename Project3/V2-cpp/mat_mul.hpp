// mat_mul.hpp
#pragma once
#include <functional>
// #include <cstddef> // Include this header for size_t

// Function to display a matrix
void display_mat(const float *mat, size_t row, size_t col);

// Function to create a randomly initilized matrix, with every element random from 0 to 1
float *create_random_matrix(size_t row, size_t col);

// Function to create a matrix whose elements are 0, 1, 2, ...
float *create_increasing_matrix(size_t row, size_t col);

// create an identity matrix with shape (mat_length, mat_length)
float *create_identity_matrix(size_t mat_length);

// Function to transpose a matrix not in-place
float *mat_transposed(const float *mat, size_t row, size_t col);

// Function to multiply two matrices
float *mat_mul(const float *mat1, const float *mat2, size_t row1, size_t col1, size_t row2, size_t col2);

float *mat_mul(const float *mat1, const float *mat2, size_t row1, size_t col1, size_t row2, size_t col2, std::function<float(const float *, const float *, size_t)> _dot_product);
