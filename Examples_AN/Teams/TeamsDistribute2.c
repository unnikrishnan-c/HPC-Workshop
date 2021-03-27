/*
 * @@name:	teams.3c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.5
 */
float dotprod(float B[], float C[], int N) {
  float sum = 0;
  int i;
#pragma omp target teams map(to: B[0:N], C[0:N]) \
                            defaultmap(tofrom:scalar) reduction(+:sum)
#pragma omp distribute parallel for reduction(+ : sum)
  for (i = 0; i < N; i++)
    sum += B[i] * C[i];
  return sum;
}

#include <stdio.h>
#include <stdlib.h>

extern void init(float *, float *, int);

int main(int argc, char *argv[]) {
  int length = 0;
  float *result, *first, *second;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  first = malloc(sizeof(float) * length);
  second = malloc(sizeof(float) * length);

  init(first, second, length);
  printf("Dot Product: %f\n", dotprod(first, second, length));

  free(first);
  free(second);
  return EXIT_SUCCESS;
}

/* Note:  The variable sum is now mapped with tofrom from the defaultmap
   clause on the combined target teams construct, for correct
   execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
