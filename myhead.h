#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"

typedef struct 
{
	int a;
	float b[2];
	char c[3];
} abc;

void mesh( int iam,  int np, MPI_Comm comm, int p, int q, int* myrow, int* mycol, \
           MPI_Comm * rowcom, MPI_Comm colcom );

void mybegin(int *, char***, MPI_Comm*, int*, int*);
void myend();

void ring(int, int *, MPI_Comm, int, int);

void datatype(char, MPI_Datatype *);

void mpistruct(MPI_Datatype *);

void init_a(int m, int k, int lda,float a[][lda],int iam);

void init_b(int k, int n,int ldb, float b[][ldb],int iam);

void matmul(int m, int k , int n, int lda, float a[][lda] ,int ldb, float b[][ldb], int ldc, float c[][ldc]);

void rcmatmul(MPI_Comm comm,int np, int iam,int m, int k, int n,int lda,float a[][lda], int ldb,float b[][ldb],int ldc, float c[][ldc],int ldw, float w[][ldw]);