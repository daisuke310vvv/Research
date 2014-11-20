#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc, char *argv[]){

	MPI_Init(&argc,&argv); //MPI初期化

	printf("Hello world\n");

	MPI_Finalize();	//MPI終了


	return EXIT_SUCCESS;
}
