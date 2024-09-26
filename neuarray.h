#include <stdio.h> 
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Structure to represent a NeuArray
typedef struct{
    int* val;   // Pointer to the array data
    int dim;    // Dimension of the array
    int* shape; // Shape of the array (size along each dimension)
    int size;   // Total number of elements in the array
}NeuArray;

// Create a NeuArray based on the provided shape and dimension
NeuArray* create_NeuArray(const int* shape, int dim){
    NeuArray* n1 = (NeuArray*)malloc(sizeof(NeuArray));
    if(n1 == NULL){
        printf("DMA Failed | NeuArray\n");
    }
    n1->shape = (int*)malloc(dim * sizeof(int));
    if(n1->shape == NULL){
        printf("DMA Failed | NeuArray Shape\n");
    }
    n1->dim = dim;
    n1->size = 1;
    for(int i = 0; i < dim; i++){
        n1->shape[i] = shape[i];
        n1->size *= shape[i];
    }
    n1->val = (int*)malloc(n1->size * sizeof(int));
    if(n1->val == NULL){
        printf("DMA Failed | NeuArray Values\n");
    }
    return n1;
}

// Calculate the total number of elements based on shape and dimension
int len(const int* shape, int dim){
    int s = 1;
    for(int i = 0; i < dim; i++){
        s *= shape[i];
    }
    return s;
}

// Print a NeuArray's shape, size, and elements
void print_NeuArray(const NeuArray* n1){
    if(n1 == NULL){
        printf("Empty Array\n");
        return;
    }
    printf("NeuArray |  Shape : (");
    for(int i = 0; i < n1->dim; i++){
        printf("%d", n1->shape[i]);
        if(i < n1->dim - 1){
            printf(", ");
        }
    }
    printf(") |  Size : %d\n\n", n1->size);
    for(int i = 0; i < n1->size; i++){
        printf("%d", n1->val[i]);
        if((i+1) % n1->shape[n1->dim - 1] == 0){
            printf("\n");
        }
        else{
            printf(" ");
        }
    }
}

// Free the memory occupied by a NeuArray
void free_NeuArray(NeuArray* n1){
    if(n1 != NULL){
        free(n1->shape);
        free(n1->val);
        free(n1);
    }
}

// Create a NeuArray initialized with zeros
NeuArray* zeros(const int* shape, int dim){
    NeuArray *n1 = create_NeuArray(shape, dim);
    for (int i = 0; i < n1->size; i++) {
        n1->val[i] = 0;
    }
    return n1;
}

// Create a NeuArray initialized with ones
NeuArray* ones(const int* shape, int dim){
    NeuArray *n1 = create_NeuArray(shape, dim);
    for (int i = 0; i < n1->size; i++) {
        n1->val[i] = 1;
    }
    return n1;
}

// Create an identity matrix (diagonal elements set to 1)
NeuArray* eye(const int* shape, int dim){
    NeuArray *n1 = create_NeuArray(shape, dim);
    int total_size = len(shape, dim);
    int diagonal_step = 1 + shape[dim - 1], diagonal = 0;
    for(int i = 0; i < total_size; i++){
        if(i == diagonal && diagonal < total_size){
            n1->val[i] = 1;
            diagonal += diagonal_step;
        } else {
            n1->val[i] = 0;
        }
    }
    return n1;
}

// Check if two NeuArrays have the same shape
int check_shape(const NeuArray* n1, const NeuArray* n2){
    if(n1->dim != n2->dim || n1->size != n2->size){
        return 0;
    }
    for(int i = 0; i < n1->dim; i++){
        if(n1->shape[i] != n2->shape[i]){
            return 0;
        }
    }
    return 1;
}

// Add two NeuArrays element-wise
NeuArray* add(const NeuArray* n1, const NeuArray* n2){
    if(!check_shape(n1, n2)){
        fprintf(stderr,"Error : Shape Mismatch\n");
        return NULL;
    }
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    if(res == NULL){
        printf("DMA Failed | Result NeuArray doesn't exist\n");
        return NULL;
    }
    for(int i = 0; i < n1->size; i++){
        res->val[i] = n1->val[i] + n2->val[i];
    }
    return res;
}

