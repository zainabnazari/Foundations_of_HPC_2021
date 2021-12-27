#include <stdio.h>
#include<stdlib.h>
#include <mpi.h>
// int main (int argc, char * argv[]) {
//   int rank, size;
//   double r;
//   MPI_Init( &argc, &argv );
//   MPI_Comm_rank( MPI_COMM_WORLD,&rank);
//   MPI_Comm_size( MPI_COMM_WORLD,&size );
r = ((double) rand() / (RAND_MAX));
std::cout << r << std::endl;


  MPI_Finalize();
}


//double*** addthree_dim_matrices(double *** x, double *** y)
void initialise_matrix3d(){


int rows=r1, columns=r2, aisles=r3;
int*** matrix3d = new int*[rows];
for (int i=0; i<rows; ++i){
  matrix3d[i]=new int*[columns];
  for (int j=0; j < columns; j++){
    matrix3d[i][j] = new int[aisles];
     for (int k=0; k< aisles; k++){

     }
  }
}
}
