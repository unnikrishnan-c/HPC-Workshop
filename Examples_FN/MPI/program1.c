#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int total_processes, rank, size = 1024;
  char hname[1024];

  MPI_Init(&argc, &argv); // initialize MPI execution environment

  MPI_Comm_size(MPI_COMM_WORLD, &total_processes); // get total processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);            // get rank of the process
  MPI_Get_processor_name(hname, &size);            // get hostname
  
  printf("Number of tasks=%d My rank=%d hostname= %s\n", total_processes, rank,
         hname); // print details

  MPI_Finalize(); // terminate MPI execution environment
}
