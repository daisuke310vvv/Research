/*
 * make3d.cpp
 *
 *  Created on: 2012/11/12
 *      Author: y-kuwa
 */

#include "make3d.h"


namespace std {

make3d::make3d() {
	//printf("make3d.cpp\n");
	// TODO 自動生成されたコンストラクター・スタブ

	strVoxTable = new structVoxel[WIDTH * HEIGHT * iNodenum];
	if (strVoxTable == NULL)
		cout << "error new VoxTable" << endl;
	//cout << sizeof(*strVoxTable) << endl;
	imglist = new strRunlengthList[listsize];

	fill(&strVoxTable[0].num, &strVoxTable[WIDTH * HEIGHT * iNodenum].num, 0);

	//field_voxel = new int[HIGH][SIZE][SIZE];

	field_voxel = new int**[SIZE];

	for (int i = 0; i < SIZE; i++) {
		field_voxel[i] = new int*[SIZE];
		for (int j = 0; j < SIZE; j++) {
			field_voxel[i][j] = new int[HIGH];
		}
	}

}

make3d::~make3d() {
	// TODO Auto-generated destructor stub
	delete[] strVoxTable;
	delete[] bird_img;
	delete[] imglist;
	delete[] field_voxel;

}
bool make3d::start(IplImage **img,int picnum) {
	
	cout << "start make3d" << endl;
	
	if (!makeBirdImg(img,picnum)) {
		cout << "error reconstucition" << endl;
		return false;
	}
	cout << "make BirdImg finish" << endl;

	return true;
}

bool make3d::makeVoxeltable(int pcnum,camera Cameradata) {
	unsigned int u, v; //ピクセル番号
	double xw, yw, zw; //フィールド座標系
	double xc, yc, zc; //カメラ座標系
	double xc1, xc2, yc1, yc2;
	double r; //回転ベクトル
	double cx=0;
	double cy=0;
	double fx=0;
	double fy=0;
	double k1=0;
	double k2=0;
	double p1=0;
	double p2=0;

	//新カメラ(Basler)での仕様
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
	
	CvMat *w_mat = cvCreateMat(3, 1, CV_64FC1); //行列w_matの領域確保
	//CvMat *c_mat = cvCreateMat(3, 1, CV_64FC1); //行列c_matの領域確保
	CvMat *ans1 = cvCreateMat(3, 1, CV_64FC1);	//行列計算の最初の答えの領域確保
	CvMat *ans2 = cvCreateMat(3, 1, CV_64FC1);	//行列計算の最後の答えの領域確保
	//全てのボクセルを各画像の全てのピクセルに対応させる↓↓-------------------------------------------------------------------------------------------------------------------------------------------
	//	#pragma omp parallel for private(pcnum,pcnum,j,k,xw,yw,zw,xc,yc,zc,xc1,yc1,r,xc2,yc2,u,v,)
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < HIGH; k++) {
				//printf("%d,%d,%d\n",i,j,k);
				xw = i * V_WIDTH;
				yw = j * V_HEIGHT;
				zw = k * V_HIGH;
				//printf("%f,%f,%f\n",xw,yw,zw);
				cvmSet(w_mat, 0, 0, xw);
				cvmSet(w_mat, 1, 0, yw);
				cvmSet(w_mat, 2, 0, zw);
				//  printf("1\n");

				cvmMul(Cameradata.rotation, w_mat, ans1);
				cvmAdd(ans1, Cameradata.translation, ans2);

				//ここの値がマイナスになるのは合っているのか？
				xc = cvmGet(ans2, 0, 0);
				yc = cvmGet(ans2, 1, 0);
				zc = cvmGet(ans2, 2, 0);
                     
				xc1 = xc / zc;
				yc1 = yc / zc;
				r = sqrt(pow(xc1, 2.0) + pow(yc1, 2.0));
				/*cout << "r=" << r << " xc1=" << xc1 << " k1="
						<< k1 << endl;makeBirdImg(
				*/
				xc2 = xc1* (1 + k1 * pow(r, 2.0)+ k2 * pow(r, 4.0))+ 2 * p1 * xc1 * yc1+ p2 * (pow(r, 2.0) + 2 * pow(xc1, 2.0));
				yc2 = yc1* (1 + k1 * pow(r, 2.0)+ k2 * pow(r, 4.0))+ p1 * (pow(r, 2.0) + 2 * pow(yc1, 2.0))+ 2 * p2 * xc1 * yc1;

				u = (unsigned int) (fx * xc2 + cx);
				v = (unsigned int) (fy * yc2 + cy);
				/*cout << "fx = " << fx << " xc2 = " << xc2
						<< " cx = " << cx << endl;
				cout << "fy = " << fy << " yc2 = " << yc2
						<< " cy = " << cy << endl;
				cout << "u = " << fx * xc2 + cx << endl;
				cout << "v = " << fy * yc2 + cy << endl;
				*/
				if (u < 0)
					u = u * (-1);
				if (v < 0)
					v = v * (-1);
				if (u >(unsigned ) WIDTH)
				 u = 0;
			
				if (v > (unsigned )HEIGHT)
				 v = 0;

				/*if()
				 v=0;
				 */
				//cout << "pcnum = " << pcnum << "\ni = " << i
				//		<< "\nj = " << j << "\nk = " << k << endl;

				//cout << hush(pcnum, u, v) << endl;
				unsigned long int h = abs(hush(pcnum, u, v));
				//if (tmp > WIDTH * HEIGHT * iNodenum)
					//tmp = 0;

				if (strVoxTable[h].num < iMAX) {
					strVoxTable[h].i[strVoxTable[h].num] = i + SIZE * j+ SIZE * SIZE * k;
					strVoxTable[h].num += 1;
					//cout << "strVoxTable[tmp].num"<<strVoxTable[tmp].num<<endl;

					//printf("fx = %f,xc2 = %f, cx = %f,u =%d\n",fx,xc2,cx,u);
					//printf("fy = %f,yc2 = %f, cy = %f,v =%d\n",fy,yc2,cy,v);
					//printf("(%d,%d,%d) - (%d,%d) \n",i,j,k,u,v);
				}
			}
		}
	}

	return true;
}

