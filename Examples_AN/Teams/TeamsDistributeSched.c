/*
 * @@name:	teams.4c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#define N 1024 * 1024
float dotprod(float B[], float C[]) {
  float sum = 0.0;
  int i;
#pragma omp target map(to : B [0:N], C [0:N]) map(tofrom : sum)
#pragma omp teams num_teams(8) thread_limit(16) reduction(+ : sum)
#pragma omp distribute parallel for reduction(+:sum) \
                dist_schedule(static, 1024) schedule(static, 64)
  for (i = 0; i < N; i++)
    sum += B[i] * C[i];
  return sum;
}

#include <stdio.h>
#include <stdlib.h>

extern void init(float *, float *, int);

int main(int argc, char *argv[]) {
  float *result, *first, *second;

  first = malloc(sizeof(float) * N);
  second = malloc(sizeof(float) * N);

  init(first, second, N);
  printf("Dot Product: %f\n", dotprod(first, second));

  free(first);
  free(second);

  return EXIT_SUCCESS;
}

/* Note:  The variable sum is now mapped with tofrom, for correct
   execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
