#include <omp.h>
#include <stdio.h>

omp_lock_t sema;

int main() {
  omp_init_lock(&sema);
  int sum = 1, threads = 20;
  
  omp_set_num_threads(threads);
  
#pragma omp parallel shared(sum)
  {
    omp_set_lock(&sema);
    sum = sum * 2;
    omp_unset_lock(&sema);
  }
  
  printf("sum=%d\n", sum); /*2^number of threads.*/
  return 0;
}
