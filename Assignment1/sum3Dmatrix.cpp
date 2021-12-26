#include <iostream>
#include <mpi.h>
int main (int argc, char * argv[]) {
  int rank, size;
  double r;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD,&rank);
  MPI_Comm_size( MPI_COMM_WORLD,&size );
r = ((double) rand() / (RAND_MAX));
std::cout << r << std::endl;
int dim1, dim2, dim3;
int*** a=initialise_matrix3d(dim1, dim2, dim3);
int*** b=initialise_matrix3d(dim1,dim2,dim3);

delete [] delete3dmatrix(a);
delete [] delete3dmatrix(b);

MPI_Finalize();

}

void delete3dmatrix(int*** matrix3d){
for (int i=0; i<rows; ++i){

  for (int j=0; j < columns; j++){

     delete [] matrix3d[i][j];
  }
  delete [] matrix3d[i];
}
delete [] matrix3d;
}
int*** addition3d(int*** a, int*** b){
  int*** matrix3d = new int*[rows];
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
//double*** addthree_dim_matrices(double *** x, double *** y)
int*** initialise_matrix3d(int rows, int columns, int aisles){

int*** matrix3d = new int*[rows];
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
