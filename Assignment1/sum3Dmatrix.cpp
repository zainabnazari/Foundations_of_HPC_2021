//Author: Zainab Nazari
// This code sum 3 dimensional matrices using mpi.

#include <iostream>
#include "mpi.h"

// This function initialise the matrix
int*** initialise_matrix3d(int rows, int columns, int aisles){
  int*** matrix3d = new int**[rows];
  for (int i=0; i<rows; ++i){
    matrix3d[i] = new int*[columns];
    for (int j=0; j < columns; j++){
      matrix3d[i][j] = new int[aisles];
       for (int k=0; k< aisles; k++){
         matrix3d[i][j][k] = ((double) rand() / (RAND_MAX));
       }
    }
  }
  return matrix3d;
}

// this function adds up the matrices.
int*** addition3d(int*** a, int*** b, int rows, int columns, int aisles){
  int*** matrix3d = new int**[rows];
  for (int i=0; i<rows; ++i){
    matrix3d[i] = new int*[columns];
    for (int j=0; j < columns; j++){
      matrix3d[i][j] = new int[aisles];
       for (int k=0; k< aisles; k++){
         matrix3d[i][j][k]=a[i][j][k]+b[i][j][k];
       }
    }
  }
  return matrix3d;
}

//This function delete the matrices to free the memory.
void delete3dmatrix(int*** matrix3d, int rows, int columns){
  for (int i=0; i<rows; ++i){
    for (int j=0; j < columns; j++){
       delete [] matrix3d[i][j];
    }
    delete [] matrix3d[i];
  }
  delete [] matrix3d;
}


int main (int argc, char * argv[]) {
  int rank, size;
  double r;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD,&rank);
  MPI_Comm_size( MPI_COMM_WORLD,&size );
r = ((double) rand() / (RAND_MAX));

//std::cout << r << std::endl;
int dim1, dim2, dim3;

dim1 = std::stoi(argv[1]);
dim2 = std::stoi(argv[2]);
dim3 = std::stoi(argv[3]);

int*** a=initialise_matrix3d(dim1, dim2, dim3);
int*** b=initialise_matrix3d(dim1,dim2,dim3);
int*** c=addition3d(a, b, dim1, dim2, dim3 );
delete3dmatrix(a, dim1, dim2);
delete3dmatrix(b, dim1, dim2);

std::cout << rank << std::endl;
MPI_Finalize();
return 0;

}
