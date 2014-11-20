/*
 * make3d.h
 *
 *  Created on: 2012/11/12
 *      Author: y-kuwa
 */

#ifndef MAKE3D_H_
#define MAKE3D_H_

#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
#include<iostream>

//並列処理のためのライブラリ
#include <omp.h>

//時間計測のためのライブラリ
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <unistd.h>

#include <math.h>
#include <omp.h>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include "calibration.h"
#include "init.h"
#include "timer.h"

//TODO:defineはひとつにまとめる

#endif /* MAKE3D_H_ */


namespace std {

struct structVoxel {
	int i[iMAX];
	int num;
};

struct strRunlengthList { //背景差分の二値化した画像を圧縮するためのランレングスリスト
	int xstart;
	int xend;
	int ystart;
	int yend;
};



class make3d {
private:
	static const int listsize = 10000;

	//ボクセルで使用する変数
	int ***field_voxel;
	structVoxel *strVoxTable; //ハッシュテーブル作成
	//camera camParm[iNodenum];

	string str;
	IplImage *srcBg_img[iNodenum]; //yomikomi img
	
	IplImage *bird_img; //鳥瞰図
	strRunlengthList *imglist;
	//camera Cameradata[iNodenum];
	//calibration Calibed;//atterukana?

	bool makeBirdImg(IplImage **img,int picnum);

	bool reconstruction(int, int, int);

	long int hush(int m, int u, int v) {

		return (u + v * (WIDTH) + m * WIDTH * HEIGHT);
	}
	int hushI(int h) {
		int i;
		i = h % (SIZE * SIZE);
		i = i % SIZE;
		return (i);
	}
	int hushJ(int h) {
		int j;
		j = h % (SIZE * SIZE);
		j = j / SIZE;
		return (j);
	}
	int hushK(int h) {
		int k;
		k = h / (SIZE * SIZE);
		return (k);
	}

public:
	bool start(IplImage **img,int picnum);
	make3d();
	bool makeVoxeltable(int i,camera Cameradata);
	virtual ~make3d();
};

} /* namespace std */
