#include <stdio.h>
#include <stdlib.h>
#include "matrix_ops.h"
#include "pgm_io.h"
#include "svd.h"

// Main program: compress image using Truncated SVD
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input.pgm> <output.pgm> <k>\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *output_file = argv[2];
    int k = atoi(argv[3]);

    int m, n, maxval;
    double **A = read_pgm(input_file, &m, &n, &maxval);

    // Values allow for k
    if (k <= 0 || k > n) {
        fprintf(stderr, "Invalid k: must be between 1 and %d\n", n);
        return 1;
    }

    // Allocating memory
    double **U = alloc_matrix(m, k);
    double *S = calloc(k, sizeof(double));
    double **V = alloc_matrix(n, k);
    double **Ak = alloc_matrix(m, n);

    printf("Computing top %d singular values...\n", k);

    // Perform truncated SVD and find compressed image
    truncated_svd(A, m, n, k, U, S, V);
    reconstruct(U, S, V, Ak, m, n, k);

    // Save compressed image
    write_pgm(output_file, Ak, m, n, maxval);

    // reconstruction error
    double err = frobenius_error(A, Ak, m, n);
    printf("Reconstruction error (Frobenius norm) = %.4f\n", err);
    printf("Compressed image saved as: %s\n", output_file);

    // Free all allocated memory
    free_matrix(A, m);
    free_matrix(U, m);
    free_matrix(V, n);
    free_matrix(Ak, m);
    free(S);

    return 0;
}
