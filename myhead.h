#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"

typedef struct 
{
	int a;
	float b[2];
	char c[3];
} abc;

void mybegin(int *, char***, MPI_Comm*, int*, int*);
void myend();

void ring(int, int *, MPI_Comm, int, int);

void datatype(char, MPI_Datatype *);

void mpistruct(MPI_Datatype *);