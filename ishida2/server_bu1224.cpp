/*************************
 サーバーのメイン
 **************************/

#include "server.h"
#include<iostream>
#include"init.h"
using namespace std;

int main(int argc, char *argv[]) {

	Communication *serverdata = new Communication(argc, argv);

	/*サーバーはランクが０でなければならない */
	if (serverdata->getMyrank() != 0) {
		puts("server is not rank0 program exit");
		return 1;
	}

	//デバッグ
	cout << serverdata->getProcessorname() << "(" << serverdata->getMyrank()
			<< ")" << "server start!" << endl;

	/*
	 * オフライン処理を実行
	 */

	
	IplImage *temp = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	string calibimg ;
	int procname;
	for (int i = 0; i < iNodenum; i++) { //calib to koko de 2kai mawasite ta
		procname = serverdata->procnameReceive();
		temp->imageData = serverdata->receive();
		
		cout << "server receive from" <<procname<< endl;

		calibimg = "calib";
		ostringstream tmp;
		tmp << procname;
		calibimg += tmp.str();
		calibimg += ".bmp";
		cvSaveImage(calibimg.c_str(),temp);

		//	printf("%d",*calibData[i]);

		//if (!isoffline(calibimg,procname)){
			// cout<<"failed isoffline"<<endl;
		 //return -1;
		//}

	}	
	 
	/*
	 * ここで待つ
	 */
	//cout<<"waiting by server"<<endl;
	MPI_Barrier(MPI_COMM_WORLD );
	cout << "server online start" << endl;

	/*
	 * ここから
	 * オンライン処理
	 */
	timer tonline("isonline time");
	tonline.tstart(); //時間計測
	if (!isonline(serverdata))
		return -1;
	tonline.tend();
	tonline.printtime();

	//cout << "server main owari" << endl;

	MPI_Barrier(MPI_COMM_WORLD ); //待つ
	delete serverdata;
	serverdata = NULL;

	return EXIT_SUCCESS;
}

bool isoffline(string calibimg,int pcnum) {

	printf("pucnum = %d\n", pcnum);

	/*
	 * TODO: 未完成offline
	 * データを本当はノードから受け取る
	 * 今はファイルから読込してます
	 */

	calibration calibration(calibimg); //koko ga imi humei
	cout << "start calibration" << endl;
	
	Cameradata[pcnum] = calibration.startcalib(pcnum);
		cout << "error Caliburation" << endl;
		//return false;

	
	if (!Make3d.makeVoxeltable(pcnum,Cameradata[pcnum]))
		return false;
	cout << "makeVoxTable finish" << endl;

	return true;
}

bool isonline(Communication *serverdata) {
	cout << "server online start 1.0" << endl;

//	unsigned char *receivedata;
	IplImage *receivedata[iNodenum];
	for (int i = 0; i < iNodenum; i++){
		receivedata[i] = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	}
	cout << "server online start 1.1" << endl;

	//TODO:ココをオープンMPで並列実行
	//サーバーの数だけ受信
	//timer trecveive("receive time");
	//trecveive.tstart();
	for (int i = 0; i < iNodenum; i++) {
		receivedata[i]->imageData = serverdata->receive();
		cout << "server received " << i << endl;
		cvSaveImage("online.bmp",receivedata[i]);
	}
	cout << "server online start 1.2" << endl;
	//trecveive.tend();
	//trecveive.printtime();

	//TODO:データ出力
	//outputImage(receivedata[1], "test.ppm");
	
	//timer tmake3d("make3d time");
	//tmake3d.tstart();

	
	//if (!Make3d.start(receivedata[i]->imageData))
		//return false;

	//tmake3d.tend();
	//tmake3d.printtime();

	cout << "end make 3d" << endl;

	return true;

}

int outputImage(unsigned char *tmp, string outputFilename) {
	FILE * fp;
	if ((fp = fopen(outputFilename.c_str(), "w")) == NULL) {
		printf("file open error\n");
		//exit(EXIT_FAILURE);
		return -1;
	}
	cout << "output " << outputFilename << endl;
	fprintf(fp, "%s\n", "P6");
	fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
	fprintf(fp, "%d\n", 255);

	fwrite(tmp, sizeof(char), 3 * HEIGHT * WIDTH, fp);

	fclose(fp);
	return 0;
}