// Subtract two NeuArrays element-wise
NeuArray* subtract(const NeuArray* n1, const NeuArray* n2){
    if(!check_shape(n1, n2)){
        fprintf(stderr,"Error : Shape Mismatch\n");
        return NULL;
    }
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    if(res == NULL){
        printf("DMA Failed | Result NeuArray doesn't exist\n");
        return NULL;
    }
    for(int i = 0; i < n1->size; i++){
        res->val[i] = n1->val[i] - n2->val[i];
    }
    return res;
}

// Multiply two NeuArrays element-wise
NeuArray* multiply(const NeuArray* n1, const NeuArray* n2){
    if(!check_shape(n1, n2)){
        fprintf(stderr,"Error : Shape Mismatch\n");
        return NULL;
    }
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    if(res == NULL){
        printf("DMA Failed | Result NeuArray doesn't exist\n");
        return NULL;
    }
    for(int i = 0; i < n1->size; i++){
        res->val[i] = n1->val[i] * n2->val[i];
    }
    return res;
}

// Divide two NeuArrays element-wise
NeuArray* divide(const NeuArray* n1, const NeuArray* n2){
    if(!check_shape(n1, n2)){
        fprintf(stderr,"Error : Shape Mismatch\n");
        return NULL;
    }
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    if(res == NULL){
        printf("DMA Failed | Result NeuArray doesn't exist\n");
        return NULL;
    }
    for(int i = 0; i < n1->size; i++){
        if(n2->val[i] == 0){
            fprintf(stderr,"Error : Can't divide by 0\n");
        }
        res->val[i] = n1->val[i] / n2->val[i];
    }
    return res;
}

// Negate the elements of a NeuArray (in-place)
NeuArray* neg(NeuArray* n1){
    for(int i = 0; i < n1->size; i++){
        n1->val[i] = -n1->val[i];
    }
    return n1;
}

// Create a copy of a NeuArray
NeuArray* copy_NeuArray(NeuArray* n1){
    NeuArray* cpy = create_NeuArray(n1->shape, n1->dim);
    if(cpy == NULL){
        printf("DMA Failed | Copy NeuArray doesn't exist\n");
    }
    memcpy(cpy->val, n1->val, n1->size * sizeof(int));
    return cpy;
}

// Compare two NeuArrays for equality
int compare_NeuArray(NeuArray* n1, NeuArray* n2){
    if(n1->dim != n2->dim || n1->size != n2->size){
        return 0;
    }
    for(int i = 0; i < n1->dim; i++){
        if(n1->shape[i] != n2->shape[i]){
            return 0;
        }
    }
    for(int i = 0; i < n1->size; i++){
        if(n1->val[i] != n2->val[i]){
            return 0;
        }
    }
    return 1;
}

// Matrix multiplication using Strassen's algorithm (optimized for square matrices)
NeuArray* strassen_multiply(NeuArray* A, NeuArray* B);

