/*
 * @@name:	teams.1c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
#include <omp.h>
#include <stdlib.h>

extern void init(float *, float*, int);

float dotprod(float B[], float C[], int N) {
  float sum0 = 0.0;
  float sum1 = 0.0;
#pragma omp target map(to : B[:N], C[:N]) map(tofrom : sum0, sum1)
#pragma omp teams num_teams(2)
  {
    int i;
    if (omp_get_num_teams() != 2)
      abort();
    if (omp_get_team_num() == 0) {
#pragma omp parallel for reduction(+ : sum0)
      for (i = 0; i < N / 2; i++)
        sum0 += B[i] * C[i];
    } else if (omp_get_team_num() == 1) {
#pragma omp parallel for reduction(+ : sum1)
      for (i = N / 2; i < N; i++)
        sum1 += B[i] * C[i];
    }
  }
  return sum0 + sum1;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int length = 0;
  float *result, *first, *second;

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s <length>", argv[0]);
    return EXIT_FAILURE;
  }

  length = atoi(argv[1]);
  first = malloc(sizeof(float) * length);
  second = malloc(sizeof(float) * length);

  init(first, second, length);
  printf("Dot Product: %f\n", dotprod(first, second, length));

  free(first);
  free(second);
  return EXIT_SUCCESS;
}

/* Note:  The variables sum0,sum1 are now mapped with tofrom, for correct
   execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
