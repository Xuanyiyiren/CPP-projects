#include <iostream>
#include <cblas.h>

int main()
{
    int m = 2; // A的行数
    int n = 2; // B的列数
    int k = 2; // A的列数和B的行数

    double A[] = {1.0, 2.0, 3.0, 4.0}; // 2x2 矩阵 A
    double B[] = {5.0, 6.0, 7.0, 8.0}; // 2x2 矩阵 B
    double C[4];                       // 结果矩阵 C，大小为 2x2

    double alpha = 1.0;
    double beta = 0.0;

    // 矩阵乘法 C = alpha * A * B + beta * C
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, k, B, n, beta, C, n);

    std::cout << "Result Matrix C:" << std::endl;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << C[i * n + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
