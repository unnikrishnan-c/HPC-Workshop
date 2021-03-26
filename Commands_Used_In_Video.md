# Commands used in Video

Change the runtime to GPU using GUI interface Edit tab. Then

1) 
```C
%%writefile numdevices.c

#include <stdio.h>
#include <omp.h>

int main() {
    int Numdevices = omp_get_num_devices();
    printf("number of devices= %d", Numdevices);
}
```
2) 
```sh
 !yes | add-apt-repository ppa:ubuntu-toolchain-r/test 
```

3) 
```sh
!apt install gcc-10 g++-10 gcc-10-offload-nvptx libgomp1
```

4) 
```sh
 !whereis gcc-10
```

5) 
```sh
!ln -sfnv /usr/local/cuda-10.0 /usr/local/cuda
```

6)
```sh
!g++-10 -fno-lto -fopenmp -foffload=nvptx-none -fstack-protector numdevices.c
```

7) 
```console
!./a.out
Output: number of devices= 1
```

8) 
```C
%%writefile first.c

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1024

int A[N][N], B[N][N], C[N][N];

void check() {

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (C[i][j] != (A[i][j] * B[i][j])) {
        printf("[ERROR] %d %d\n", i, j);
        break;
      }
    }
  }
}

int main() {
  srand(3);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = rand() % 1024 + 1;
      B[i][j] = rand() % 1024 + 1;
    }
  }

#pragma omp target data map(to : A, B) map(from : C)
  {
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++)
        C[i][j] = A[i][j] * B[i][j];
    }
  }

  printf("%d %d %d \n", A[0][0], B[0][0], C[0][0]);
  check();
}

```
9) 
```sh
!g++-10 -fno-lto -fopenmp -foffload=nvptx-none -fstack-protector first.c -o first
```
10) 
```console
! ./first
Output: 571 210 119910 
```

11) 
```console
!nvprof ./first
Output: lenghty output with profiling information. first three lines
==1797== NVPROF is profiling process 1797, command: ./a.out
571 210 119910 
==1797== Profiling application: ./a.out
```
