# My Matrix Class Implementation

I implemented a template class called `Mymat` for representing matrices and providing various matrix operation functionalities. Here’s a summary of my completed work:

### 1. Basic Structure of the Matrix Class
   - **Template Class**: I created a template class `Mymat` that can handle different types of elements (such as `int`, `float`, `double`, etc.).
   - **Member Variables**:
     - `size_t rows`: The number of rows in the matrix.
     - `size_t cols`: The number of columns in the matrix.
     - `Element *elements`: A dynamic array pointing to the matrix elements.

### 2. Constructors and Destructor
   - **Default Constructor**: I initialized a matrix with specified rows and columns, setting all elements to zero.
   - **Copy Constructor**: I implemented deep copying of the matrix.
   - **Destructor**: I released the dynamically allocated memory.

### 3. Output Operator Overloading
   - **`operator<<`**: I overloaded the output operator to print the matrix to the standard output stream.

### 4. Assignment Operator Overloading
   - **`operator=`**: I implemented deep copy assignment for the matrix.

### 5. Comparison Operator Overloading
   - **`operator==`**: I compared whether two matrices are equal.

### 6. Matrix Shape Operations
   - **`shape()`**: I returned the shape of the matrix (number of rows and columns).
   - **`reshape()`**: I attempted to reshape the matrix to specified rows and columns.

### 7. Element Access and Modification
   - **`get_element()`**: I retrieved the element at a specified position.
   - **`set_element()`**: I set the element at a specified position.

### 8. Matrix Creation Functions
   - **`create_identity_matrix()`**: I created an identity matrix.
   - **`create_increasing_matrix()`**: I created a matrix with elements increasing from 0.
   - **`create_random_matrix()`**: I created a matrix with random elements.

### 9. Matrix Operations
   - **`T()`**: I returned the transpose of the matrix.
   - **`operator*`**: I implemented matrix multiplication.
   - **`operator+`**: I implemented matrix addition.
   - **`operator-`**: I implemented matrix subtraction.
   - **`operator*`**: I implemented scalar multiplication of the matrix.
   - **`operator/`**: I implemented scalar division of the matrix.

### 10. Error Handling
   - I added error handling logic in several operations, such as checking if the matrix is empty, if shapes match, etc., and output error messages when errors occur.

### 11. Others
   - **`dotproduct.hpp`**: I included the `dotproduct.hpp` header file, but the functionality within the code was not directly used.

### Summary
I have implemented a relatively complete matrix class that covers basic operations, creation, computation, and error handling for matrices. This class can handle different types of matrices and provides rich functionality to meet various matrix operation needs.

### TODO

- [ ] Copy operator overloading and copy constructor use shallow copying instead of deep copying
  - Implement using `shared_ptr` or manually track reference counts
- [ ] The previously implemented matrix operations generate new matrices, which is not suitable for large matrices as it leads to significant memory allocation. Need to overload operators like `+=`, `/=`.
- [ ] Specialize `Mymat<float>` for matrix multiplication using CPU acceleration techniques
  - OpenMP
  - AVX2 instruction set

### Outlook

The matrix transpose in OpenCV is implemented using another class `Matrixexpr` (might be misspelled) because in-place transpose of non-square matrices is not feasible; I'll explain this reason later.

However, just transposing a matrix would require copying the entire matrix, which is clearly inefficient. This is why OpenCV utilizes another class that seems to delay evaluation and computes it only when necessary.

This concept resembles functional programming because simply transposing a matrix is not trivial in computing, and mathematically, it is not simple either. A matrix represents a linear mapping, and the transpose is the dual mapping of that linear transformation. Elevating to the categorical level, it becomes a contravariant functor, filled with morphisms (going crazy here).

The essence of linear mapping is a function, and if we use the dual mapping to find the transpose of a matrix, it feels similar to lazy evaluation? This echoes functional programming's lazy evaluation.

#### Why can't a simple transpose be in-place?

Non-square matrices cannot achieve transpose in-place. You might think that transposing a matrix is just relocating a bunch of values, and since the targets are clear, how hard can it be? Yes, relocating things is precisely what the symmetric group does. If we flatten the matrix into a one-dimensional array (which is the essence of how computers store matrices), describing it in terms of symmetric groups is more appropriate. 

For square matrices, the effect of permutation is a group element with an order not exceeding 2, meaning that this permutation can easily be broken down into independent swap operations, which can be easily implemented using swap.

However, for non-square matrices, the permutation effect may be a high-order symmetric group element. This means that the permutation, once broken down, results in opposing rotations involving three or more elements swapping positions. It is not straightforward to know the order of the rotation, i.e., how many elements are swapping positions. This is the issue at hand. 

For example, here is the effect of transposing a 3x5 matrix:

![alt text](./V1/matrix_transpose.jpg)

There exist two 6-cycles, meaning 6 elements are involved in the swapping. This is unpredictable. While it is mathematically easy to identify such rotation structures, a computer must store this rotational structure, leading to unavoidable additional space complexity.
