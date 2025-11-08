#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

// Allocate memory for matrix (m x n)
double **alloc_matrix(int m, int n);

// Free memory allocated for a matrix
void free_matrix(double **mat, int m);

// Compute Euclidean norm of a vector
double norm(double *v, int n);

// Matrix multiplication of A and B: C = A * B  (A: m×p, B: p×n)
void matmul(double **A, double **B, double **C, int m, int p, int n);

#endif
