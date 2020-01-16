#include"mpi.h"
#include<stdio.h>
int main(int argc, char *argv[])
{
	int rank,size,arr[50],x;
	MPI_Init(&argc,&argv);
	int buf[100];
    int s=100;
	MPI_Buffer_attach(buf,s);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		fprintf(stdout,"Enter %d elements : \n",size-1);
		for(int i=1;i<size;i++)
			scanf("%d",&arr[i]);

        for(int i=1;i<size;i++)
		MPI_Bsend(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
		
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		if(rank%2==0)
		fprintf(stdout, "Rank: %d Number :  %d  Square : %d\n",rank,x,x*x);
	    else
	    	fprintf(stdout, "Rank: %d Number :  %d  Cube : %d\n",rank,x,x*x*x);
		fflush(stdout);
	}
	MPI_Buffer_detach(&buf,&s);
	MPI_Finalize();
	return 0;
}