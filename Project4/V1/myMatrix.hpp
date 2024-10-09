// myMatrix.hpp
#pragma once

#include <iostream>
#include <cstring>
#include <iomanip>
#include <random>
#include <utility> // std::pair in Mymat::shape()
#include "dotproduct.hpp"

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

    // Hard copy!
    Mymat(const Mymat &mat) : rows(mat.rows), cols(mat.cols)
    {
        size_t mat_size = rows * cols;
        elements = new Element[mat_size]{};
        std::memcpy(elements, mat.elements, mat_size * sizeof(Element));
    }

    // Destructor: Frees the memory allocated for the matrix elements.
    ~Mymat()
    {
        delete[] elements;
    }

    // Help to rebuild `operator<<`: Outputs the matrix to the given output stream.
    std::ostream &_stream_insertion_operator(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Mymat &mat) { return mat._stream_insertion_operator(os); }

    // Hard copy!
    // Only if the mat object on the left has the same size of the right one.
    Mymat operator=(const Mymat &mat);

    bool operator==(const Mymat &mat) const;

    std::pair<size_t, size_t> shape() const
    {
        return std::make_pair(rows, cols);
    }

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

    // Transpose, return a new mat;
    Mymat T() const;

    // Matrix multiplication
    Mymat operator*(const Mymat &mat_r) const;

    Mymat operator+(const Mymat &mat_r) const;
    Mymat operator-(const Mymat &mat_r) const;

    Mymat operator*(Element coef) const;
    friend Mymat operator*(Element coef, const Mymat &mat) { return mat * coef; }

    Mymat operator/(Element coef) const;
};

template <typename Element>
Mymat<Element> Mymat<Element>::operator=(const Mymat<Element> &mat)
{
    size_t mat_size = mat.rows * mat.cols;
    if (rows * cols == mat_size)
    {
        rows = mat.rows;
        cols = mat.cols;
        elements = new Element[mat_size]{};
        std::memcpy(elements, mat.elements, mat_size * sizeof(Element));
    }
    else
    {
        std::cerr << "Mymat::Operator=(): Matrix size do not match!" << std::endl;
    }
    return *this;
}

template <typename Element>
bool Mymat<Element>::operator==(const Mymat<Element> &mat) const
{
    if ((rows == mat.rows) && (cols == mat.cols))
    {
        size_t mat_size = rows * cols;
        return memcmp(elements, mat.elements, mat_size * sizeof(Element)) == 0;
    }
    else
        return false;
}

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
bool Mymat<Element>::reshape(size_t rows, size_t cols)
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

template <typename Element>
Mymat<Element> Mymat<Element>::T() const
{
    Mymat mat_t(cols, rows);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            mat_t.elements[j * mat_t.cols + i] = elements[i * cols + j];
        }
    }
    return mat_t;
}

template <typename Element>
Mymat<Element> Mymat<Element>::operator*(const Mymat<Element> &mat_r) const
{
    if (elements == nullptr || rows == 0 || cols == 0)
    {
        fprintf(stderr, "Mymat::operator*(): The frist input ptr cannot be NULL!\n");
        return Mymat();
    }
    if (mat_r.elements == nullptr || mat_r.rows == 0 || mat_r.cols == 0)
    {
        fprintf(stderr, "Mymat::operator*(): The second input ptr cannot be NULL!\n");
        return Mymat();
    }
    if (cols != mat_r.rows)
    {
        fprintf(stderr, "Mymat::operator*(): Shape do not match! The cols for the frist matrix and the rows for the second matrix must be equal!");
        return Mymat();
    }
    Mymat<Element> result(rows, mat_r.cols);
    Element temp = 0;
    for (size_t i = 0; i < result.rows; i++)
    {
        for (size_t j = 0; j < result.cols; j++)
        {
            temp = 0;
            for (size_t k = 0; k < cols; k++)
                temp += elements[i * cols + k] * mat_r.elements[k * mat_r.cols + j];
            result.elements[i * result.cols + j] = temp;
        }
    }
    return result;
}

template <typename Element>
Mymat<Element> Mymat<Element>::operator+(const Mymat<Element> &mat_r) const
{
    if (elements == nullptr || rows == 0 || cols == 0)
    {
        fprintf(stderr, "Mymat::operator+(): The frist input ptr cannot be NULL!\n");
        return Mymat();
    }
    if (mat_r.elements == nullptr || mat_r.rows == 0 || mat_r.cols == 0)
    {
        fprintf(stderr, "Mymat::operator+(): The second input ptr cannot be NULL!\n");
        return Mymat();
    }
    if (!(rows == mat_r.rows || cols == mat_r.cols))
    {
        fprintf(stderr, "Mymat::operator+(): Shape do not match! Their shape must be the same.");
        return Mymat();
    }
    Mymat<Element> result(rows, cols);
    size_t mat_size = rows * cols;
    for (size_t i = 0; i < mat_size; i++)
        result.elements[i] = elements[i] + mat_r.elements[i];
    return result;
}

template <typename Element>
Mymat<Element> Mymat<Element>::operator-(const Mymat<Element> &mat_r) const
{
    if (elements == nullptr || rows == 0 || cols == 0)
    {
        fprintf(stderr, "Mymat::operator+(): The frist input ptr cannot be NULL!\n");
        return Mymat();
    }
    if (mat_r.elements == nullptr || mat_r.rows == 0 || mat_r.cols == 0)
    {
        fprintf(stderr, "Mymat::operator+(): The second input ptr cannot be NULL!\n");
        return Mymat();
    }
    if (!(rows == mat_r.rows || cols == mat_r.cols))
    {
        fprintf(stderr, "Mymat::operator+(): Shape do not match! Their shape must be the same.");
        return Mymat();
    }
    Mymat<Element> result(rows, cols);
    size_t mat_size = rows * cols;
    for (size_t i = 0; i < mat_size; i++)
        result.elements[i] = elements[i] - mat_r.elements[i];
    return result;
}

template <typename Element>
Mymat<Element> Mymat<Element>::operator*(Element coef) const
{
    if (elements == nullptr || rows == 0 || cols == 0)
    {
        fprintf(stderr, "Mymat::operator*(Element coef): The frist input ptr cannot be NULL!\n");
        return Mymat();
    }
    Mymat<Element> result(rows, cols);
    size_t mat_size = rows * cols;
    for (size_t i = 0; i < mat_size; i++)
        result.elements[i] = elements[i] * coef;
    return result;
}

template <typename Element>
Mymat<Element> Mymat<Element>::operator/(Element coef) const
{
    if (elements == nullptr || rows == 0 || cols == 0)
    {
        fprintf(stderr, "Mymat::operator*(Element coef): The frist input ptr cannot be NULL!\n");
        return Mymat();
    }
    Mymat<Element> result(rows, cols);
    size_t mat_size = rows * cols;
    for (size_t i = 0; i < mat_size; i++)
        result.elements[i] = elements[i] / coef;
    return result;
}