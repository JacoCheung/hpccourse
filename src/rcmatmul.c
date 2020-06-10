#include "myhead.h"
void init_a(int m, int k, int lda,float a[][lda],int iam){
    int  offset;
    offset = iam * m;

    for(int i = 0 ; i < m; i ++){
        for(int j = 0 ;  j < k ; j++){
            a[i][j] = i + j+ offset;
        }
    }
}

void init_b(int k, int n,int ldb, float b[][ldb],int iam){
    int offset = iam * n;
    for(int i = 0 ; i < k; i ++){
        for(int j = 0 ;  j < n ; j++){
            b[i][j] = 1 - 2 * ( ( i + j + offset) % 2);
        }
    }
}

void matmul(int m, int k , int n, int lda, float a[][lda] ,int ldb, float b[][ldb], int ldc, float *c){
    // printf("matmul param m %d k %d n %d lda %d ldb %d ldc %d",m,k,n,lda,ldb,ldc);
    for(int i = 0 ; i < m; i ++){
        for(int j = 0 ;  j < n ; j++){
            c[i *ldc + j] =0;
            for(int l = 0 ; l < k; l++){
                c[i *ldc + j] += a[i][l] * b[l][j];
            }
        }
    }
}
//m,k,n都是小矩阵的规模，大矩阵的规模是np * m * k,k * n * np
void rcmatmul(MPI_Comm comm,int np, int iam,int m, int k, int n,int lda,float a[][lda], int ldb,float b[][ldb],int ldc, float c[][ldc],int ldw, float w[][ldw]){
    int left, right;
    MPI_Status st;

    MPI_Datatype rectb, rectw;

    MPI_Type_vector(k,n,ldb,MPI_FLOAT,&rectb);
    MPI_Type_vector(k,n,ldw,MPI_FLOAT,&rectw);
    MPI_Type_commit(&rectb);
    MPI_Type_commit(&rectw);
    int l = iam * n;
    left = (np + iam - 1) % np;
    right = (iam+1) % np;

    for(int i = 0 ; i < np - 1; i++){
        if(i % 2 == 0){
            matmul(m,k,n,lda,a,ldb,b,ldc,&c[0][l]);
            MPI_Sendrecv(b,1,rectb,left,1,\
                         w,1,rectw,right,1,comm,&st
                        );
        }
        else {
            matmul(m,k,n,lda,a,ldw,w,ldc,&c[0][l]);
            MPI_Sendrecv(w,1,rectw,left,1,\
                         b,1,rectb,right,1,comm,&st
                        );
        }

        l += n ;
        if(l == np * n) l = 0;
    }

    if( (np - 1) %2 == 0)
        matmul( m,k,n,lda,a,ldb,b,ldc,&c[0][l]);
    else 
        matmul( m,k,n,lda,a,ldw,w,ldc,&c[0][l]);
    
    MPI_Type_free( & rectb);
    MPI_Type_free( & rectw);
}