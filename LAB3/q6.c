#include"mpi.h"
#include<stdio.h>
#include<string.h>
#define mcw MPI_COMM_WORLD

int main(int argc,char *argv[])
{
	int rank,size,N,M,i,j,l,counto,counte,odd[5],even[5];
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
	counto=0;
	counte=0;
	for(i=0;i<l;i++)
	{
	  if(C[i]%2==0)
	  {
	  	C[i]=1;
	  	counte++;
	  }
	  else
	  {
	  	C[i]=0;
	  	counto++;
	  }
	}
	fflush(stdout);
	MPI_Gather(C,l,MPI_INT,B,l,MPI_INT,0,mcw);
	MPI_Gather(&counto,1,MPI_INT,odd,1,MPI_INT,0,mcw);
	MPI_Gather(&counte,1,MPI_INT,even,1,MPI_INT,0,mcw);
	if(rank==0)
	{
		int toteven=0,totodd=0;
		fprintf(stdout, "The gathered result in the root :\n");
		for(int i=0;i<N;i++)
		{
			toteven+=even[i];
			totodd+=odd[i];
		}
		for(int i=0;i<M;i++)
			printf("%d\t",B[i]);
		fprintf(stdout, "Total odd :%d\n",totodd);
		fprintf(stdout, "Total even :%d\n",toteven);
		fflush(stdout);
		
	}
	MPI_Finalize();
	return(0);
}