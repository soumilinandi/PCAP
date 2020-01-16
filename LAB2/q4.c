#include"mpi.h"
#include<stdio.h>
int main(int argc, char *argv[])
{
	int rank,size,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter x \n");
		scanf("%d",&x);
		fprintf(stdout,"Sent %d from process 0\n",x);
		MPI_Ssend(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Recv(&x,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&status);	
		fprintf(stdout, "Received %d in process %d\n",x,rank);
		fflush(stdout);
	}
	else if(rank<size-1)
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
		fprintf(stdout, "Received %d in process %d\n",x,rank);
		x=x+1;
		fprintf(stdout,"Sent %d from process %d\n",x,rank);	
		MPI_Ssend(&x,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
		
		fflush(stdout);
	}
	else if(rank==size-1)
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
		fprintf(stdout, "Received %d in process %d\n",x,rank);
		x=x+1;
		MPI_Ssend(&x,1,MPI_INT,0,0,MPI_COMM_WORLD);	
		fprintf(stdout,"Sent %d from process %d\n",x,rank);	
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}

