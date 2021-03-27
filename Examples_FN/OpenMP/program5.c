#include <omp.h>
#include <stdio.h> //Program 5

int main() {
  int k;
#pragma omp parallel
  {
#pragma omp single
    for (k = 0; k < 10; k++)
      printf("itr=%d  thread-id %d\n", k, omp_get_thread_num());
  }
  return 0;
}
