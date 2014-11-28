#include "node.h"

int main(int argc,char *argv[]){


	/* ---------------------------------------------------------- */
	// MPI通信クラスのインスタンス化
	/* ---------------------------------------------------------- */
	Communication *nodedata = new Communication(argc,argv);

	if(nodedata->getMyrank() == 0){
		puts("Node rank is 0. It must be a number except 0.\n exit.");
		return 1;
	}else
		printf("my rank is %d\n",nodedata->getMyrank());
	/* ---------------------------------------------------------- */


	/* ---------------------------------------------------------- */
	// serverに送信
	/* ---------------------------------------------------------- */
	nodedata->procrankSend(nodedata->getMyrank());
	/* ---------------------------------------------------------- */

	MPI_Barrier(MPI_COMM_WORLD);
	printf("end barrier on rank %d\n",nodedata->getMyrank());

	//nodedataを使ってデータのやりとり
	//node側は基本的にカメラから得た画像を処理してサーバ側に情報を投げる


	/* ---------------------------------------------------------- */
	// BallTracking
	/* ---------------------------------------------------------- */
	char imgName[256];

	int i;
	for(i = 0;i<60;i++){

		char imgName[256];
		sprintf(imgName,"/root/data/data1/%d.bmp",17800+i);
		IplImage *srcImg = cvLoadImage(imgName,CV_LOAD_IMAGE_GRAYSCALE);
		IplImage *inputImg = cvCreateImage(cvGetSize(srcImg),8,1);

		ballTrackingByHoughTransform(inputImg);
	}
	/* ---------------------------------------------------------- */

	

	/* ---------------------------------------------------------- */
	// デストラクト
	/* ---------------------------------------------------------- */
	delete (nodedata);
	nodedata = NULL;
	/* ---------------------------------------------------------- */

	return EXIT_SUCCESS;
}

void node_hello_world(){


	printf("hello world on Client\nfaaaaa\n");

}

