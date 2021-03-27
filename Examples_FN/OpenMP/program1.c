#include <omp.h>
#include <stdio.h>

int main() {
#pragma omp parallel
  { /* { should be on a  newline */
    printf("Hello World!\n");
  }
  
  return 0;
}
