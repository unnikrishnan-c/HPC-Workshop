/*
 * @@name:	array_sections.3c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */
 
extern void i_output(int *Array, int Length);

void foo() {
  int A[30] = {0}, *p;
#pragma omp target data map(A [0:4])
  {
    p = &A[0];
#pragma omp target map(p [7:20])
    {
      A[2] = 0;
      p[8] = 0;
    }
  }
  
  i_output(A, 30);
}

int main() {
  foo();
  return 0;
}
