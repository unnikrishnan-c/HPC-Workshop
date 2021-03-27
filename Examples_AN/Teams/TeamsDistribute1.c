/*
 * @@name:	teams.2c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#define min(x, y) (((x) < (y)) ? (x) : (y))

float dotprod(float B[], float C[], int N, int block_size, int num_teams,
              int block_threads) {
  float sum = 0.0;
  int i, i0;
#pragma omp target map(to : B [0:N], C [0:N]) map(tofrom : sum)
#pragma omp teams num_teams(num_teams) thread_limit(block_threads) \
      reduction(+:sum)
#pragma omp distribute
  for (i0 = 0; i0 < N; i0 += block_size)
#pragma omp parallel for reduction(+ : sum)
    for (i = i0; i < min(i0 + block_size, N); i++)
      sum += B[i] * C[i];
  return sum;
}

#include <stdio.h>
#include <stdlib.h>

extern void init(float *, float *, int);

int main(int argc, char *argv[]) {
  int length = 0;
  int block_size, num_teams, block_threads;
  float *result, *first, *second;

  if (argc < 5) {
    fprintf(stderr, "USAGE: %s <N> <block_size> <num_teams> <block_threads>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  block_size = atoi(argv[2]);
  num_teams  = atoi(argv[3]);
  block_threads = atoi(argv[4]);
  
  first = malloc(sizeof(float) * length);
  second = malloc(sizeof(float) * length);

  init(first, second, length);
  printf("Dot Product: %f\n", dotprod(first, second, length, block_size, num_teams, block_threads));

  free(first);
  free(second);
  return EXIT_SUCCESS;
}

/* Note:  The variable sum is now mapped with tofrom, for correct
   execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
