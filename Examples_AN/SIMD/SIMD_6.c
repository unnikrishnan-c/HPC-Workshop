/*
 * @@name:	SIMD.6c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#pragma omp declare simd linear(p : 1) notinbranch
int foo(int *p) {
  *p = *p + 10;
  return *p;
}

int myaddint(int *a, int *b, int n) {
#pragma omp simd
  for (int i = 0; i < n; i++) {
    a[i] = foo(&b[i]); /* foo is not called under a condition */
  }
  return a[n - 1];
}

#pragma omp declare simd linear(p : 1) inbranch
float goo(float *p) {
  *p = *p + 18.5f;
  return *p;
}

float myaddfloat(float *x, float *y, int n) {
#pragma omp simd
  for (int i = 0; i < n; i++) {
    x[i] = (x[i] > y[i]) ? goo(&y[i]) : y[i];
    /* goo is called under the condition (or within a branch) */
  }
  return x[n - 1];
}

#include <stdio.h>
#include <stdlib.h>

extern void init(float *, float *, int);
extern void i_init(int *, int *, int);

int main(int argc, char *argv[]) {
  int length = 0;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  
  float *first  = malloc(sizeof(float) * length);
  float *second = malloc(sizeof(float) * length);
  
  int *first_i  = malloc(sizeof(int) * length);
  int *second_i = malloc(sizeof(int) * length);
  
  init(first, second, length);
  i_init(first_i, second_i, length);
  
  printf("Add_Float: %f\n", myaddfloat(first, second, length));
  printf("Add_Int: %d\n",   myaddint(first_i, second_i, length));
  
  free(first);
  free(second);
  
  free(first_i);
  free(second_i);

  return EXIT_SUCCESS;
}
