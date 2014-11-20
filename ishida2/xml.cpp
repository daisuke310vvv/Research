/*
 * xml.cpp
 *
 *  Created on: 2012/10/26
 *      Author: y-kuwa
 */

#include "xml.h"
#include <iostream>
namespace std {

xml::xml(string str0) {
	// TODO 自動生成されたコンストラクター・スタブ

	//カメラパラメータが記述されたxmlファイルを開く
	if ((cvfs = cvOpenFileStorage(str0.c_str(), NULL, CV_STORAGE_READ)) == 0) {
		cout << "read error xml: " << str0 << endl;
	}
	nodeA = NULL;
	nodeRows = NULL;
	nodeCols = NULL;
}

xml::xml() {
	// TODO Auto-generated destructor stub
	nodeA = NULL;
	nodeRows = NULL;
	nodeCols = NULL;
	cvReleaseFileStorage(&cvfs);
}

xml::~xml() {
	// TODO Auto-generated destructor stub
	cvReleaseFileStorage(&cvfs);
}

CvMat* xml::getIntrinsic(CvMat *data) {

	nodeA = cvGetFileNodeByName(cvfs, 0, "intrinsic");
	nodeRows = cvGetFileNodeByName(cvfs, nodeA, "rows");
	nodeCols = cvGetFileNodeByName(cvfs, nodeA, "cols");
	data = (CvMat*) cvRead(cvfs, nodeA, 0);
	return data;

}

CvMat* xml::getDistortion(CvMat *data) {

	nodeA = cvGetFileNodeByName(cvfs, 0, "distortion");
	nodeRows = cvGetFileNodeByName(cvfs, nodeA, "rows");
	nodeCols = cvGetFileNodeByName(cvfs, nodeA, "cols");
	data = (CvMat*) cvRead(cvfs, nodeA, 0);
	return data;

}

CvMat* xml::getRotation(CvMat *data) {

	nodeA = cvGetFileNodeByName(cvfs, 0, "rotation");
	nodeRows = cvGetFileNodeByName(cvfs, nodeA, "rows");
	nodeCols = cvGetFileNodeByName(cvfs, nodeA, "cols");
	data = (CvMat*) cvRead(cvfs, nodeA, 0);
	return data;

}

CvMat* xml::getTranslation(CvMat *data) {

	nodeA = cvGetFileNodeByName(cvfs, 0, "translation");
	nodeRows = cvGetFileNodeByName(cvfs, nodeA, "rows");
	nodeCols = cvGetFileNodeByName(cvfs, nodeA, "cols");
	data = (CvMat*) cvRead(cvfs, nodeA, 0);
	return data;

}

} /* namespace std */
