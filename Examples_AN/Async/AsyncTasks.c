/*
 * @@name:	async_target.1c
 * @@type:	C
 * @@compilable:	yes
 * @@linkable:	no
 * @@expect:	success
 * @@version:	omp_4.0
 */


#pragma omp declare target
float F(float);
#pragma omp end declare target

#define N 1000000000
#define CHUNKSZ 1000000

void init(float *, int);
extern void output(float *, int);

float Z[N];

void pipedF() {
  int C, i;
  init(Z, N);
  for (C = 0; C < N; C += CHUNKSZ) {
#pragma omp task shared(Z)
#pragma omp target map(Z [C:CHUNKSZ])
#pragma omp parallel for
    for (i = 0; i < CHUNKSZ; i++)
      Z[i] = F(Z[i]);
  }
#pragma omp taskwait
  output(Z, 100);
}

float F(float X) {
  float value = 0.0f;
  for (int i = 2; i < 200; ++i)
    value += (X / i);
  return value;
}

int main() {
  pipedF();
  return 0;
}
