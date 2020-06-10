#include "myhead.h"
#include <stdlib.h>

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
	
// #define chkstruct
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
		MPI_Aint lb;
	//查看所定义类型的信息
		sizeabc = sizeof(abc);
		MPI_Type_get_extent(newtp,&lb,&extnewtp);

		// MPI_Type_extent(newtp, &extnewtp);
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

// #define ckrcmatmul
#ifdef ckrcmatmul
	float A[1][4];
	float B[4][1];
	float C[1][4];
	float W[4][1];
	for(int j = 0 ; j < 4 ; j++)
	{
		A[0][j] = iam - 1;
		B[j][0] = iam + 1;
	}

	printf("A %d row: %f, %f, %f, %f\n",iam,A[0][0],A[0][1],A[0][2],A[0][3]);
	printf("B %d col: %f, %f, %f, %f\n",iam,B[0][0],B[1][0],B[2][0],B[3][0]);

	
	MPI_Barrier(comm);

	printf("C %d row: %f, %f, %f, %f\n",iam,C[0][0],C[0][1],C[0][2],C[0][3]);

#endif

// #define ckgather
#ifdef ckgather 

	int a = iam;
	int b = iam - np;
	int * recvbuf = NULL;
	if(iam == 0){
		recvbuf = (int*)malloc(np * sizeof(int));
	}
	MPI_Gather(&a,1,MPI_INT,recvbuf,1,MPI_INT,0,comm);
	MPI_Barrier(comm);
	if(iam == 0){
		printf("gather all data:\n");
		for(int i = 0 ; i < np ; i++){
			printf("%d ",recvbuf[i]);
		}
		printf("\n");
		// free(recvbuf);
		// recvbuf = NULL;
	}
	MPI_Barrier(comm);

	MPI_Scatter(recvbuf,1,MPI_INT,&b,1,MPI_INT,0,comm);
	printf("iam %d b is %d\n",iam,b);

	int *sendbuf = (int *) malloc(sizeof(int)*(iam + 1));

	int sendcount = iam + 1;
	int *disp = (int * )malloc(sizeof(int) * np);
	int *recvcount = (int * )malloc(sizeof(int) * np);

	disp[0] = 0;
	MPI_Gather(&sendcount,1,MPI_INT,recvcount,1,MPI_INT,0,comm);
	for(int s = 1 ; s < np;s++){
		disp[s] = disp[s - 1] + recvcount[s-1];
	}
	for(int i = 0 ; i < iam + 1; i++){
		sendbuf[i] = iam;
	}
	int recvnum = 0;
	for(int i = 0 ; i < np; i++){
		recvnum += recvcount[i];
	}
	recvbuf = (int *) malloc(sizeof(int)*(recvnum));
	MPI_Gatherv(sendbuf,sendcount,MPI_INT,recvbuf,recvcount,disp,MPI_INT,0,comm);
	if(iam == 0){
		printf("recvcount is\n");
		for(int i = 0 ; i < np; i++){
			printf("%d ",recvcount[i]);
		}
		printf("\n");
		for(int i = 0 ; i < recvnum;i++){
			printf("%d ",recvbuf[i]);
		}
		printf("\n");
	}

#endif

// #define ckalltoall
#ifdef ckalltoall
	int * all_send = (int *) malloc( sizeof (int ) * np * 2);
	int * all_recv = (int *) malloc( sizeof (int ) * np * 2);
	int sendcount = 1;
	
	for(int i = 0 ; i < np * 2; i++)
		all_send[i] = np - iam;
	
	MPI_Alltoall(all_send,1,MPI_2INT,all_recv,1,MPI_2INT,comm);
	printf("in %d: ",iam);
	for(int i = 0 ; i < np * 2; i++ ){

		printf("%d ",all_recv[i]);
	}
	printf("\n");

#endif
//使用FLOAT_INT符合结构求出最大值以及最大值的位置
// #define ckreduce
#ifdef ckreduce
	typedef struct {float val;int loc;} float_int;
	float_int data[2], result[2];
	data[0].val = 1./ (iam + 2) ;
	data[0].loc = iam;

	data[1].val = (iam + 1) * 10;
	data[1].loc = iam;

	MPI_Allreduce(&data,&result,1,MPI_FLOAT_INT,MPI_MAXLOC,comm);
	printf("from rank %d result is (%f,%d) (%f,%d) \n",iam,result[0].val,result[0].loc,result[1].val,result[1].loc);

#endif

#define ckmesh
#ifdef ckmesh
	MPI_Comm rowcomm,colcomm;
	int col,row;
	int p = 2, q = (np + p - 1 )/ p;
	mesh( iam,  np, comm, p, q, &row, &col, & rowcomm, & colcomm );
	printf("proc %d , (%d,%d)\n",iam,row,col);
#endif

	// 函数功能实现
	// m = iam;
	// ring(m, &n, comm, np, iam);
	// printf("Thread : %d of %d , n = %d\n", np, iam, n);

	// 结束程序
	myend();

	return;
}
