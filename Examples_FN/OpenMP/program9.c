#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void readValues(int arr[8][8]) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      arr[i][j] = i + j;
}

void printValues(int arr[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++)
      printf("%10d   ", arr[i][j]);
    printf("\n");
  }
}

void main(int argc, char *argv[]) {
  int arr1[8][8], arr2[8][8], arr3[8][8];
  
  readValues(arr1); // read first matrix
  readValues(arr2); // read second matrix
  
#pragma omp parallel for num_threads(3)
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      arr3[i][j] = arr1[i][j] + arr2[i][j];
      
  printValues(arr3);
}
