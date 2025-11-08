#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_ops.h"
#include "svd.h"

#define MAX_ITER 1000
#define EPSILON 1e-8

// Power Iteration Method to find top singular values
double power_iteration(double **A, double *u, double *v, int m, int n) {
    double *Av = malloc(m * sizeof(double));
    double *ATu = malloc(n * sizeof(double));

    // Taking some random vector v
    for (int i = 0; i < n; i++)
        v[i] = (double)rand() / RAND_MAX;

    double sigma_old = 0;

    // Repeat until final and initial v are converge
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // u = A * v
        for (int i = 0; i < m; i++) {
            Av[i] = 0;
            for (int j = 0; j < n; j++)
                Av[i] += A[i][j] * v[j];
        }
        double nu = norm(Av, m);
        for (int i = 0; i < m; i++) u[i] = Av[i] / nu;

        // v = A^T * u
        for (int j = 0; j < n; j++) {
            ATu[j] = 0;
            for (int i = 0; i < m; i++)
                ATu[j] += A[i][j] * u[i];
        }
        double nv = norm(ATu, n);
        for (int j = 0; j < n; j++) v[j] = ATu[j] / nv;

        double sigma = nv;
        if (fabs(sigma - sigma_old) < EPSILON) break;
        sigma_old = sigma;
    }

    free(Av);
    free(ATu);
    return sigma_old;
}

// Find top k singular values
void truncated_svd(double **A, int m, int n, int k, double **U, double *S, double **V) {
    double **A_copy = alloc_matrix(m, n);

    // Copying original matrix
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            A_copy[i][j] = A[i][j];

    double *u = malloc(m * sizeof(double));
    double *v = malloc(n * sizeof(double));

    for (int t = 0; t < k; t++) {
        // Find next top singular value
        double sigma = power_iteration(A_copy, u, v, m, n);
        S[t] = sigma;

        for (int i = 0; i < m; i++) U[i][t] = u[i];
        for (int j = 0; j < n; j++) V[j][t] = v[j];

        // Deflation step: removing computed component from A to find next top singular values
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                A_copy[i][j] -= sigma * u[i] * v[j];
    }

    free(u);
    free(v);
    free_matrix(A_copy, m);
}

// A_k matrix from U, S, V components
void reconstruct(double **U, double *S, double **V, double **Ak, int m, int n, int k) {
    double **VT = alloc_matrix(k, n);

    // Compute ΣV^T
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            VT[i][j] = V[j][i] * S[i];

    // U * ΣV^T = reconstructed matrix
    matmul(U, VT, Ak, m, k, n);
    free_matrix(VT, k);
}

// Finding reconstruction error between A and A_k
double frobenius_error(double **A, double **B, int m, int n) {
    double err = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            err += (A[i][j] - B[i][j]) * (A[i][j] - B[i][j]);
    return sqrt(err);
}
