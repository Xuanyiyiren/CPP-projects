// playground2.cpp

#include <iostream>
// #include <cstdlib>
#include "mat_mul.hpp"
// #include "dotproduct.hpp"

int main()
{
    srand(12345);
    size_t row = 3, col = 5;
    float *mat = create_increasing_matrix(row, col);

    std::cout << "The first Matrix: " << std::endl;
    display_mat(mat, row, col);

    float *idd = create_identity_matrix(col);
    std::cout << "The identity Matrix: " << std::endl;
    display_mat(idd, col, col);

    float *result = mat_mul(mat, idd, row, col, col, col);
    std::cout << "mat * idd is: " << std::endl;
    display_mat(result, row, col);

    size_t row2 = 5, col2 = 4;

    float *mat2 = create_increasing_matrix(row2, col2);
    std::cout << "mat2 is: " << std::endl;
    display_mat(mat2, row2, col2);
    float *result2 = mat_mul(mat, mat2, row, col, row2, col2);
    std::cout << "mat * mat2 is: " << std::endl;
    display_mat(result2, row, col2);

    delete[] mat;
    delete[] idd;
    delete[] result;

    return 0;
}
