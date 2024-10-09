// main.cpp
#include <iostream>
#include <random>
#include "myMatrix.hpp"

int main()
{
    Mymat<int> mat1(4, 6);
    std::cout << mat1;
    mat1.set_element(0, 1, 19);
    std::cout << "mat1 with shape" << "(" << mat1.shape().first << "," << mat1.shape().second << ") : " << std::endl
              << mat1;

    Mymat<int> mat2 = Mymat<int>::create_identity_matrix(5);
    std::cout << std::endl
              << mat2;

    Mymat<int> mat3 = Mymat<int>::create_increasing_matrix(4, 5);
    std::cout << std::endl
              << mat3;

    mat3.reshape(10);
    std::cout << "After reshaping :" << std::endl
              << mat3;

    std::random_device rd; // 获取随机数种子
    unsigned int random_seed = rd();
    std::cout << "The random seed is : " << random_seed << std::endl;
    std::default_random_engine engine(random_seed);
    Mymat<float> mat4 = Mymat<float>::create_random_matrix(5, 5, engine);
    std::cout << std::endl
              << mat4;

    std::cout << "Testing copy constructor" << std::endl;
    std::cout << "mat1 = " << std::endl
              << mat1;

    Mymat<int> mat5 = mat1;
    std::cout << "mat5 = " << std::endl
              << mat5;
    mat5.set_element(2, 3, 100);
    std::cout << "mat5 = " << std::endl
              << mat5;

    Mymat<int> mat6(mat1.rows, mat1.cols);
    mat6 = mat5;
    std::cout << "mat6 = " << std::endl
              << mat6;

    std::cout << "mat5 == mat 6 ? " << (mat5 == mat6) << std::endl;
    std::cout << "mat5 == mat 6 ? " << (mat1 == mat6) << std::endl;
    mat6.reshape(6);
    std::cout << "Reshape mat6, mat5 == mat 6 ? " << (mat5 == mat6) << std::endl;

    std::cout << "mat1 = " << std::endl
              << mat1;
    std::cout << "mat1 transpose = " << std::endl
              << mat1.T();
}