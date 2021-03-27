/*
 * @@name:	SIMD.3c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
double work(double *a, double *b, int n) {
  int i;
  double tmp, sum;
  sum = 0.0;
#pragma omp simd private(tmp) reduction(+ : sum)
  for (i = 0; i < n; i++) {
    tmp = a[i] + b[i];
    sum += tmp;
  }
  return sum;
}

#include <stdio.h>
#include <stdlib.h>

extern void d_init(double *, double *, int);

int main(int argc, char *argv[]) {
  int length = 0;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  
  double *first  = malloc(sizeof(double) * length);
  double *second = malloc(sizeof(double) * length);
  
  d_init(first, second, length);
  printf("work: %lf\n", work(first, second, length));
  
  free(first);
  free(second);

  return EXIT_SUCCESS;
}
