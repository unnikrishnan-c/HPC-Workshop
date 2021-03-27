/*
 * @@name:	target_data.6c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#define THRESHOLD 1000000
extern void init(float *, float *, int);
extern void init_again(float *, float *, int);
extern void output(float *, int);

void vec_mult(float *p, float *v1, float *v2, int N) {
  int i;
  init(v1, v2, N);
#pragma omp target data if (N > THRESHOLD) map(from : p [0:N])
  {
#pragma omp target if (N > THRESHOLD) map(to : v1[:N], v2[:N])
#pragma omp parallel for
    for (i = 0; i < N; i++)
      p[i] = v1[i] * v2[i];
    init_again(v1, v2, N);
#pragma omp target if (N > THRESHOLD) map(to : v1[:N], v2[:N])
#pragma omp parallel for
    for (i = 0; i < N; i++)
      p[i] = p[i] + (v1[i] * v2[i]);
  }
  output(p, N);
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int length = 0;

  float *first, *second, *result;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  first = malloc(sizeof(float) * length);
  second = malloc(sizeof(float) * length);
  result = malloc(sizeof(float) * length);

  vec_mult(result, first, second, length);

  free(first);
  free(second);
  free(result);

  return EXIT_SUCCESS;
}