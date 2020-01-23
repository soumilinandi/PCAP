#include"mpi.h"
#include<stdio.h>
#include<string.h>
#define mcw MPI_COMM_WORLD

int main(int argc,char *argv[])
{
	int rank,size,N,M,i,j,l,count;
	int A[30],C[30],B[40];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(mcw,&rank);
	MPI_Comm_size(mcw,&size);

	if(rank==0)
	{
	
		N=size;
		fprintf(stdout,"Enter length of array which is divisible by %d :\n",N);
		scanf("%d",&M);
		fprintf(stdout,"Enter array  elements :\n");
		for(i=0;i<M;i++)
			scanf("%d",&A[i]);
		fflush(stdout);
		l=M/N;
	}
	MPI_Bcast(&l,1,MPI_INT,0,mcw);
	MPI_Scatter(A,l,MPI_INT,C,l,MPI_INT,0,mcw);
	//fprintf(stdout, "I have received in process %d \n",rank);
	for(i=1;i<l;i++)
	{
	  C[i]=C[i]+C[i-1];
	}
	fflush(stdout);
	MPI_Gather(C,l,MPI_INT,B,l,MPI_INT,0,mcw);

	if(rank==0)
	{
		fprintf(stdout, "The gathered result in the root :\n");
		for(int i=0;i<M;i++)
			printf("%d\t",B[i]);
		fflush(stdout);
		
	}
	MPI_Finalize();
	return(0);
}