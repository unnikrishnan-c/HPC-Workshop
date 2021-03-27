/*
 * @@name:	target.6c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.5
 */
#define THRESHOLD1 1000000
#define THRESHOLD2 1000

extern void init(float *, float *, int);
extern void output(float *, int);

void vec_mult(float *p, float *v1, float *v2, int N) {
  int i;

  init(v1, v2, N);

#pragma omp target parallel for if (target                                     \
                                    : N > THRESHOLD1) if (parallel             \
                                                          : N > THRESHOLD2)    \
    map(to                                                                     \
        : v1 [0:N], v2[:N]) map(from                                           \
                                : p [0:N])
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];

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
  first  = malloc(sizeof(float) * length);
  second = malloc(sizeof(float) * length);
  result = malloc(sizeof(float) * length);

  vec_mult(result, first, second, length);

  free(first);
  free(second);
  free(result);

  return EXIT_SUCCESS;
}