// Standard matrix multiplication (for general cases)
NeuArray* matrix_multiply(NeuArray* A, NeuArray* B) {
    if (A->dim < 2 || B->dim < 2 || A->shape[A->dim - 1] != B->shape[B->dim - 2]) {
        fprintf(stderr, "Error: Dimensions are wrong for matrix multiplication\n");
        return NULL;
    }
    if (A->dim == 2 && B->dim == 2 && A->shape[0] == A->shape[1] && 
        B->shape[0] == B->shape[1] && A->shape[0] == B->shape[0]) {
        return strassen_multiply(A, B);
    }
    int res_dim = A->dim + B->dim - 2;
    int* res_shape = malloc(res_dim * sizeof(int));
    for (int i = 0; i < A->dim - 1; i++) {
        res_shape[i] = A->shape[i];
    }
    for (int i = 0; i < B->dim - 1; i++) {
        res_shape[A->dim - 1 + i] = B->shape[i + 1];
    }
    NeuArray* res = create_NeuArray(res_shape, res_dim);
    free(res_shape);
    int common_dim = A->shape[A->dim - 1];
    int res_size = res->size;
    int A_stride = 1, B_stride = 1, res_stride = 1;
    for (int i = A->dim - 1; i > 0; i--) {
        A_stride *= A->shape[i];
    }
    for (int i = B->dim - 1; i > 1; i--) {
        B_stride *= B->shape[i];
    }
    for (int i = res_dim - 1; i > 0; i--) {
        res_stride *= res->shape[i];
    }
    for (int i = 0; i < res_size; i++) {
        double sum = 0;
        int A_index = (i / res_stride) * A_stride;
        int B_index = (i % res_stride) / B->shape[B->dim - 1];
        for (int k = 0; k < common_dim; k++) {
            sum += A->val[A_index + k] * B->val[B_index + k * B_stride];
        }
        res->val[i] = sum;
    }
    return res;
}

// Helper function for Strassen multiplication algorithm
NeuArray* strassen_multiply(NeuArray* A, NeuArray* B) {
    int n = A->shape[0];
    if (n == 1) {
        NeuArray* C = create_NeuArray(A->shape, A->dim);
        C->val[0] = A->val[0] * B->val[0];
        return C;
    }
    int new_n = n / 2;
    int new_shape[2] = {new_n, new_n};
    NeuArray *A11, *A12, *A21, *A22, *B11, *B12, *B21, *B22;
    A11 = create_NeuArray(new_shape, 2);
    A12 = create_NeuArray(new_shape, 2);
    A21 = create_NeuArray(new_shape, 2);
    A22 = create_NeuArray(new_shape, 2);
    B11 = create_NeuArray(new_shape, 2);
    B12 = create_NeuArray(new_shape, 2);
    B21 = create_NeuArray(new_shape, 2);
    B22 = create_NeuArray(new_shape, 2);
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11->val[i*new_n + j] = A->val[i*n + j];
            A12->val[i*new_n + j] = A->val[i*n + j + new_n];
            A21->val[i*new_n + j] = A->val[(i+new_n)*n + j];
            A22->val[i*new_n + j] = A->val[(i+new_n)*n + j + new_n];
            B11->val[i*new_n + j] = B->val[i*n + j];
            B12->val[i*new_n + j] = B->val[i*n + j + new_n];
            B21->val[i*new_n + j] = B->val[(i+new_n)*n + j];
            B22->val[i*new_n + j] = B->val[(i+new_n)*n + j + new_n];
        }
    }
    NeuArray *M1, *M2, *M3, *M4, *M5, *M6, *M7;
    M1 = matrix_multiply(add(A11, A22), add(B11, B22));
    M2 = matrix_multiply(add(A21, A22), B11);
    M3 = matrix_multiply(A11, subtract(B12, B22));
    M4 = matrix_multiply(A22, subtract(B21, B11));
    M5 = matrix_multiply(add(A11, A12), B22);
    M6 = matrix_multiply(subtract(A21, A11), add(B11, B12));
    M7 = matrix_multiply(subtract(A12, A22), add(B21, B22));
    NeuArray *C11, *C12, *C21, *C22;
    C11 = add(subtract(add(M1, M4), M5), M7);
    C12 = add(M3, M5);
    C21 = add(M2, M4);
    C22 = add(subtract(add(M1, M3), M2), M6);
    NeuArray* C = create_NeuArray(A->shape, A->dim);
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            C->val[i*n + j] = C11->val[i*new_n + j];
            C->val[i*n + j + new_n] = C12->val[i*new_n + j];
            C->val[(i+new_n)*n + j] = C21->val[i*new_n + j];
            C->val[(i+new_n)*n + j + new_n] = C22->val[i*new_n + j];
        }
    }
    free_NeuArray(A11); free_NeuArray(A12); free_NeuArray(A21); free_NeuArray(A22);
    free_NeuArray(B11); free_NeuArray(B12); free_NeuArray(B21); free_NeuArray(B22);
    free_NeuArray(M1); free_NeuArray(M2); free_NeuArray(M3); free_NeuArray(M4);
    free_NeuArray(M5); free_NeuArray(M6); free_NeuArray(M7);
    free_NeuArray(C11); free_NeuArray(C12); free_NeuArray(C21); free_NeuArray(C22);
    return C;
}

