#ifndef PGM_IO_H
#define PGM_IO_H

// Read a P2 format PGM image and convert it as a matrix
double **read_pgm(const char *filename, int *m, int *n, int *maxval);

// convert a matrix to a P2 format PGM image
void write_pgm(const char *filename, double **A, int m, int n, int maxval);

#endif
