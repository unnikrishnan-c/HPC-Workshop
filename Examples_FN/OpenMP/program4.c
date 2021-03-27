#include <omp.h>
#include <stdio.h>
int main() {
  int id;
  printf("Number of processors: %d\n", omp_get_num_procs());
  printf("Number of threads: %d\n", omp_get_max_threads());
  
  id = omp_get_thread_num();
  printf("Hello from process thread (serial code)= %d\n", id);
  
#pragma omp parallel private(id)
  {
    id = omp_get_thread_num();
    printf("Hello from process thread (parallel code)=%d\n", id);
  }
  
  id = omp_get_thread_num();
  printf("Serial code, thread-id= %d \n", );
  return 0;
}
