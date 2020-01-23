#include"mpi.h"
#include<stdio.h>
#define mcw MPI_COMM_WORLD

int main(int argc,char *argv[])
{
	int rank,size,N,M,A[100],C[100],i,j,avg=0;
	float c,B[100];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(mcw,&rank);
	MPI_Comm_size(mcw,&size);

	if(rank==0)
	{
		N=size;
		M=4;
		/*fprintf(stdout,"Enter M value :\n");
		scanf("%d",&M);*/
		for(i=0;i<N*M;i++)
		{
			   scanf("%d",&A[i]);
		}
				fflush(stdout);

	}
	MPI_Bcast(&M,1,MPI_INT,0,mcw);
	MPI_Scatter(A,M,MPI_INT,C,M,MPI_INT,0,mcw);
	avg=0;
	for(i=0;i<M;i++)
	{
	  fprintf(stdout, "I have received %d in process %d \n",C[i],rank);
	  avg+=C[i];
	}
	fflush(stdout);
	c=avg/M;;
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,mcw);
	if(rank==0)
	{
		float sum=0;
		fprintf(stdout, "The gathered result in the root \n");
		fflush(stdout);
		for(i=0;i<N;i++)
		{
			fprintf(stdout, "%f\t",B[i]);
			sum+=B[i];
		}
		fprintf(stdout, "\nThe gathered avg in the root is %f \n",sum/N);

		fflush(stdout);
	}
	MPI_Finalize();
	return(0);
}