/*
 * @@name:	SIMD.5c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
void work(double **a, double **b, double **c, int n) {
  int i, j;
  double tmp;
#pragma omp for simd collapse(2) private(tmp)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tmp = a[i][j] + b[i][j];
      c[i][j] = tmp;
    }
  }
}

#include <stdio.h>
#include <stdlib.h>

extern void d_init(double *, double *, int);
extern void d_output(double *, int);

int main(int argc, char *argv[]) {
  int length = 0;
  double **result, **first, **second;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);

  first  = malloc(sizeof(double *) * length);
  second = malloc(sizeof(double *) * length);
  result = malloc(sizeof(double *) * length);
  
  for (int i = 0; i < length; ++i) {
    first[i]  = malloc(sizeof(double) * length);
    second[i] = malloc(sizeof(double) * length);
    result[i] = malloc(sizeof(double) * length);
    
    d_init(first[i], second[i], length);
  }

  work(first, second, result, length);
  
  printf("[");
  for (int i = 0; i < length; ++i) 
    d_output(result[i], length);
  printf("]");
  
  for (int i = 0; i < length; ++i) {
    free(first[i]);
    free(second[i]);
    free(result[i]);
  }

  free(first);
  free(second);
  free(result);
  return EXIT_SUCCESS;
}

