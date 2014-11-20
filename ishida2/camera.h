/*
 * camera.h
 *
 *  Created on: 2012/10/26
 *      Author: y-kuwa
 */

#ifndef CAMERA_H_
#define CAMERA_H_

//OpenCVのライブラリ
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <string>
#include<cstring>
#include "xml.h"
namespace std {

class camera {
public:
	//カメラのデータはどこからでも見えるようにするので扱いに注意すること
	//この値がベースとなり、キャリブレーションするとここにまた入れる
	CvMat *intrinsic;
	CvMat *distortion;
	CvMat *rotation;
	CvMat *translation;
	int str0[15];
	int serial;

	camera();
	virtual ~camera();
};





} /* namespace std */
#endif /* CAMERA_H_ */
