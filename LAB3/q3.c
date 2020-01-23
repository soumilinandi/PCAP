#include"mpi.h"
#include<stdio.h>
#include<string.h>
#define mcw MPI_COMM_WORLD

int main(int argc,char *argv[])
{
	int rank,size,N,M,i,j,l,count;
	char A[30],C[30];
	int B[30];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(mcw,&rank);
	MPI_Comm_size(mcw,&size);

	if(rank==0)
	{
		N=size;
		fprintf(stdout,"Enter an even length string :\n");
		gets(A);
		l=strlen(A)/2;
		printf("%d\n",l);
		fflush(stdout);

	}
	MPI_Bcast(&l,1,MPI_INT,0,mcw);
	MPI_Scatter(A,l,MPI_CHAR,C,l,MPI_CHAR,0,mcw);
	fprintf(stdout, "I have received in process %d \n",rank);
	count=0;
	for(i=0;i<l;i++)
	{
	  if(C[i]=='a' || C[i]=='e' || C[i]=='i' || C[i]=='o' || C[i]=='u' || C[i]=='A' || C[i]=='E' || C[i]=='I' || C[i]=='O' || C[i]=='U')
	  {
	  	 
	  }
	  else
	  {
	  	fprintf(stdout, "%c",C[i]);
	  	 count++;
	  }
	}
	fflush(stdout);
	MPI_Gather(&count,1,MPI_INT,B,1,MPI_INT,0,mcw);
	if(rank==0)
	{
		int sum=0;
		fprintf(stdout, "The gathered result in the root \n");
		fflush(stdout);
		for(i=0;i<N;i++)
		{
			fprintf(stdout, "%d\t",B[i]);
			sum+=B[i];
		}
		fprintf(stdout, "\nThe gathered sum of non vowels in the root is %d \n",sum);
		fflush(stdout);
	}
	MPI_Finalize();
	return(0);
}