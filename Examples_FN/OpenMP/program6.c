#include <omp.h>
#include <stdio.h> //Program 6

int main() {
#pragma omp parallel
  {
#pragma omp master
    printf("master thread-id: %d\n", omp_get_thread_num());
  }
  return 0;
}
