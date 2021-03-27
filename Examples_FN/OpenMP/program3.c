#include <omp.h>
#include <stdio.h> //program 3
int main() {
  int k;
#pragma omp parallel private(k)
  {
    for (k = 0; k < 10; k++)
      printf("Itr: %d tid=%d\n", k, omp_get_thread_num());
  }
  return 0;
}
