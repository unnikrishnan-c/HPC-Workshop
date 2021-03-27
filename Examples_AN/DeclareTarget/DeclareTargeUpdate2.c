/*
 * @@name:	declare_target.4c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#define N 10000
#pragma omp declare target
float Q[N][N];
float Pfun(const int i, const int k) { return Q[i][k] * Q[k][i]; }
#pragma omp end declare target

float accum(int k) {
  float tmp = 0.0;
#pragma omp target update to(Q)
#pragma omp target map(tofrom : tmp)
#pragma omp parallel for reduction(+ : tmp)
  for (int i = 0; i < N; i++)
    tmp += Pfun(i, k);
  return tmp;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern void init_one(float *, int);

int main(int argc, char *argv[]) {
  int k = 0;

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <k>", argv[0]);
    return EXIT_FAILURE;
  }

  k = atoi(argv[1]);
  assert(k < N);

  for (int i = 0; i < N; ++ i)
    init_one(Q[i], N);
  
  printf("%f\n", accum(k));

  return EXIT_SUCCESS;
}

/* Note:  The variable tmp is now mapped with tofrom, for correct
   execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
