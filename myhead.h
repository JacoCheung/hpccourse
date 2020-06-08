#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"

void mybegin(int *, char***, MPI_Comm*, int*, int*);
void myend();

void ring(int, int *, MPI_Comm, int, int);