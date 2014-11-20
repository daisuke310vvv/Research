#include <stdio.h>

#include "node.h"
#include "mpi.h"

int main(int argc,char *argv[]){

	hello_world();

	return 0;
}

void hello_world(){


	printf("hello world on Client\n");

}

