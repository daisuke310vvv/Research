/*
 * timer.cpp
 *
 *  Created on: 2012/12/06
 *      Author: y-kuwa
 */

#include "timer.h"

namespace std {

timer::timer() {
	// TODO 自動生成されたコンストラクター・スタブ
	dbigin = 0;
	dend = 0;
	name = "NULL";
}

timer::timer(string tmp) {
	// TODO 自動生成されたコンストラクター・スタブ
	dbigin = 0;
	dend = 0;
	name = tmp;

}

timer::~timer() {
	// TODO Auto-generated destructor stub
}

void timer::tstart() {
	dbigin = MPI_Wtime();
}

void timer::tend() {
	dend = MPI_Wtime();
}
void timer::printtime(string tmp) {
	name = tmp;
	if (dend - dbigin < 0) {
		cout << name << "time error" << endl;
	}

	else {
		cout << name << ":" << dend - dbigin << endl;
	}

}

void timer::printtime() {
	if (dend - dbigin < 0) {
		cout << "time error" << endl;
	}

	else {
		if (name != "NULL")
			cout << name << ":" << dend - dbigin <<"[s]" <<endl;
		else
			cout << dend - dbigin << endl;
	}

}

} /* namespace std */
