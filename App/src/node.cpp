#include <stdio.h>

#include "node.h"

int main(int argc,char *argv[]){

	node_hello_world();

	/* ---------------------------------------------- */
	// 
	/* ---------------------------------------------- */
	/*
	Communication *nodedata = new Communication(argc,argv);

	if(nodedata->getMyrank() == 0){
		puts("Node rank is 0. It must be a number except 0.\n exit.");
		return 1;
	}

	//nodedataを使ってデータのやりとり
	//node側は基本的にカメラから得た画像を処理してサーバ側に情報を投げる

	hello_world();


	delete (nodedata);
	nodedata = NULL;

	*/

	return EXIT_SUCCESS;
}

void noed_hello_world(){


	printf("hello world on Client\n");

}

