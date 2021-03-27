/*
 * @@name:	SIMD.4c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
void work(float *b, int n, int m) {
  int i;
#pragma omp simd safelen(16)
  for (i = m; i < n; i++)
    b[i] = b[i - m] - 1.0f;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern void init_one(float *, int);
extern void output(float *, int);

int main(int argc, char *argv[]) {
  int length = 0;
  int stride = 0; 
  float *b;

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <length> <stride(< 16)>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  stride = atoi(argv[2]);
  
  assert(stride < 16);  
  
  b = malloc(sizeof(float) * length);
  
  init_one(b, length);
  work(b, length, stride);
  output(b, length);

  free(b);
  return EXIT_SUCCESS;
}
