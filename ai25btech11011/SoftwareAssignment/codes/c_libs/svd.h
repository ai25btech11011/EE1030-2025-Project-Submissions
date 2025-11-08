#ifndef SVD_H
#define SVD_H

// power iteration to find the top singular value and vectors
double power_iteration(double **A, double *u, double *v, int m, int n);

// truncated SVD for top k singular values
void truncated_svd(double **A, int m, int n, int k, double **U, double *S, double **V);

// Reconstruct compressed image from U, Σ, V matrices
void reconstruct(double **U, double *S, double **V, double **Ak, int m, int n, int k);

// reconstruction error using Frobenius norm
double frobenius_error(double **A, double **B, int m, int n);

#endif
