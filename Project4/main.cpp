#include <iostream>
#include <iomanip>
template <typename Element>
class Mymat
{
    size_t rows;
    size_t cols;
    Element *elements;

public:
    Mymat(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        elements = new Element[rows * cols]{};
    }
    ~Mymat() { delete[] elements; }

    void display() const;
};

template <typename Element>
void Mymat<Element>::display() const
{
    if (elements == nullptr)
    {
        std::cerr << "Mymat::display(): This matrix is NULL!" << std::endl;
        return;
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << std::setw(10) << elements[i * cols + j] << "\t"; // 设置宽度为10
        }
        std::cout << std::endl;
    }
}

int main()
{
    Mymat<int> mat1(3, 3);
    mat1.display();
}