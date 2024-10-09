// playground2.cpp

#include <iostream>
#include <cstdlib>
#include <chrono>
#include "mat_mul.hpp"
#include "dotproduct.hpp"
#include <fstream>

#define HEADLENGTH 5
#define AVE_TIME 10
#define TIME_START start = std::chrono::steady_clock::now();
#define TIME_END(NAME)                                                                     \
    end = std::chrono::steady_clock::now();                                                \
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
    std::cout << (NAME) << " : duration = " << duration << "ms" << std::endl;

auto start = std::chrono::steady_clock::now();
auto end = std::chrono::steady_clock::now();
auto duration = 0L;
auto dur_ave = 0L;

int main()
{
    srand(12345);
    std::ofstream outFile("../testlog.csv");
    if (outFile.is_open())
    {
        outFile << "Matrix_Length, naive_dotprodoct, unloop, OpenMP, avx2, avx2+OpenMP\n";
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl; // 错误处理
    }

    size_t mat_length_step = 1 << 7; // 128
    // size_t mat_length_end = 1 << 9;

    size_t mat_length_end = 1 << 11; // 2048

    for (int mat_length = mat_length_step; mat_length <= mat_length_end; mat_length += mat_length_step)
    {
        std::cout << "The matrice's length is : " << mat_length << std::endl;
        outFile << mat_length << ", ";
        size_t row1 = mat_length, col1 = mat_length;
        float *mat1 = create_random_matrix(row1, col1);
        std::cout << "The head of the first Matrix is : " << std::endl;
        display_mat(mat1, HEADLENGTH, HEADLENGTH);

        size_t row2 = mat_length, col2 = mat_length;
        float *mat2 = create_random_matrix(row2, col2);
        std::cout << "The head of the second Matrix is: " << std::endl;
        display_mat(mat2, HEADLENGTH, HEADLENGTH);
        float *result = nullptr;
        std::cout << "=======================" << std::endl;

        dur_ave = 0L;
        for (size_t testid = 0; testid < AVE_TIME + 2; testid++)
        {
            TIME_START
            result = mat_mul(mat1, mat2, row1, col1, row2, col2, dotproduct);
            TIME_END("Naive product")
            if (testid >= 2)
                dur_ave += duration;
        }
        dur_ave /= AVE_TIME;
        outFile << dur_ave << ", ";
        std::cout << "Their multiplication's head is: " << std::endl;
        display_mat(result, HEADLENGTH, HEADLENGTH);
        delete[] result;
        std::cout << "=======================" << std::endl;

        dur_ave = 0L;
        for (size_t testid = 0; testid < AVE_TIME + 2; testid++)
        {
            TIME_START
            result = mat_mul(mat1, mat2, row1, col1, row2, col2, dotproduct_unloop);
            TIME_END("product_unloop")
            if (testid >= 2)
                dur_ave += duration;
        }
        dur_ave /= AVE_TIME;
        outFile << dur_ave << ", ";
        std::cout << "Their multiplication is is: " << std::endl;
        display_mat(result, HEADLENGTH, HEADLENGTH);
        delete[] result;
        std::cout << "=======================" << std::endl;

        dur_ave = 0L;
        for (size_t testid = 0; testid < AVE_TIME + 2; testid++)
        {
            TIME_START
            result = mat_mul(mat1, mat2, row1, col1, row2, col2, dotproduct_omp);
            TIME_END("OpenMP")
            if (testid >= 2)
                dur_ave += duration;
        }
        dur_ave /= AVE_TIME;
        outFile << dur_ave << ", ";
        std::cout << "Their multiplication is is: " << std::endl;
        display_mat(result, HEADLENGTH, HEADLENGTH);
        delete[] result;
        std::cout << "=======================" << std::endl;

        dur_ave = 0L;
        for (size_t testid = 0; testid < AVE_TIME + 2; testid++)
        {
            TIME_START
            result = mat_mul(mat1, mat2, row1, col1, row2, col2, dotproduct_avx2);
            TIME_END("product_avx2")
            if (testid >= 2)
                dur_ave += duration;
        }
        dur_ave /= AVE_TIME;
        outFile << dur_ave << ", ";
        std::cout << "Their multiplication is is: " << std::endl;
        display_mat(result, HEADLENGTH, HEADLENGTH);
        delete[] result;
        std::cout << "=======================" << std::endl;

        dur_ave = 0L;
        for (size_t testid = 0; testid < AVE_TIME + 2; testid++)
        {
            TIME_START
            result = mat_mul(mat1, mat2, row1, col1, row2, col2, dotproduct_avx2_omp);
            TIME_END("avx2 + OpenMP")
            if (testid >= 2)
                dur_ave += duration;
        }
        dur_ave /= AVE_TIME;
        outFile << dur_ave << "\n";
        std::cout << "Their multiplication is is: " << std::endl;
        display_mat(result, HEADLENGTH, HEADLENGTH);
        delete[] result;
        std::cout << "=======================" << std::endl;

        delete[] mat1;
        delete[] mat2;
        std::cout << std::endl
                  << std::endl;
    }
    outFile.close();
    return 0;
}
