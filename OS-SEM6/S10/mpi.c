#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

#define MAXSIZE 1000

int main(int argc,char *argv[])
{
	int rank,size;
	int array[MAXSIZE];
	int local_sum = 0;
	int global_sum = 0;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	srand(time(NULL) + rank);
	
	int i;
	for(i=0;i<1000;i++)
	{
		array[i]=rand()%50;
		local_sum+=array[i];
	}
	
	MPI_Reduce(&local_sum,&global_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(rank==0)
		printf("Total Sum : %d",global_sum);
		
	MPI_Finalize();
	return 0;
	
	
}