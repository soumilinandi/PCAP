#include"mpi.h"
#include<stdio.h>
#define mcw MPI_COMM_WORLD
int main(int argc,char *argv[])
{
	int rank,size,N,A[10],B[10],c,i;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(mcw,&rank);
	MPI_Comm_size(mcw,&size);

	if(rank==0)
	{
		N=size;
		fprintf(stdout,"Enter %d values :\n",N);
		fflush(stdout);
		for(i=0;i<N;i++)
			scanf("%d",&A[i]);
	}
	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,mcw);
	fprintf(stdout, "I have received %d in process %d \n",c,rank);
	fflush(stdout);
	c=c*c;
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,mcw);
	if(rank==0)
	{
		fprintf(stdout, "The gathered result in the root \n");
		fflush(stdout);
		for(i=0;i<N;i++)
			fprintf(stdout, "%d\t",B[i]);
		fflush(stdout);
	}
	MPI_Finalize();
	return(0);
}