/*
 * @@name:	target_data.3c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */

#include <math.h>
#define COLS 100

void gramSchmidt(float Q[][COLS], const int rows) {
  int cols = COLS;
#pragma omp target data map(Q [0:rows] [0:cols])
  for (int k = 0; k < cols; k++) {
    double tmp = 0.0;

#pragma omp target map(tofrom : tmp)
#pragma omp parallel for reduction(+ : tmp)
    for (int i = 0; i < rows; i++)
      tmp += (Q[i][k] * Q[i][k]);

    tmp = 1 / sqrt(tmp);

#pragma omp target
#pragma omp parallel for
    for (int i = 0; i < rows; i++)
      Q[i][k] *= tmp;
  }
}

#include <stdio.h>
#include <stdlib.h>

extern void init_one(float *, int);

int main(int argc, char *argv[]) {
  int rows = 0;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <rows>", argv[0]);
    return EXIT_FAILURE;
  }

  rows = atoi(argv[1]);
  
  float (*array)[COLS] = malloc(sizeof(float (*)[COLS]) * rows);
  
  for (int i = 0; i < rows; ++i)
    init_one(array[i], COLS);

  gramSchmidt(array, rows);

  free(array);
  return EXIT_SUCCESS;
}

/* Note:  The variable tmp is now mapped with tofrom, for correct
   execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
