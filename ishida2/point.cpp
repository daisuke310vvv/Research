/*
 * point.cpp
 *
 *  Created on: 2012/11/07
 *      Author: y-kuwa
 */

#include "point.h"

namespace std {


point::point() {
	// TODO 自動生成されたコンストラクター・スタブ


	char rltemp[] ={0,P_HEIGHT,0,P_WIDTH,P_HEIGHT,0,P_WIDTH,0,0,0,0,0};
	
	memmove(rl, rltemp, 8*NUM_POINTS*3);

}

point::~point() {
	// TODO Auto-generated destructor stub
}

void point::setdigiPoint_mat(double * tmp) {
	for (int i = 0; i < 17; i++)
		digiPoint_mat[i] = tmp[i];
}

} /* namespace std */
