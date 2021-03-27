/*
 * @@name:	SIMD.1c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
 
extern void d_init(double *, double *, int);
extern void d_init_one(double *, int);
extern void d_output(double *, int);
 
void star(double *a, double *b, double *c, int n, int *ioff) {
  int i;
#pragma omp simd
  for (i = 0; i < n; i++)
    a[i] *= b[i] * c[i + *ioff];
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int length = 0;
  int ioff = 0;
  double *result, *first, *second;

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <length> <ioff>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  ioff   = atoi(argv[2]);
  first  = malloc(sizeof(double) * length);
  second = malloc(sizeof(double) * length);
  result = malloc(sizeof(double) * length);

  d_init(first, second, length);
  d_init_one(result, length);
  star(result, first, second, length, &ioff);
  d_output(result, length);

  free(first);
  free(second);
  free(result);
  return EXIT_SUCCESS;
}
