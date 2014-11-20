/*
 * point.h
 *
 *  Created on: 2012/11/07
 *      Author: y-kuwa
 */

#ifndef POINT_H_
#define POINT_H_

//#define NUM_POINTS 9
#include "cstring"
#include "init.h"

namespace std {

class point {
private:

	double rl[NUM_POINTS*3];

	double digiPoint_mat[18];

public:

	point();
	virtual ~point();
	 double* get_rl() {
		return rl;
	}
	void setdigiPoint_mat(double*);
	double* getdigiPoint_mat() {
		return digiPoint_mat;
	}

};

} /* namespace std */
#endif /* POINT_H_ */
