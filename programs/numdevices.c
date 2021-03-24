#include<stdio.h>
#include<omp.h>
int main(){
    int Numdevices=omp_get_num_devices();
    printf("number of devices= %d", Numdevices);
}
