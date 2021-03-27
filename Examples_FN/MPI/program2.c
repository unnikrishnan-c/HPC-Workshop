#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int rank, size, number = 0, src = 0;
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  if (rank == 0) {
    number = 100;
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }
  
  if (rank == 1) {
    MPI_Recv(&number, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received integer value %d from process %d \n ", rank,
           number, src);
  }
  
  MPI_Finalize();
}
