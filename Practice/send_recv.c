#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc,char *argv[]){

	int myrank;
	int nodenum;
	int tag = 0;
	char message[256] = {0};

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nodenum);

	if(myrank ==0){
		int source;	
		MPI_Status recv_status;

		for(source = 1;source<nodenum,source++){
			MPI_Recv(message,256,MPI_CHAR,source,tag,MPI_COMM_WORLD,&recv_status);
			printf("%s",message);
		}
	}else{
		strcat(message, "Helloworld\n");
		MPI_Send(message,strlen(message)+1,MPI_CHAR,0,tag,MPI_COMM_WORLD);
	}

	MPI_Finalize();


	return EXIT_SUCCESS;
}
