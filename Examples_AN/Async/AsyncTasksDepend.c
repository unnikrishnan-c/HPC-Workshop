/*
 * @@name:	async_target.2c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#include <omp.h>
#include <stdlib.h>

#pragma omp declare target
extern void init(float *, float *, int);
#pragma omp end declare target

extern void foo();

extern void output(float *, int);

void vec_mult(float *p, int N, int dev) {
  float *v1, *v2;
  int i;
  
#pragma omp task shared(v1, v2) depend(out : v1, v2)
#pragma omp target device(dev) map(v1, v2)
  {
    // check whether on device dev
    if (omp_is_initial_device())
      abort();
    v1 = (float *)malloc(N * sizeof(float));
    v2 = (float *)malloc(N * sizeof(float));
    init(v1, v2, N);
  }
  foo(); // execute other work asychronously
#pragma omp task shared(v1, v2, p) depend(in : v1, v2)
#pragma omp target device(dev) map(to : v1, v2) map(from : p [0:N])
  {
    // check whether on device dev
    if (omp_is_initial_device())
      abort();
#pragma omp parallel for
    for (i = 0; i < N; i++)
      p[i] = v1[i] * v2[i];
    free(v1);
    free(v2);
  }
#pragma omp taskwait
  output(p, N);
}

#include <stdio.h>
#include <stdlib.h>

void foo() {
  printf("execute other work asychronously\n");
}

int main(int argc, char *argv[]) {
  int length = 0;
  int devno  = 0;
  float *array;

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <length> <device number>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  devno  = atoi(argv[2]);
  
  array = malloc(sizeof(float) * length);
  vec_mult(array, length, devno);

  free(array);
  return EXIT_SUCCESS;
}

