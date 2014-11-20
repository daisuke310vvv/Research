/*
 * camera.cpp
 *
 *  Created on: 2012/10/26
 *      Author: y-kuwa
 */

#include "camera.h"
#define XMLNAME "21142797.xml"
//#include "iostream"
namespace std {

camera::camera() {
	// TODO 自動生成されたコンストラクター・スタブ
	//const int str0[] = { 21142796, 21142798, 21142799, 21142800, 21142801,
	//		21142802, 21142804, 21142805, 21142806, 21142807, 21142808 }; //16台のカメラID

	const int tmp[] = {21142807,21142794,21142797,21142793,21142805, 21142808,21142799,21142796,21142800,21142801,21142798,21142806,21142795,21142792, 21142802}; //16台のカメラID

	for (int i = 0; i < int (sizeof(tmp)/sizeof(const int)); i++) {
		str0[i] = tmp[i];
	}
	//memcpy(str0, tmp, sizeof(tmp));

//	cout << str0[0] <<endl;

	serial = 0;
	intrinsic = cvCreateMat(3, 3, CV_32FC1); //内部行列;
	//CvMat intrinsic = cvCreateMat (3, 3, CV_32FC1);//内部行列
	distortion = cvCreateMat(1, 4, CV_32FC1);	//歪み係数
	rotation = cvCreateMat(3, 3, CV_64FC1);	//回転行列
	translation = cvCreateMat(3, 1, CV_64FC1);	//並進行列

}

camera::~camera() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

