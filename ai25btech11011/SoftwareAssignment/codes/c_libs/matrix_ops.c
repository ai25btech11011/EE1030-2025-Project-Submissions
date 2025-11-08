#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_ops.h"

// Allocate memory for an m×n matrix
double **alloc_matrix(int m, int n) {
    double **mat = malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
        mat[i] = calloc(n, sizeof(double));
    return mat;
}

// Free allocated matrix memory
void free_matrix(double **mat, int m) {
    for (int i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
}

// Compute the L2 norm of a vector
double norm(double *v, int n) {
    double s = 0;
    for (int i = 0; i < n; i++)
        s += v[i] * v[i];
    return sqrt(s);
}

// Matrix multiplication of A and B : C = A * B
void matmul(double **A, double **B, double **C, int m, int p, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < p; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}
