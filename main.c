#include "myhead.h"

void main(argc, argv)
int argc;
char **argv;
{
	MPI_Comm comm;
	int np, iam;
	int m, n;
	// 初始化环境
	mybegin(&argc, &argv, &comm, &np, &iam);

	// 函数功能实现
	m = iam;
	ring(m, &n, comm, np, iam);
	printf("Thread : %d of %d , n = %d\n", np, iam, n);


	// 结束程序
	myend();

	return;
}