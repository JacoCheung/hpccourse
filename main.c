#include "myhead.h"

void main(argc, argv)
int argc;
char **argv;
{
	MPI_Comm comm;
	int np, iam;
	// 初始化环境
	mybegin(&argc, &argv, &comm, &np, &iam);

	// 函数功能实现
	printf("Thread : %d of %d \n", np, iam);


	// 结束程序
	myend();

	return;
}