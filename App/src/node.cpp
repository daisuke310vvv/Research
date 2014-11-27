#include "node.h"

int main(int argc,char *argv[]){

	Communication *nodedata = new Communication(argc,argv);

	if(nodedata->getMyrank() == 0){
		puts("Node rank is 0. It must be a number except 0.\n exit.");
		return 1;
	}


	printf("my rank is %d\n",nodedata->getMyrank());
	//nodedataを使ってデータのやりとり
	//node側は基本的にカメラから得た画像を処理してサーバ側に情報を投げる

	delete (nodedata);
	nodedata = NULL;

	// BallTracking
	/* ------------------------------------------------------- */
	//char imgName[256];
	//sprintf(imgName,"/root/data/data1/%d.bmp",17800);
	//IplImage *img = cvLoadImage(imgName,CV_LOAD_IMAGE_GRAYSCALE);

	//ballTrackingByHoughTransform(img);
		/*
	int i;
	for(i = 0;i<60;i++){

		char imgName[256];
		sprintf(imgName,"/root/data/data1/%d.bmp",17800+i);
		IplImage *img = cvLoadImage(imgName,CV_LOAD_IMAGE_GRAYSCALE);

		ballTrackingByHoughTransform(img);
	}
	*/
	/* ------------------------------------------------------- */

	return EXIT_SUCCESS;
}

void node_hello_world(){


	printf("hello world on Client\nfaaaaa\n");

}

