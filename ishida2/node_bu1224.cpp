/****************************************
 ノードのメイン
 ****************************************/

#include<iostream>
#include "node.h"
#include"init.h"
using namespace std;


int main(int argc, char *argv[]) {

	Communication* nodedata = new Communication(argc, argv);

	//char temp[100];
	/*ノードはランクが0以外でなければならない */
	if (nodedata->getMyrank() == 0) {
		puts("node rank = 0 program exit");
		return 1;
	}
	
	//デバッグ用出力
	string temp = nodedata->getProcessorname();
	cout << temp << "(" << nodedata->getNodenum() << "): My rank is "
			<< nodedata->getMyrank() << endl;
	/*
	 * キャリブレーションイメージを送信する
	 */
	int procname;
	procname = procname2cameranum(temp);
	char str[32];

	IplImage *tmp_img;
	sprintf(str, "/home/user/img/1.bmp");
	tmp_img = cvLoadImage(str,CV_LOAD_IMAGE_ANYCOLOR);
	
	nodedata->procnameSend(procname);	//processer nameの転送
	nodedata->send(tmp_img->imageData);	//結果の転送
	cvReleaseImage(&tmp_img);

	cout<<"send calibImage"<<endl;
	
//cout<<"waiting"<<endl;
	MPI_Barrier(MPI_COMM_WORLD); // waiting for each pc
//cout<<"node online start!"<<endl;
	
	/*
	 * オンライン処理
	 *
	 */
	Images* images = new Images(filename, NUMIMG); //TODO ayasii
	if (!isnodeonline(images)){
	cout<<"error online"<<endl;
		return false;

	}

	/*
	 * データの転送
	 */

	sprintf(str, "online.ppm");
	tmp_img = cvLoadImage(str,CV_LOAD_IMAGE_ANYCOLOR);

	cout<<"node send data"<<endl;
//images->test(images->getimage());
	nodedata->send(tmp_img->imageData);	//結果の転送
//sleep(10);
	MPI_Barrier(MPI_COMM_WORLD);

	/*
	 * 後始末
	 */
	//delete (images);
	images = NULL;

	delete (nodedata);
	nodedata = NULL;

	//cout << temp << ": nodeend!!" << endl;

	return EXIT_SUCCESS;
}

bool isnodeonline(Images* images) {
	/*
	 *  オンライン処理
	 *  本当はforで回す
	 */
	//start = clock();
	char str[32];
	sprintf(str, "%s%d.bmp", filename, NUMIMG);
	/*
	 * ここの部分はカメラから撮影したデータとなる
	 */
	cout <<"online data: "<< str << endl;
	Image* image = new Image(str);
	images->online(image);

	if(images->getimage()==NULL)
		return false;
	//images->test(image);
	images->test(images->getimage());
	//delete image;
	return true;

}

int procname2cameranum(string temp) {

return atoi(temp.substr(7,2).c_str());
}

