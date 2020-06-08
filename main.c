#include "myhead.h"

void main(argc, argv)
int argc;
char **argv;
{
	MPI_Comm comm;
	int np, iam;
	int m, n, narray[100], marray[101];
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
	datatype('c', &newtp);
	
	MPI_Type_commit(&newtp);
	if (iam == 2)
	{
		MPI_Send(narray + iam * 5, 3, newtp, 1, 5, comm);
		//这样发送的是10处开始的数据，3个 newtp类型
	}
	if (iam == 1)
	{
		MPI_Recv(marray, 3, newtp, 2, 5, comm, &st);
		printf("\n Date on Proc %d  are %d, %d, %d, %d, %d, %d\n",\
		iam, marray[0], marray[1], marray[2], marray[3], marray[4], marray[5]);
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
