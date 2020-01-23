#include"mpi.h"
#include<stdio.h>
#include<string.h>
#define mcw MPI_COMM_WORLD

int main(int argc,char *argv[])
{
	int rank,size,N,M,i,j,l,count;
	char A[30],AA[30],C1[30],C2[30],RES[40];
	int k;
	char B[40];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(mcw,&rank);
	MPI_Comm_size(mcw,&size);

	if(rank==0)
	{
	
		N=size;
		fprintf(stdout,"Enter two even length string :\n");
		gets(A);
		gets(AA);
		l=strlen(A)/N;
		printf("%d\n",l);
		fflush(stdout);
	}
	MPI_Bcast(&l,1,MPI_INT,0,mcw);
	MPI_Scatter(A,l,MPI_CHAR,C1,l,MPI_CHAR,0,mcw);
	MPI_Scatter(AA,l,MPI_CHAR,C2,l,MPI_CHAR,0,mcw);
	//fprintf(stdout, "I have received in process %d \n",rank);
	for(i=0;i<l*2;i=i+2)
	{
	  RES[i]=C1[i/2];
	  RES[i+1]=C2[i/2];
	}
	fflush(stdout);
	MPI_Gather(RES,l*2,MPI_CHAR,B,l*2,MPI_CHAR,0,mcw);

	if(rank==0)
	{
		fprintf(stdout, "The gathered result in the root %s\n",B);
		fflush(stdout);
		
	}
	MPI_Finalize();
	return(0);
}