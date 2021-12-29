#include <iostream>
#include "mpi.h"
#include<cstdlib> 
int main (int argc, char * argv[]) {
  int rank, size;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD,&rank);
  MPI_Comm_size( MPI_COMM_WORLD,&size );
srand (time(NULL)+rank*1000);
double r = ((double) rand() / (RAND_MAX));
std::cout << r << &r<< std::endl;

MPI_Finalize();
return 0;
}
