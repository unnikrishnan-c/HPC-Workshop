/*
 * @@name:	array_sections.1c
 * @@type:	C
 * @@compilable:	no
 * @@linkable:	no
 * @@expect:	failure
 * @@version:	omp_4.0
 */
 
extern void i_output(int *Array, int Length);

void foo() {
  int A[30] = {0};
#pragma omp target data map(A [0:4])
  {
/* Cannot map distinct parts of the same array */
#pragma omp target map(A [7:20])
    { A[2] = 0; }
  }
  
  i_output(A, 30);
}

int main(void) {
  foo();
  return 0;
}
