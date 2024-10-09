// mat_mul.cpp
#include <iostream>
#include <functional>
#include <iomanip>
#include "mat_mul.hpp"
#include "dotproduct.hpp"

// void display_mat(const float *mat, size_t row, size_t col)
// {
//     if (mat == nullptr)
//     {
//         std::cerr << "display_mat(): The input ptr cannot be NULL!" << std::endl;
//         return;
//     }
//     for (size_t i = 0; i < row; ++i)
//     {
//         for (size_t j = 0; j < col; ++j)
//         {
//             std::cout << mat[i * col + j] << "\t";
//         }
//         std::cout << std::endl;
//     }
// }

void display_mat(const float *mat, size_t row, size_t col)
{
    if (mat == nullptr)
    {
        std::cerr << "display_mat(): The input ptr cannot be NULL!" << std::endl;
        return;
    }
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            std::cout << std::setw(10) << mat[i * col + j] << "\t"; // 设置宽度为10
        }
        std::cout << std::endl;
    }
}

float *create_random_matrix(size_t row, size_t col)
{
    size_t mat_size = row * col;
    float *mat = new float[mat_size];
    for (size_t i = 0; i < mat_size; ++i)
        mat[i] = static_cast<float>(rand()) / RAND_MAX;
    return mat;
}

float *create_increasing_matrix(size_t row, size_t col)
{
    size_t mat_size = row * col;
    float *mat = new float[mat_size];
    for (size_t i = 0; i < mat_size; ++i)
        mat[i] = static_cast<float>(i);
    return mat;
}

float *create_identity_matrix(size_t mat_length)
{
    size_t mat_size = mat_length * mat_length;
    float *mat = new float[mat_size]();
    for (size_t i = 0; i < mat_length; ++i)
        mat[i * mat_length + i] = 1.f;
    return mat;
}

float *mat_transposed(const float *mat, size_t row, size_t col)
{
    float *new_mat = new float[row * col];
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            new_mat[j * row + i] = mat[i * col + j];
        }
    }
    return new_mat;
}

#include <functional>

float *mat_mul(const float *mat1, const float *mat2, size_t row1, size_t col1, size_t row2, size_t col2, std::function<float(const float *, const float *, size_t)> _dot_product)
{
    if (mat1 == nullptr || mat2 == nullptr)
    {
        std::cerr << "mat_mul(): Input ptr cannot be NULL!" << std::endl;
        return nullptr;
    }
    if (col1 != row2)
    {
        std::cerr << "Shape do not match!" << std::endl;
        return nullptr;
    }
    float *mat_out = new float[row1 * col2];
    float *mat2_T = mat_transposed(mat2, row2, col2);
    for (size_t i = 0; i < row1; ++i)
    {
        for (size_t j = 0; j < col2; ++j)
        {
            mat_out[i * col2 + j] = _dot_product(mat1 + i * col1, mat2_T + j * col1, col1);
        }
    }
    delete[] mat2_T;
    return mat_out;
}
