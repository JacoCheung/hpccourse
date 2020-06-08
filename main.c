#include "myhead.h"

void main(argc, argv)
int argc;
char **argv;
{
	MPI_Comm comm;
	int np, iam;
	int m, n, narray[100], marray[101], matr[10][25];
	MPI_Datatype newtp;
	MPI_Status st;
	
#define chkdatatype

	// 初始化环境
	mybegin(&argc, &argv, &comm, &np, &iam);

#ifdef chkdatatype
	for (m = 0; m < 100; ++ m)
	{
		narray[m] = m;
	}
	datatype('i', &newtp);
	
	MPI_Type_commit(&newtp);
	if (iam == 2)
	{
		// for (m = 0; m < 10; ++ m)
		// {
			// for (n = 0; n < 25; ++ n)
			// {
				// matr[m][n] = m + n;
			// }
		// }
		// MPI_Send(matr, 1, newtp, 1, 5, comm);
		MPI_Send(narray, 1, newtp, 1, 5, comm);
	}
	if (iam == 1)
	{
		// MPI_Recv(matr, 1, newtp, 2, 5, comm, &st);
		// printf("\n Date on Proc %d  are %d, %d, %d, %d, %d, %d\n",\
		iam, matr[0][0], matr[0][1], matr[0][2], matr[1][0], matr[1][1], matr[1][2]);
		
		MPI_Recv(marray, 1, newtp, 2, 5, comm, &st);
		printf("\n Date on Proc %d  are %d, %d, %d, %d, %d\n",\
		iam, marray[0], marray[1], marray[2], marray[5], marray[6]);		
	}
	// printf("\nData type is created\n");
	MPI_Type_free(&newtp);
#endif


	// 函数功能实现
	// m = iam;
	// ring(m, &n, comm, np, iam);
	// printf("Thread : %d of %d , n = %d\n", np, iam, n);

	// 结束程序
	myend();

	return;
}
