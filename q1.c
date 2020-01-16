#include"mpi.h"
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	char arr[]="Hey There DeliLAh";
	MPI_Status status;
	if(rank==0)
	{
		
		MPI_Ssend(arr,25,MPI_CHAR,1,1,MPI_COMM_WORLD);
		MPI_Recv(arr,25,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);
		fprintf(stdout,"I have received %s from process 1\n",arr);
		fflush(stdout);
	}
	else
	{
		MPI_Recv(arr,25,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		for(int i=0;arr[i]!='\0';i++)
		{
			if(isupper(arr[i]))
				arr[i]=tolower(arr[i]);
			else
				arr[i]=toupper(arr[i]);
		}
		MPI_Ssend(arr,25,MPI_CHAR,0,2,MPI_COMM_WORLD);


	}
	MPI_Finalize();
	return 0;
}