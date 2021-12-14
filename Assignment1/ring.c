#include <stdio.h>
#include<stdlib.h>
#include <mpi.h>
int main (int argc, char * argv[]) {
int rank, size;
int recv_x;
int recv_y;
MPI_Init( &argc, &argv );
MPI_Comm_rank( MPI_COMM_WORLD,&rank);
MPI_Comm_size( MPI_COMM_WORLD,&size );
int negative_rank=-rank;
MPI_Send(&negative_rank,1,MPI_INTEGER,((rank+1) % size),rank * 10,MPI_COMM_WORLD);
MPI_Send(&rank,1,MPI_INTEGER,(rank+size-1) % size,rank * 10,MPI_COMM_WORLD);
MPI_Status status;
MPI_Recv(&recv_x,1,MPI_INTEGER,((rank+1) % size),((rank+1) % size) * 10,MPI_COMM_WORLD,&status);
MPI_Recv(&recv_y,1,MPI_INTEGER,((rank+size-1) % size),((rank+size-1) % size) * 10,MPI_COMM_WORLD,&status);
printf("My rank is %d and my size is %d and I receive a message from right which is %d \n",rank, size, recv_x);
printf("My rank is %d and my size is %d and I receive a message from left which is  %d \n",rank, size, recv_y);
MPI_Finalize();
}
