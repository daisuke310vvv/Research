#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc,char *argv[]){

	int myrank;
	int nodenum;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nodenum);

	printf("my node rank: %d. size of node: %d\n",myrank,nodenum);

	MPI_Finalize();



	return EXIT_SUCCESS;
}
