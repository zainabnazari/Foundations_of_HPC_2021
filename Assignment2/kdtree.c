//this code is for kd tree and in this case k=2.
#include <stdio.h>
#include <stdio.h>
#include <mpi.h>

// compile with float or double (using -DDOUBLE_PRECISION)
#ifndef DOUBLE_PRECISION
#define float_t float
#else
#define float_t double
#endif

// hard code dimensionality of data
#define NDIM 2

struct kpoint float_t[NDIM];

struct kdnode
{
int axis;
kdpoint split;
struct kdnode *left, *right;
}

int leaf;
int point;
int number_of_data_points;
int median;

struct knode * build_kdtree(<current data set >, int ndim, int axis)
//axis  is the splitting dimension from the previous call
// (may be -1 for the first call )
int myaxis = (axis+1)%ndim;
struct kdnode *this_node = (struct kdnode *)malloc(sizeof(struct kdnode ));
this_node.axis=myaxis;

...;

this_node.left=build_kdtree(<left_points>,ndim,myaxis);
this_node.right=build_kdtree(<right_points>,ndim,myaxis);

return this_node;


if (p==){

printf("%d", p)


}
struct leftchild{}

struct rightchild{}


}



int main(){



return 0;
}
