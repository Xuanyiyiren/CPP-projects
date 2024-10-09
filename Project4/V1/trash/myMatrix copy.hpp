// myMatrix.hpp
#pragma once

#include <iostream>
#include <memory>
#include <iomanip>
#include <random>

template <typename Element>
class Mymat
{
public:
    size_t rows;
    size_t cols;
    Element *elements;

public:
    // Constructor: Initializes a matrix with the given number of rows and columns,
    //              and sets all elements to zero.
    Mymat(size_t rows = 0, size_t cols = 0) : rows(rows), cols(cols)
    {
        if (rows == 0 || cols == 0)
            elements = nullptr;
        else
            elements = new Element[rows * cols]{};
    }

    // Destructor: Frees the memory allocated for the matrix elements.
    ~Mymat() { delete[] elements; }

    // Help to rebuild `operator<<`: Outputs the matrix to the given output stream.
    std::ostream &_stream_insertion_operator(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Mymat &mat) { return mat._stream_insertion_operator(os); }

    /**
     * @brief Reshapes the matrix to the specified number of rows and columns.
     *
     * This function attempts to reshape the current matrix to the given dimensions.
     * If the number of columns is not provided (i.e., `cols` is 0), it will calculate
     * the number of columns such that the total number of elements remains the same.
     *
     * @return bool Returns `true` if the reshape operation is successful, otherwise `false`.
     *
     * @note The reshape operation will fail if the total number of elements in the new
     *       dimensions does not match the current number of elements in the matrix.
     */
    bool reshape(size_t rows, size_t cols = 0);

    // Retrieves the element at the specified row and column.
    Element get_element(size_t row, size_t col) const;

    // Sets the element at the specified row and column to the given value.
    bool set_element(size_t row, size_t col, Element value);

    // Creates and returns an identity matrix of the specified size.
    static Mymat create_identity_matrix(size_t mat_length);

    // Creates and returns a matrix with elements increasing sequentially from 0.
    static Mymat create_increasing_matrix(size_t row, size_t col);

    /**
     * @brief Create a matrix with random elements
     *
     * This function generates a matrix with the specified number of rows and columns,
     * and fills it with random elements using the provided random number generator.
     * The elements of the matrix will be uniformly distributed within the specified range from `a` to `b`.
     *
     * @param gen The random number generator to use, this param is pass by reference!
     */
    static Mymat create_random_matrix(size_t rows, size_t cols, std::default_random_engine &gen, Element a = 0, Element b = 1);
};

template <typename Element>
std::ostream &Mymat<Element>::_stream_insertion_operator(std::ostream &os) const
{
    if (elements == nullptr)
    {
        std::cerr << "Mymat::display(): This matrix is NULL!" << std::endl;
        os << "Empty matrix!" << std::endl;
        return os;
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            os << std::setw(10) << elements[i * cols + j] << "\t";
        }
        os << std::endl;
    }
    return os;
}

template <typename Element>
inline bool Mymat<Element>::reshape(size_t rows, size_t cols)
{
    size_t mat_size = (this->rows) * (this->cols);
    if (cols == 0)
    {
        if (mat_size % rows == 0)
            cols = mat_size / rows;
        else
        {
            std::cerr << "reshaping failed" << std::endl;
            return false;
        }
    }
    else
    {
        if (mat_size != rows * cols)
        {
            std::cerr << "reshaping failed" << std::endl;
            return false;
        }
    }
    this->rows = rows;
    this->cols = cols;
    return true;
}

template <typename Element>
Element Mymat<Element>::get_element(size_t row, size_t col) const
{
    if (row > rows || col > cols)
    {
        std::cerr << "getElement(): indices are out of range" << std::endl;
        return 0;
    }
    else
        return elements[row * cols + col];
}

template <typename Element>
bool Mymat<Element>::set_element(size_t row, size_t col, Element value)
{
    if (row > rows || col > cols)
    {
        std::cerr << "getElement(): indices are out of range" << std::endl;
        return false;
    }
    else
    {
        elements[row * cols + col] = value;
        return true;
    }
}

template <typename Element>
Mymat<Element> Mymat<Element>::create_identity_matrix(size_t mat_length)
{
    Mymat<Element> eye(mat_length, mat_length);
    for (size_t i = 0; i < mat_length; i++)
        eye.elements[i * mat_length + i] = 1;
    return eye;
}

template <typename Element>
Mymat<Element> Mymat<Element>::create_increasing_matrix(size_t rows, size_t cols)
{
    // std::cout << "Hello! create_increasing_matrix()" << std::endl;
    Mymat<Element> mat(rows, cols);
    size_t mat_size = rows * cols;
    for (size_t i = 0; i < mat_size; i++)
    {
        mat.elements[i] = i;
    }
    // std::cout << "Bye  ! create_increasing_matrix()" << std::endl;
    return mat;
}

template <typename Element>
Mymat<Element> Mymat<Element>::create_random_matrix(size_t rows, size_t cols, std::default_random_engine &gen, Element a, Element b)
{
    Mymat<Element> mat(rows, cols);
    std::uniform_real_distribution<> dis(a, b);
    size_t mat_size = rows * cols;
    for (size_t i = 0; i < mat_size; i++)
        mat.elements[i] = static_cast<Element>(dis(gen));
    return mat;
}
