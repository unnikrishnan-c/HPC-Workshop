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
