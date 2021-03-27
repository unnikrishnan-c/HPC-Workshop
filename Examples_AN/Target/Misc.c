#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__attribute__((constructor)) void InitSeed() { srand(getpid()); }

void init(float *FirstArray, float *SecondArray, int Count) {
  for (int i = 0; i < Count; ++i) {
    FirstArray[i]  = (float)(rand() % 100);
    SecondArray[i] = (float)(rand() % 100);
  }
}

void init_again(float *FirstArray, float *SecondArray, int Count) {
  init(FirstArray, SecondArray, Count);
}


void init_one(float *Array, int Count) {
  for (int i = 0; i < Count; ++i)
    Array[i] = (float)(rand() % 100);
}

int maybe_init_again(float *Array, int Count) {
  if ((random() % 100) % 2) {
    init_one(Array, Count);
    return 1;
  }
  return 0;
}

void init_one_int(int *Array, int Count) {
  for (int i = 0; i < Count; ++i)
    Array[i] = (rand() % 100);  
}

void init_vars(float *FirstArray, float *SecondArray, int Count) {
  init(FirstArray, SecondArray, Count);
}

void output(float *Array, int Count) {
/*
  printf("[");
  for (int i = 0; i < Count; ++i)
    printf("%f, ", Array[i]);
  printf("]");
*/
}

void s_init(float *FirstArray, float *SecondArray, int Length) {
  init(FirstArray, SecondArray, Length);
}

void d_init(double *FirstArray, double *SecondArray, int Length) {
  for (int i = 0; i < Length; ++i) {
    FirstArray[i]  = (double)(rand() % 100);
    SecondArray[i] = (double)(rand() % 100);
  }
}

void d_init_one(double *Array, int Count) {
  for (int i = 0; i < Count; ++i)
    Array[i] = (double)(rand() % 100);
}

void i_init(int *FirstArray, int *SecondArray, int Length) {
  for (int i = 0; i < Length; ++i) {
    FirstArray[i]  = (rand() % 100);
    SecondArray[i] = (rand() % 100);
  }
}


void s_output(float *Array, int Length) { output(Array, Length); }

void d_output(double *Array, int Length) {
  printf("[");
  for (int i = 0; i < Length; ++i)
    printf("%lf, ", Array[i]);
  printf("]");
}


