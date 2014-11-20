/*
 * calibration.h
 *
 *  Created on: 2012/11/06
 *      Author: y-kuwa
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <string>
#include "xml.h"
#include "camera.h"
#include "point.h"
#include "init.h"


/*
 * 正面画像?
 */



//#define DST_WIDTH 1278
//#define DST_HEIGHT 958
//#define PCNUM 3

namespace std {

//Clickした座標を保存する構造体を宣言します。
struct strPoint{
  int x;//座標を保存するための座標（？）
  int y;//座標を保存するための座標（？）
  int flag;
  int coordinate[NUM_POINTS*2];//座標
};

class calibration {
private:
	//CvFileStorage *cvfs;
	//int serial;
	//int mpirank;
	IplImage *srcBg_img;
	string filename;
	string tmpname;
	string str2;
	

public:
	camera Cameradata;
	calibration();
	calibration(string calibimg);
	virtual ~calibration();
	camera startcalib(int pcnum);
	bool DoCaliburation(int pcnum);
	static void Mouse(int event, int x, int y, int flags, void *param); // コールバック関数

};

} /* namespace std */
#endif /* CALIBRATION_H_ */