// Compute the product of elements in a shape array
int array_product(int* n1, int n) {
    int prod = 1;
    for (int i = 0; i < n; i++) prod *= n1[i];
    return prod;
}

// Generates a NeuArray with random integer values between low and high
NeuArray* randint(int low, int high, int* shape, int dim) {
    NeuArray* res = create_NeuArray(shape, dim);
    for (int i = 0; i < res->size; i++) {
        res->val[i] = low + rand() % (high - low);
    }
    return res;
}

// Reshapes a given NeuArray to the new specified shape and dimension
NeuArray* reshape(NeuArray* n1, int* new_shape, int new_dim) {
    int new_size = array_product(new_shape, new_dim);
    if (new_size != n1->size) {
        fprintf(stderr, "Error: New shape must have the same number of elements.\n");
        return NULL;
    }
    NeuArray* res = create_NeuArray(new_shape, new_dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = n1->val[i];
    }
    return res;
}

// Transposes a 2D NeuArray (swaps rows and columns)
NeuArray* transpose(NeuArray* n1) {
    if (n1->dim != 2) {
        fprintf(stderr, "Error: Transpose is only implemented for 2D array.\n");
        return NULL;
    }
    int new_shape[2] = {n1->shape[1], n1->shape[0]};
    NeuArray* res = create_NeuArray(new_shape, 2);
    for (int i = 0; i < n1->shape[0]; i++) {
        for (int j = 0; j < n1->shape[1]; j++) {
            res->val[j * n1->shape[0] + i] = n1->val[i * n1->shape[1] + j];
        }
    }
    return res;
}

// Applies the square root function to each element in the NeuArray
NeuArray* sqrt_NeuArray(NeuArray* n1) {
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = sqrt(n1->val[i]);
    }
    return res;
}

// Computes the mean (average) of the elements in the NeuArray
double mean(NeuArray* n1) {
    double sum = 0;
    for (int i = 0; i < n1->size; i++) {
        sum += n1->val[i];
    }
    return sum / n1->size;
}

// Finds the maximum value in the NeuArray
int max(NeuArray* n1) {
    int max_val = n1->val[0];
    for (int i = 1; i < n1->size; i++) {
        if (n1->val[i] > max_val) max_val = n1->val[i];
    }
    return max_val;
}

// Finds the minimum value in the NeuArray
int min(NeuArray* n1) {
    int min_val = n1->val[0];
    for (int i = 1; i < n1->size; i++) {
        if (n1->val[i] < min_val) min_val = n1->val[i];
    }
    return min_val;
}

// Applies the exponential function to each element in the NeuArray
NeuArray* exp(NeuArray* n1) {
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = exp(n1->val[i]);
    }
    return res;
}

// Raises each element in the NeuArray to a given power
NeuArray* power(NeuArray* n1, double expn) {
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = pow(n1->val[i], expn);
    }
    return res;
}

// Applies the sine function to each element in the NeuArray
NeuArray* sin(NeuArray* n1) {
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = sin(n1->val[i]);
    }
    return res;
}

// Applies the cosine function to each element in the NeuArray
NeuArray* cos(NeuArray* n1) {
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = cos(n1->val[i]);
    }
    return res;
}

// Applies the tangent function to each element in the NeuArray
NeuArray* tan(NeuArray* n1) {
    NeuArray* res = create_NeuArray(n1->shape, n1->dim);
    for (int i = 0; i < n1->size; i++) {
        res->val[i] = tan(n1->val[i]);
    }
    return res;
}
