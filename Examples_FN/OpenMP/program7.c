#include <omp.h>
#include <stdio.h>

int main() {
  int sum = 1, threads = 20;
  omp_set_num_threads(threads);
  
#pragma omp parallel
  {
#pragma omp atomic update
    sum = sum * 2;
  }
  
  printf("sum=%d\n", sum); /*2^number of threads.*/
  return 0;
}
