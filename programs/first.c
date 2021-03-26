#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1024

int A[N][N], B[N][N], C[N][N];

void check() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (C[i][j] != (A[i][j] * B[i][j])) {
        printf("[ERROR] %d %d\n", i, j);
        break;
      }
    }
  }
}

int main() {
  srand(3);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = rand() % 1024 + 1;
      B[i][j] = rand() % 1024 + 1;
    }
  }

#pragma omp target data map(to : A, B) map(from : C)
  {
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++)
        C[i][j] = A[i][j] * B[i][j];
    }
  }

  printf("%d %d %d \n", A[0][0], B[0][0], C[0][0]);
  check();
}
