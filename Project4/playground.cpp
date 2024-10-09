#include <iostream>
#include <vector>
#include <random>

std::vector<double> initializeRandomFloats(size_t size, std::default_random_engine &engine, double a = 0., double b = 1.)
{
    std::uniform_real_distribution<double> distribution(a, b);
    std::vector<double> vec(size);
    for (auto &value : vec)
    {
        value = distribution(engine);
    }
    return vec;
}

int main()
{
    const size_t size = 10;
    // 设置随机数种子
    std::random_device rd; // 获取随机数种子
    unsigned int random_seed = rd();
    std::cout << "The random seed is : " << random_seed << std::endl;
    std::default_random_engine engine(random_seed);

    // 初始化浮点数数组
    std::vector<double> myFloats = initializeRandomFloats(size, engine);
    std::vector<double> myFloats2 = initializeRandomFloats(size, engine);

    // 打印结果
    for (const auto &value : myFloats)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    // 打印结果
    for (const auto &value : myFloats2)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
