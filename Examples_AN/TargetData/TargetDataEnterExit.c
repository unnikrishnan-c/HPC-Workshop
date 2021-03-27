/*
 * @@name:        target-unstructured-data.1.c
 * @@type:        C
 * @@compilable:  yes
 * @@linkable:    no
 * @@expect:      success
 * @@version:     omp_4.5
 */
#include <stdlib.h>
#include <stdio.h>

void d_output(double *, int);

typedef struct {
  double *A;
  int N;
} Matrix;

void init_matrix(Matrix *mat, int n) {
  mat->A = (double *)malloc(n * sizeof(double));
  mat->N = n;
#pragma omp target enter data map(alloc:mat->A[:n])
}

void free_matrix(Matrix *mat) {
#pragma omp target exit data map(delete:mat->A[:mat->N])
  mat->N = 0;
  free(mat->A);
  mat->A = NULL;
}

int main(int argc, char *argv[]) {
  int length = 0;
  Matrix M;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <rows>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  init_matrix(&M, length); 
  free_matrix(&M);
  
  return EXIT_SUCCESS;
}
