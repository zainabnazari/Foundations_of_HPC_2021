#include <stdio.h>
#include<stdlib.h>
#include <mpi.h>
int main (int argc, char * argv[]) {
int rank, size;
int count=0;
int recv_x;
int recv_y;
double t1, t2, t3;
MPI_Init( &argc, &argv );
MPI_Comm_rank( MPI_COMM_WORLD,&rank);
MPI_Comm_size( MPI_COMM_WORLD,&size );
int negative_rank=-rank;
if (rank==0)
{
t1 = MPI_Wtime();
};
MPI_Send(&negative_rank,1,MPI_INTEGER,((rank+1) % size),rank * 10,MPI_COMM_WORLD);
MPI_Send(&rank,1,MPI_INTEGER,(rank+size-1) % size,rank * 10,MPI_COMM_WORLD);
MPI_Status status;


MPI_Recv(&recv_x,1,MPI_INTEGER,((rank+1) % size),((rank+1) % size) * 10,MPI_COMM_WORLD,&status);
count++;
int tag_from_right=status.MPI_TAG;
MPI_Recv(&recv_y,1,MPI_INTEGER,((rank+size-1) % size),((rank+size-1) % size) * 10,MPI_COMM_WORLD,&status);
count++;
int tag_from_left=status.MPI_TAG;


while (!(tag_from_right==rank * 10 && tag_from_left==rank * 10))
{
int recv_s=recv_x-rank;
int recv_a=recv_y+rank;
MPI_Send(&recv_a,1,MPI_INTEGER,((rank+1) % size),tag_from_left,MPI_COMM_WORLD);
MPI_Send(&recv_s,1,MPI_INTEGER,(rank+size-1) % size,tag_from_right,MPI_COMM_WORLD);
MPI_Recv(&recv_x,1,MPI_INTEGER,((rank+1) % size),MPI_ANY_TAG,MPI_COMM_WORLD,&status);
count++;
tag_from_right=status.MPI_TAG;
MPI_Recv(&recv_y,1,MPI_INTEGER,((rank+size-1) % size),MPI_ANY_TAG,MPI_COMM_WORLD,&status);
count++;
tag_from_left=status.MPI_TAG;
};
printf("I am process %d and I have received %d messages. My final messages have tag %d and value %d,%d \n",rank, count, tag_from_left, recv_x, recv_y);
//printf( "Elapsed time is %f\n", t2 - t1 );
if (rank==0)
{
t2 = MPI_Wtime();
t3 = t2 - t1;
printf("The elapsed time for %d processor with rank 0 is t= %d \n", size, t3); 
}

MPI_Finalize();
}
