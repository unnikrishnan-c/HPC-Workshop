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
```sh
!./a.out
```
```console
Output: number of devices= 1
```

8) 
```C
%%writefile first.c
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define n 1024
int A[n][n], B[n][n], C[n][n];
void check(){
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++) {
        if(C[i][j]!=(A[i][j]*B[i][j])){
            printf("error %d %d",i,j);
            exit(0);
    }

    } 
}
    int main(){
srand(3);
for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
                A[i][j]=rand()%1024+1;
                B[i][j]=rand()%1024+1;
        }
}
#pragma omp target enter data map(to: A, B) 
{
#pragma omp parallel for
for(int i=0; i<n; i++) {
for(int j=0; j<n; j++)
C[i][j] = A[i][j] * B[i][ j];
}

}
#pragma omp target exit data map(from: C) 
printf("%d %d %d \n",A[0][0],B[0][0], C[0][0]);
check();
}

```
9) 
```sh
!g++-10 -fno-lto -fopenmp -foffload=nvptx-none -fstack-protector first.c -o first
```
10) 
```sh
!./first
```
```console
Output: 571 210 119910 
```

11) 
```sh
!nvprof ./first
```
```console
Output: lenghty output with profiling information. first three lines
==1797== NVPROF is profiling process 1797, command: ./a.out
571 210 119910 
==1797== Profiling application: ./a.out
```
