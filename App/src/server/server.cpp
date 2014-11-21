#include <stdio.h>

#include "server.h"

int main(int argc,char *argv[]){

	Communication *serverdata = new Communication(argc,argv);

	if(serverdata -> getMyrank() != 0){
		puts("server is not rank 0.");
		return 1;
	}

	hello_world();


	delete (serverdata);
	serverdata = NULL;

	return EXIT_SUCCESS;
}

void hello_world(){

	printf("hello world on server\n");
}
