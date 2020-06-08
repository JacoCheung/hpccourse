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
	abc x[10];
	MPI_Aint sizeabc, extnewtp;
	int i;
	
#define chkstruct

	// 初始化环境
	mybegin(&argc, &argv, &comm, &np, &iam);

#ifdef chkstruct
	mpistruct(&newtp);
	MPI_Type_commit(&newtp);
	if (iam == 0)
	{
		for (m = 0; m < 10; ++ m)
		{
			x[m].a = m;
			
			x[m].b[0] = 20 * (m + 1);
			x[m].b[1] = 30 * (m + 1);
			
			x[m].c[0] = 'a' + 3 * m;
			x[m].c[1] = 'b' + 3 * m;
			x[m].c[2] = 'C' + 3 * m;
		}
		MPI_Send(x, 3, newtp, 1, 5, comm);
			
	//查看所定义类型的信息
		sizeabc = sizeof(abc);
		MPI_Type_extent(newtp, &extnewtp);
		printf("\n iam = %d, sizeof = %ld, and extent = %ld\n", iam, sizeabc, extnewtp);
	}
		
	if (iam == 1)
	{
		// MPI_Recv(matr, 1, newtp, 2, 5, comm, &st);
		// printf("\n Date on Proc %d  are %d, %d, %d, %d, %d, %d\n",\
		iam, matr[0][0], matr[0][1], matr[0][2], matr[1][0], matr[1][1], matr[1][2]);
		
		MPI_Recv(x, 3, newtp, 0, 5, comm, &st);

		printf("\n values are %d, %f, %f, %c, %c, %c\n",\
		x[0].a, x[0].b[0], x[0].b[1], x[0].c[0], x[0].c[1], x[0].c[2]);

		printf("\n values are %d, %f, %f, %c, %c, %c\n",\
		x[1].a, x[1].b[0], x[1].b[1], x[1].c[0], x[1].c[1], x[1].c[2]);

		// printf("\n Date on Proc %d  are %d, %d, %d, %d, %d\n",\
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
