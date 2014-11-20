/****************************************
 ノードのメイン
 ****************************************/

#include<iostream>
#include "node.h"
#include"init.h"
using namespace std;


int main(int argc, char *argv[]) {

	nodedata = new Communication(argc, argv);

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

	
	sprintf(str, "%s%d.bmp", filename, 0);
	tmp_img = cvLoadImage(str,CV_LOAD_IMAGE_ANYCOLOR);
	
	nodedata->procrankSend(nodedata->getMyrank());
	nodedata->procnameSend(procname);	//processer nameの転送
	nodedata->send(tmp_img->imageData);	//結果の転送
	

	cout<<"send calibImage"<<endl;
	
	//cout<<"waiting"<<endl;
	MPI_Barrier(MPI_COMM_WORLD); // waiting for each pc
	//cout<<"node online start!"<<endl;
	
	/*
	 * オンライン処理
	 *
	 */
	
	//Images* images = new Images(filename, NUMIMG ,STARTNUM); //OFFLINE SHORI
	
	//OnLine SHORI
	//if (!isnodeonline(images)){
	//	cout<<"error online"<<endl;
	//	return false;
	//}

	/*
	 * データの転送
	 */
	IplImage *tmp_img;
	int listflag=0,k=0;
	tmp_img = cvLoadImage(str,CV_LOAD_IMAGE_GRAYSCALE);
	int imglist[HEIGHT*20];

//RUNLENGTH
	for(int i=0;i<WIDTH;i++){
	for(int j=0;j<HEIGHT;j++){
		if(tmp_img->imageData[j*WIDTH+i]!=0){//senshu

			if(listflag==0){
			//startpoint
			imglist[k] = i+j*WIDTH;
			listflag++;
			}
			else{
			imglist[k] = i+j*WIDTH;
			listflag++;
			}
		}
		else{//haikei
			if(listflag!=0){
			k++;
			//printf("k=%d\n",k);
			listflag=0;
			}
			else{
			listflag=0;
			}
		}
	}
}
	for(int picnum=26300;picnum<=30000;picnum++){
		
		
		sprintf(str, "%s%d.bmp",tempfilename,picnum);
		tmp_img = cvLoadImage(str,CV_LOAD_IMAGE_GRAYSCALE);
		//cvSaveImage(str3,receivedata[i]);
		
		MPI_Barrier(MPI_COMM_WORLD);
		nodedata->monosend(tmp_img->imageData);	//結果の転送
		//printf("procname = %d send ok\n",procname);
			//sleep(10);
		//nodedata->testsend(imglist);	//結果の転送

		MPI_Barrier(MPI_COMM_WORLD);
		cvReleaseImage(&tmp_img);

	}
	//cout << nodedata->getMyrank()<<"--node online start"<<endl;
	//sprintf(str, "/home/user/2.bmp");
	//tmp_img = cvLoadImage(str,CV_LOAD_IMAGE_GRAYSCALE);

	//images->test(images->getimage());
	
	/*
	 * 後始末
	 */
	
	//delete (images);
	//images = NULL;

	delete (nodedata);
	nodedata = NULL;

	//cout << temp << ": nodeend!!" << endl;

	return EXIT_SUCCESS;
}

bool isnodeonline(Images* images) {
	/*
	 *  オンライン処理
	 */
	int i=0;
	while(0){

		//start = clock();
		char str[32];
		sprintf(str, "%s%d.bmp", filename, STARTNUM+NUMIMG+i);
		printf("%d.bmp\n", STARTNUM+NUMIMG+i);

		/*
		* ここの部分はカメラから撮影したデータとなる
		*/

		cout <<"online data: "<< str << endl;
		Image* image = new Image(str);
		cout << "online-image read" << endl;
		images->online(image);

		if(images->getimage()==NULL)
			return false;
		//images->test(image);
		images->test(images->getimage());

		nodedata->monosend(tmp_img->imageData);	//結果の転送
		//sleep(10);
		MPI_Barrier(MPI_COMM_WORLD);
		i++;
	}

	//delete image;
	return true;

}

int procname2cameranum(string temp) {

return atoi(temp.substr(6,2).c_str());
}

