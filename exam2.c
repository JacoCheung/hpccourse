#include <stdio.h>
#include "mpi.h"

void make_newtype(int m, int n, int lda,MPI_Datatype * newtype){

    MPI_Datatype vec_type;
    const int count = m;
    const int length = m;
    const int stride = lda;
    MPI_Type_vector(count, length, stride, MPI_INT, &vec_type);
    // MPI_Datatype oldtp[2];
	// int blklen[2];
	// MPI_Aint displs[2]; 
    // displs[0] = 1;
    // displs[1] = sizeof(int )*( m * lda + n);

    //MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb,
    //                        MPI_Aint extent, MPI_Datatype *newtype)
    MPI_Type_create_resized(vec_type,0,sizeof(int )*( m * lda + n),newtype);
    // oldtp[0] = vec_type;
	// oldtp[1] = MPI_UB;
    
    // blklen[0] = m;
    // blklen[1] = 1;

	// MPI_Type_create_struct(2, blklen, displs, oldtp, newtype);
}

int main(int args, char ** argv){

    MPI_Init(&args,&argv);
    MPI_Datatype submat;
    const int lda = 100;
    const int  M = 100, N = 100;

    const int m = 5, n = 5;

    make_newtype(m,n,lda,&submat);

    MPI_Finalize();
    return 0;
}