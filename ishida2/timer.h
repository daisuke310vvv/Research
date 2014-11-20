/*
 * timer.h
 *
 *  Created on: 2012/12/06
 *      Author: y-kuwa
 */

#ifndef TIMER_H_
#define TIMER_H_
#include"iostream"
#include"mpi.h"
#include"string"

namespace std {

class timer {
public:
	timer();
	timer(string);
	void tstart();
	void tend();
	virtual ~timer();
	void printtime(string);
	void printtime();

private:
	double dbigin;
	double dend;
	string name;

};

} /* namespace std */
#endif /* TIMER_H_ */
