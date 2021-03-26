#include <omp.h>
#include <stdio.h>

int main() {
  int Numdevices = omp_get_num_devices();
  printf("number of devices= %d\n", Numdevices);
}
