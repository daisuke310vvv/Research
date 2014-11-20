/*
 * calibration.cpp
 *
 *  Created on: 2012/11/06
 *      Author: y-kuwa
 */

#include "calibration.h"


namespace std {

calibration::calibration() {
	// TODO 自動生成されたコンストラクター・スタブ

	//TODO 連結
	filename = "test.bpm"; //ここはカメラから受け取った画像にする
	srcBg_img = cvLoadImage(filename.c_str(), CV_LOAD_IMAGE_ANYCOLOR);

}

calibration::calibration(string calibimg) {
	//cvCopy(temp,srcBg_img);
	// TODO 自動生成されたコンストラクター・スタブ

	filename = calibimg; //konnna mendo-na kotowo sinakute ha ikenai noka?
	srcBg_img = cvLoadImage(filename.c_str(), CV_LOAD_IMAGE_ANYCOLOR);
}

calibration::~calibration() {
	// TODO Auto-generated destructor stub
}

camera calibration::startcalib(int pcnum) {
	//for (int i = 0; i < iNodenum; i++) {
		//tmpname = Cameradata.str0[i];
		 //TODO kamera num to image no taio zuke
		
		ostringstream tmp;
		tmp << Cameradata.str0[pcnum]; //string型へ変換
		tmpname = "inParams/";
		tmpname += tmp.str();
		tmpname += ".xml";
		//printf("pucnum = %d\n", pcnum);
		cout << "Read inPrams of -" << tmpname << endl;

		Cameradata.serial = Cameradata.str0[pcnum];
		xml xmldata(tmpname);
		Cameradata.intrinsic = xmldata.getIntrinsic(Cameradata.intrinsic);
		Cameradata.distortion = xmldata.getDistortion(Cameradata.distortion);

		double cx=0;
		double cy=0;
		double fx=0;
		double fy=0;
		double k1=0;
		double k2=0;
		double p1=0;
		double p2=0;
	
		//新カメラ(Basler)での仕様
		//for (int pcnum = 0; pcnum < iNodenum; pcnum++) {
		
		cx= cvmGet(Cameradata.intrinsic, 0, 2);
		printf("cx = %f, ", cx);
		cy = cvmGet(Cameradata.intrinsic, 1, 2);
		printf("cy = %f, ", cy);
		fx = cvmGet(Cameradata.intrinsic, 0, 0);
		printf("fx = %f, ", fx);
		fy = cvmGet(Cameradata.intrinsic, 1, 1);
		printf("fy = %f, ", fy);
		k1 = cvmGet(Cameradata.distortion, 0, 0);
		printf("k1 = %f, ", k1);
		k2 = cvmGet(Cameradata.distortion, 0, 1);
		printf("k2 = %f, ", k2);
		p1 = cvmGet(Cameradata.distortion, 0, 2);
		printf("p1 = %f, ", p1);
		p2 = cvmGet(Cameradata.distortion, 0, 3);
		printf("p2 = %f\n", p2);
		//}

		cout << "set name of exParams " << tmpname << endl;
		tmpname = "exParams/";
		tmpname += tmp.str();
		tmpname += ".xml";
		cout << "Set exPrams of -" << tmpname << endl;
		 
		if (DoCaliburation(pcnum)==false) {
			cout << "DoCalibration return false" << endl;
			
		}
		//i++;
	//}
	return Cameradata;

}
void calibration::Mouse(int event, int x, int y, int flags, void *param) { // コールバック関数

	strPoint *click_pointData;
	click_pointData = (strPoint *) param;

	switch (event) {
	//左クリックした場合の処理を下記に記す。
	case CV_EVENT_LBUTTONDOWN:
		click_pointData->coordinate[click_pointData->x] = x;	//デジタル画像上のx座標代入
		click_pointData->coordinate[click_pointData->y] = y;	//デジタル画像上のy座標代入
		click_pointData->flag++;

		//規定回数に達するまでクリックにて取得する。
		if (click_pointData->flag <= NUM_POINTS) {
			printf("【%d回目】%d,%d\n", click_pointData->flag,
					click_pointData->coordinate[click_pointData->x],
					click_pointData->coordinate[click_pointData->y]);
			click_pointData->x = click_pointData->x + 2;
			click_pointData->y = click_pointData->y + 2;
		}

		if (click_pointData->flag == NUM_POINTS) {
			//click_pointData->flag=0;
			break;
		}
		break;
	}
}

bool calibration::DoCaliburation(int pcnum) {	//iNodenumの数だけ実行される
	//xmlのデータを読み出し
	xml xmldata(tmpname);
	// もし以前に外部パラメータファイルが生成されていたらキャリブレーションを行わない。 (注)少しでもカメラが動いた場合はするキャリブレーションが必要
	if (xmldata.getCvfs() != 0) {
		string presskey;
		for (;;) {
			cout << " 【Attention!!】" << tmpname
					<< " is already created.\n if you calibrate press [y] \n,if you read this file press [n] \n"
					<< endl;
			//scanf("%d", &presskey);
			cin >> presskey;
			if (presskey == "y")
				break;

			else if (presskey == "n") {
				cout << "NOT calibration" << endl;
				//既に存在するファイルから外部パラメータを読み込む
				Cameradata.rotation = xmldata.getRotation(Cameradata.rotation); //回転行列
			
				Cameradata.translation = xmldata.getTranslation(Cameradata.translation); //並進行列
				return true;
			
			}
		}
	}

	/*
	 * ここからキャリブレーション
	 */
	cout << "start calibration: " << Cameradata.serial << endl;

	CvMat src_point_mat;	//対応する画像上の点の配列．2xNまたはNx2でNはビューにおける点の数．
	CvMat realPoints_mat;	//オブジェクトの点の配列．3xNまたはNx3でNはビューにおける点の数．
	CvMat *r_vector;	//回転ベクトル
	r_vector = cvCreateMat(3, 1, CV_64FC1);	//回転ベクトルのメモリを確保します。
	//point click_point;

	strPoint mouse_point;
	mouse_point.x = 0;
	mouse_point.y = 1;
	mouse_point.flag = 0;
	//OpenCVの形式に変換
	double rl[]={0,P_HEIGHT,0,
			P_WIDTH,P_HEIGHT,0,
			P_WIDTH,0,0,
			0,0,0,
		};
	realPoints_mat = cvMat(NUM_POINTS, 3, CV_64FC1,rl);
	//引数の画像を表示します。
	if (srcBg_img == NULL) {
		printf("Can'matT load Image¥n");
		cvWaitKey(0);
		return false;
	}
	cvNamedWindow("Calibration", CV_WINDOW_AUTOSIZE);
	cvShowImage("Calibration", srcBg_img);
	cvSetMouseCallback("Calibration", Mouse, &mouse_point);
	mouse_point.x = 0;
	mouse_point.y = 1;
	//すべての座標を取得したら画像ウィンドウをクリックし次のステップへ進みます。
	cvWaitKey(0); // ０秒待つ => ずっと入力待ち
	cvDestroyWindow("Calibration");

	double digiPoint_mat[]={mouse_point.coordinate[0],mouse_point.coordinate[1],mouse_point.coordinate[2],mouse_point.coordinate[3],mouse_point.coordinate[4],mouse_point.coordinate[5],mouse_point.coordinate[6],mouse_point.coordinate[7]};
	src_point_mat = cvMat(NUM_POINTS,2,CV_64FC1,digiPoint_mat);

	//click_point.setdigiPoint_mat((double*) mouse_point.coordinate);
	//src_point_mat = cvMat(NUM_POINTS, 2, CV_64FC1,click_point.getdigiPoint_mat());

	//回転ベクトルと並進ベクトルの算出します。
	cvFindExtrinsicCameraParams2(&realPoints_mat, &src_point_mat,Cameradata.intrinsic, 0, r_vector, Cameradata.translation); //内部パラメータを用いて回転ベクトルと並進ベクトルを算出
	//回転ベクトルから回転行列へ変換します。
	cvRodrigues2(r_vector, Cameradata.rotation);
	//homography行列を計算
	CvMat *h = cvCreateMat(3, 3, CV_64FC1);
	cvFindHomography(&src_point_mat, &realPoints_mat, h);

	// 正面変換
	IplImage *dst_img;
	dst_img = cvCreateImage(cvSize(P_WIDTH, P_HEIGHT), IPL_DEPTH_8U, 3); //正面画像領域確保
	cvWarpPerspective(srcBg_img, dst_img, h);
	cvSaveImage("shomen.bmp", dst_img);

	// 算出した外部行列をXMLファイルへ書き出します。
	CvFileStorage *fs;
	str2 = "exParams/";
	ostringstream tmp;
	tmp << Cameradata.serial;
	str2 += tmp.str();
	str2 += ".xml";
	cout << "output file :" << str2 << endl;
	fs = cvOpenFileStorage(str2.c_str(), 0, CV_STORAGE_WRITE);
	//cout << "tst05.3" << endl;
	//cvWrite (fs, "CameraID", camParm->serial);
	cvWrite(fs, "intrinsic", Cameradata.intrinsic);
	cvWrite(fs, "rotation", Cameradata.rotation);
	cvWrite(fs, "translation", Cameradata.translation);
	cvWrite(fs, "distortion", Cameradata.distortion);
	cvReleaseFileStorage(&fs);
	//cout << "tst05.3" << endl;

	return true;
}
} /* namespace std */

