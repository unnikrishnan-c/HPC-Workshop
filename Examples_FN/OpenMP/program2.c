#include <omp.h>
#include <stdio.h> //program 2

#define tid omp_get_thread_num()
int main() {
  int k;
  
#pragma omp parallel
  {
    for (k = 0; k < 10; k++)
      printf("Itr: %d, tid\n", k, tid);
  }
  
  return 0;
}
