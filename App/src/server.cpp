#include <stdio.h>

#include "server.h"

int main(int argc,char *argv[]){

	/* ----------------------------------------------------------- */
	// 同期通信クラスのインスタンス化
	/* ----------------------------------------------------------- */
	Communication *serverdata = new Communication(argc,argv);

	if(serverdata -> getMyrank() != 0){
		puts("server is not rank 0.");
		return 1;
	}else
		printf("I'm server. My rank is %d\n",serverdata->getMyrank());
	/* ----------------------------------------------------------- */



	/* ----------------------------------------------------------- */
	// ノードからの受信
	/* ----------------------------------------------------------- */
	//before(iNodenum) -> after(serverdata->getNodenum())
	printf("node num %d\n",serverdata->getNodenum());
	for(int i =0;i<serverdata->getNodenum()-1;i++){

		printf("received nodeRank %d\n",serverdata->procrankReceive());

	}
	/* ----------------------------------------------------------- */


	/* ----------------------------------------------------------- */
	// MPI_Barrier();
	// -> 全プロセスがこの関数を呼ぶまでブロック
	/* ----------------------------------------------------------- */
	MPI_Barrier(MPI_COMM_WORLD);
	/* ----------------------------------------------------------- */
	printf("end MPI_Barrier\n");


	/* ----------------------------------------------------------- */
	// デストラクト
	/* ----------------------------------------------------------- */
	delete (serverdata);
	serverdata = NULL;
	/* ----------------------------------------------------------- */

	return EXIT_SUCCESS;
}

void hello_world(){

	printf("hello world on servereeeer\n");
}
