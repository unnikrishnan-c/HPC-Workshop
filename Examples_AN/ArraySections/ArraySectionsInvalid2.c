/*
 * @@name:	array_sections.2c
 * @@type:	C
 * @@compilable:	no
 * @@linkable:	no
 * @@expect:	failure
 * @@version:	omp_4.0
 */
 
extern void i_output(int *Array, int Length);

void foo() {
  int A[30] = {0}, *p;
#pragma omp target data map(A [0:4])
  {
    p = &A[0];
/* invalid because p[3] and A[3] are the same
 * location on the host but the array section
 * specified via p[...] is not a subset of A[0:4] */
#pragma omp target map(p [3:20])
    {
      A[2] = 0;
      p[8] = 0;
    }
  }
  
  i_output(A, 30);
}

int main(void) {
  foo();
  return 0;
}