bool make3d::reconstruction(int m, int u, int v) {
	int h = hush(m, u, v);
	//cout << "h = "<< h<<endl;
 	//cout << "strVoxTable["<<h<<"].num"<<strVoxTable[h].num<<endl;
	for (int p = 0; p < strVoxTable[h].num; p++) {
		 //lscout << "h = "<< h<<endl;
		
		/*printf("hushI = %d\n",hushI(strVoxTable[hush(m,u,v)].i[p]));
		 printf("hushJ = %d\n",hushJ(strVoxTable[hush(m,u,v)].i[p]));
		 printf("hushK = %d\n",hushK(strVoxTable[hush(m,u,v)].i[p]));*/
		field_voxel[hushI(strVoxTable[h].i[p])][hushJ(strVoxTable[h].i[p])][hushK(strVoxTable[h].i[p])] += 1;
		//cout << "count"<<endl;

	}
	return true;
}

bool make3d::makeBirdImg(IplImage **srcBg_img,int picnum) {
	cout << "start makeBirdImg" << endl;
	
bird_img = cvCreateImage(cvSize(SIZE, SIZE), IPL_DEPTH_8U, 1);
//cout << "01" << endl;

timer makeverdimage("make verdimage");
makeverdimage.tstart();
	
	/*
	 * TODO: ここはノードから送られてきた画像を使います
	 *
	 */
	
	

	//初期化
int i,j,k,y,x;
#pragma omp parallel num_threads(8)
{

#pragma omp  for private(i,j,k)
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			for (k = 0; k < HIGH; k++) {
				if (k == 0) {
				
					bird_img->imageData[i + j * SIZE] = 0;

				}
				field_voxel[i][j][k] = 0; //ボクセルの初期化
			}
		}
	}
//cout << "02" << endl;

#pragma omp  for private(i,y,x)
	for (i = 0; i < iNodenum; i++) {
		for (y = 0; y < HEIGHT; y++) {
			for (x = 0; x < WIDTH; x++) {
				
				//ピクセルが選手領域画素ならば
				if ((unsigned char) srcBg_img[i]->imageData[srcBg_img[i]->widthStep* y + x] != 0) {

					reconstruction(i, x, y);

				} 
			}
		}
	}
	/*Graph R*/
/*
	FILE *fp;
	str[32];
	if ((fp = fopen("vox.csv", "w")) == NULL) {
		printf("file open error fp\n");
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "ﾃﾞｰﾀ形式,2\n");
	fprintf(fp, "memo\n");
	fprintf(fp, "X,Y,Z\n");
*/
//cout << "03" << endl;

#pragma omp  for private(i,j,k)
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			for (k = 0; k < HIGH; k++) {
				
				if (field_voxel[i][j][k] == VOTE) {				//票数閾値
					bird_img->imageData[i + j *bird_img->widthStep] = 255;
				
				}
			}
		}
	}
}
//cout << "04" << endl;
makeverdimage.tend();
makeverdimage.printtime();

	//fclose(fp);
	IplImage *dst_img;
	dst_img = cvCloneImage(bird_img);
	cvFlip(bird_img,dst_img,1);
	char str4[30];
	sprintf(str4, "bird/%d.bmp", picnum);
	cvSaveImage(str4, dst_img);
	//cout << "makeBirdImg finished" << endl;
	//cvWaitKey(0); // ０秒待つ => ずっと入力待ち
	return true;
}

} /* namespace std */
