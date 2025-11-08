#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix_ops.h"
#include "pgm_io.h"

// Read image in P2 PGM format and convert it into a  matrix
double **read_pgm(const char *filename, int *m, int *n, int *maxval) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("PGM file open failed");
        exit(1);
    }

    char magic[3];
    fscanf(fp, "%2s", magic);
    if (strcmp(magic, "P2") != 0) {
        fprintf(stderr, "Only P2 PGM format supported.\n");
        exit(1);
    }

    // Take image dimensions and max pixel value
    fscanf(fp, "%d %d %d", n, m, maxval);
    double **A = alloc_matrix(*m, *n);

    // convert pixel values into matrix
    for (int i = 0; i < *m; i++)
        for (int j = 0; j < *n; j++) {
            int val;
            fscanf(fp, "%d", &val);
            A[i][j] = (double)val;
        }

    fclose(fp);
    return A;
}

// convert matrix data into P2 PGM file format
void write_pgm(const char *filename, double **A, int m, int n, int maxval) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Cannot write PGM");
        exit(1);
    }

    fprintf(fp, "P2\n%d %d\n%d\n", n, m, maxval);

    // limiting values to [0, maxval] and write to file
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int val = (int)fmin(fmax(A[i][j], 0), maxval);
            fprintf(fp, "%d ", val);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}
