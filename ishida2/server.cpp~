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
	
	for (int i = 0; i < iNodenum; i++) {
		
		pc2rank[i] = serverdata->procrankReceive();		
		pc2imgs[i] = serverdata->procnameReceive(pc2rank[i]);
		cout << "server receive from bfrimg" <<pc2imgs[i]<< endl;
		pc2imgs[i] +=(-1);
		//pc2rank[i] +=(-1);
		temp->imageData = serverdata->receive(pc2rank[i]);
		
		cout << "server receive from rank" <<pc2rank[i]<< endl;
		cout << "server receive from aftimg" <<pc2imgs[i]<< endl;

		calibimg = "calib";
		ostringstream tmp;
		tmp << pc2rank[i];
		calibimg += tmp.str();
		calibimg += ".bmp";
		cvSaveImage(calibimg.c_str(),temp);

		//	printf("%d",*calibData[i]);

		if (!isoffline(calibimg,pc2imgs[i],i)){
			 cout<<"failed isoffline"<<endl;
		 	return -1;
		}
	}	
	 
	/*
	 * ここで待つ
	 */
	//cout<<"waiting by server"<<endl;
	MPI_Barrier(MPI_COMM_WORLD);
	cout << "server online start" << endl;

	/*
	 * ここから
	 * オンライン処理
	 */
	//timer tonline("isonline time");
	//tonline.tstart(); //時間計測
	if (!isonline(serverdata))
		return -1;
	//tonline.tend();
	//tonline.printtime();

	//cout << "server main owari" << endl;

	//MPI_Barrier(MPI_COMM_WORLD ); //待つ
	delete serverdata;
	serverdata = NULL;

	return EXIT_SUCCESS;
}

bool isoffline(string calibimg,int pcnum,int i) {

	printf("pucnum = %d\n", pcnum);

	calibration calibration(calibimg); //koko ga imi humei
	cout << "start calibration" << endl;
	
	Cameradata[i] = calibration.startcalib(pcnum);
		//cout << "error Caliburation" << endl;
		//return false;

	if (!Make3d.makeVoxeltable(i,Cameradata[i]))
		return false;
	cout << "makeVoxTable finish" << endl;

	return true;

}

bool isonline(Communication *serverdata) {
	cout << "server memory allocated" << endl;
	//unsigned char *receivedata;
	IplImage *receivedata[iNodenum],*test_img[iNodenum];
	//cvCreateImage(cvSize(HEIGHT/10,WIDTH/10),8,1);

	
	//int *imglist[iNodenum];
	char str3[20];
	for(int picnum=26300;picnum<=30000;picnum++){

		for (int i = 0; i < iNodenum; i++){
		test_img[i] = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);
		receivedata[i] = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);
		}
	//printf("test\n");
		
		//TODO:ココをオープンMPで並列実行
		//サーバーの数だけ受信
		
		cout << "----receive wating   "<< picnum <<"-----"<< endl;
		MPI_Barrier(MPI_COMM_WORLD);
		timer trecveive("receive time");
		trecveive.tstart();
		for (int i = 0; i < iNodenum; i++) {
			receivedata[i]->imageData = serverdata->monoreceive(pc2rank[i]);
			//imglist[i] = serverdata->testreceive(pc2rank[i]);
			//cout << "server receive from rank" <<pc2rank[i]<< endl;
			//sprintf(str3,"/home/user/receve%dimg.bmp",pc2rank[i]);
			//cvSaveImage(str3,receivedata[i]);
		}
		
		
		//for (int i = 0; i < iNodenum; i++) {
			//receivedata[i]->imageData = serverdata->monoreceive(pc2rank[i]);
			//imglist[i] = serverdata->testreceive(pc2rank[i]);
			//cout << "save image of  receivedata from rank" << pc2rank[i]<< endl;
			//sprintf(str3,"/home/user/receve%dimg.bmp",pc2rank[i]);
			//cvSaveImage(str3,receivedata[i]);
		//}

		trecveive.tend();
		trecveive.printtime();
		
		//timer tmake3d("make3d time");
		//tmake3d.tstart();

		//start_clock =clock();
	
		if (!Make3d.start(receivedata,picnum))
			return false;

		for (int i = 0; i < iNodenum; i++){
		
		cvReleaseImage(&receivedata[i]);
		}
		//for (int i = 0; i < iNodenum; i++)
		//delete[] receivedata;

		MPI_Barrier(MPI_COMM_WORLD); // waiting for each pc

		//picnum++;
	}
	
	cvWaitKey(0); // ０秒待つ => ずっと入力待ち
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

