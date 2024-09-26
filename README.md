# Neupy: A Simple Numpy Clone in C

!(neupy)[logo.png]

## Overview

**Neupy** is a basic implementation of the fundamental features of the NumPy library written in C. It provides multi-dimensional array support and operations commonly used in scientific computing, machine learning, and data manipulation. This project simulates the core array-based operations such as array creation, mathematical operations, reshaping, and matrix multiplication, offering a foundation for array manipulation in a style similar to Python’s NumPy.

## Features

- **Multi-dimensional arrays**: Support for creating arrays with arbitrary dimensions.
- **Mathematical operations**: Add, subtract, multiply, and divide arrays element-wise.
- **Matrix operations**: Matrix multiplication using traditional and Strassen algorithms.
- **Reshaping & Transposing**: Reshape arrays into different dimensions or transpose matrices.
- **Random Arrays**: Generate arrays with random values within a specified range.
- **Trigonometric & Exponential Functions**: Compute element-wise trigonometric functions like sine, cosine, and tangent, as well as power, square root, and exponentiation functions.

## Categories of Functions

### 1. **Array Creation Functions**
   - `create_NeuArray`: Create an empty array with a given shape.
   - `zeros`: Create an array filled with zeros.
   - `ones`: Create an array filled with ones.
   - `eye`: Create an identity matrix.
   - `randint`: Create an array filled with random integers.

### 2. **Array Inspection Functions**
   - `print_NeuArray`: Print the contents and shape of an array.
   - `len`: Calculate the total number of elements in an array.
   - `compare_NeuArray`: Compare two arrays element-wise.
   - `max`: Find the maximum value in the array.
   - `min`: Find the minimum value in the array.
   - `mean`: Calculate the mean of the array.

### 3. **Mathematical Functions**
   - `add`: Element-wise addition of two arrays.
   - `subtract`: Element-wise subtraction of two arrays.
   - `multiply`: Element-wise multiplication of two arrays.
   - `divide`: Element-wise division of two arrays.
   - `neg`: Negate all elements in an array.
   - `sqrt_array`: Compute the square root of each element in an array.
   - `exp_array`: Compute the exponential (e^x) of each element in an array.
   - `power`: Raise each element in the array to the given power.

### 4. **Trigonometric Functions**
   - `sin`: Compute the sine of each element in an array.
   - `cos`: Compute the cosine of each element in an array.
   - `tan`: Compute the tangent of each element in an array.

### 5. **Linear Algebra Functions**
   - `matrix_multiply`: Perform matrix multiplication.
   - `strassen_multiply`: Perform matrix multiplication using the Strassen algorithm.
   - `transpose`: Transpose a 2D matrix.

### 6. **Array Reshaping Functions**
   - `reshape`: Change the shape of an array while maintaining the number of elements.
   - `free_NeuArray`: Free memory allocated to the array.

## How to Use

### Prerequisites

- GCC (or any other C compiler)
- Standard C Libraries (`stdlib.h`, `stdio.h`, etc.)

### Compilation

To compile the project, run the following command:

```bash
gcc -o neuarray main.c -lm
```

Here, `main.c` is the source file where you will be using the NeuArray library. The `-lm` flag links the math library for functions like `pow`, `sqrt`, etc.

### Using NeuArray in Your Project

1. **Include the necessary headers**:

```c
#include "neuarray.h"
```

2. **Create arrays and perform operations**:

```c
int shape[] = {3, 3};
NeuArray* arr1 = ones(shape, 2);
NeuArray* arr2 = randint(1, 10, shape, 2);

// Add the arrays
NeuArray* sum = add(arr1, arr2);

// Print the result
print_NeuArray(sum);

// Free memory
free_NeuArray(arr1);
free_NeuArray(arr2);
free_NeuArray(sum);
```

### Example Code

```c
#include <stdio.h>
#include "neuarray.h"

int main() {
    int shape[] = {2, 2};

    // Create two arrays with random integers
    NeuArray* A = randint(0, 10, shape, 2);
    NeuArray* B = randint(0, 10, shape, 2);

    // Perform matrix multiplication
    NeuArray* C = matrix_multiply(A, B);

    // Print the arrays and result
    printf("Matrix A:\n");
    print_NeuArray(A);

    printf("Matrix B:\n");
    print_NeuArray(B);

    printf("Matrix A * B:\n");
    print_NeuArray(C);

    // Free allocated memory
    free_NeuArray(A);
    free_NeuArray(B);
    free_NeuArray(C);

    return 0;
}
```


