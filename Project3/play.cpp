#include <iostream>
#include <functional>

float simple_dot(const float *a, const float *b, size_t n)
{
    float result = 0;
    for (size_t i = 0; i < n; ++i)
    {
        result += a[i] * b[i];
    }
    return result;
}

float *mat_mul(const float *mat1, const float *mat2, size_t row1, size_t col1, size_t row2, size_t col2,
               std::function<float(const float *, const float *, size_t)> dot_product = simple_dot)
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
            mat_out[i * col2 + j] = dot_product(mat1 + i * col1, mat2_T + j * col1, col1);
        }
    }
    delete[] mat2_T;
    return mat_out;
}

int main()
{
    const float mat1[] = {1, 2, 3, 4};
    const float mat2[] = {5, 6, 7, 8};
    size_t row1 = 2, col1 = 2, row2 = 2, col2 = 2;

    float *result = mat_mul(mat1, mat2, row1, col1, row2, col2);

    // 输出结果
    for (size_t i = 0; i < row1; ++i)
    {
        for (size_t j = 0; j < col2; ++j)
        {
            std::cout << result[i * col2 + j] << " ";
        }
        std::cout << std::endl;
    }

    delete[] result; // 记得释放内存
    return 0;
}
