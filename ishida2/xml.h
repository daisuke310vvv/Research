/*
 * xml.h
 *
 *  Created on: 2012/10/26
 *      Author: y-kuwa
 */

#ifndef XML_H_
#define XML_H_
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <string>
namespace std {

class xml {
private:
	CvFileStorage *cvfs;
	CvFileNode *nodeA;
	CvFileNode *nodeRows;
	CvFileNode *nodeCols;
public:
	xml(string);
	xml();
	virtual ~xml();

	CvMat* getIntrinsic(CvMat*);
	CvMat* getDistortion(CvMat*);
	CvMat* getRotation(CvMat*);
	CvMat* getTranslation(CvMat*);
	CvFileStorage* getCvfs(){return cvfs;}

};

} /* namespace std */
#endif /* XML_H_ */
