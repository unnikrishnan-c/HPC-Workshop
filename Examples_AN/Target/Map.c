/*
 * @@name:	target.2c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
extern void init(float *, float *, int);
extern void output(float *, int);
void vec_mult(int N) {
  int i;
  float p[N], v1[N], v2[N];
  init(v1, v2, N);
#pragma omp target map(v1, v2, p)
#pragma omp parallel for
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];
  output(p, N);
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int length = 0;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  vec_mult(length);

  return EXIT_SUCCESS;
}
