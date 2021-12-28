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

int dim1, dim2, dim3;
int in_dim1, in_dim2, in_dim3;

in_dim1 = std::stoi(argv[1]);
in_dim2 = std::stoi(argv[2]);
in_dim3 = std::stoi(argv[3]);
dim1=in_dim1;
dim2=in_dim2;
dim3=in_dim3/size;

int*** big_matrix=initialise_matrix3d(in_dim1, in_dim2, in_dim3);
int*** a=initialise_matrix3d(dim1, dim2, dim3);
int*** b=initialise_matrix3d(dim1,dim2,dim3);
int*** c=addition3d(a, b, dim1, dim2, dim3 );
int size_small_matrix=dim1*dim2*dim3;
MPI_Gather(c,size_small_matrix,MPI_DOUBLE,big_matrix,size_small_matrix,MPI_DOUBLE,0,MPI_COMM_WORLD);
delete3dmatrix(a, dim1, dim2);
delete3dmatrix(b, dim1, dim2);
delete3dmatrix(c, dim1, dim2);
delete3dmatrix(big_matrix, in_dim1, in_dim2);

std::cout << rank << std::endl;

// Displaying the values with proper index.
   for (int i = 0; i <dim1; ++i) {
       for (int j = 0; j < dim2; ++j) {
           for (int k = 0; k < dim3; ++k) {
               std::cout << "c[" << i << "][" << j << "][" << k << "] = " << c[i][j][k] << std::endl;
           }
       }
   }

MPI_Finalize();
return 0;

}
