/*
 * sqrt.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Eric Song
 *      I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

double sqrt(double num, double epsilon) {
	double next, last;
	last = num;

	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}

	if (num == 0 || num == 1) {
		return num;
	}

	next = (last + num/last)/2;
	while (abs(last - next) >= epsilon) {
        last = next;
		next = (last + num/last) / 2;
	}
	return next;
}

int main(int argc, char* argv[]) {
	double num, epsilon;
	istringstream iss;

	if (argc == 1 || argc > 3) {
		cerr << "Usage: ./sqrt <value> [epsilon]" << endl;
		return 1;
    }

	if (argc == 3) {
        iss.str(argv[2]);
        if (!(iss >> epsilon)) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
		if (epsilon <= 0) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		iss.clear();
		iss.str(argv[1]);
		if (!(iss >> num)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}
		double res = sqrt(num,epsilon);
		cout << fixed << setprecision(8) << res << endl;
		return 0;
	}

	iss.clear();
	iss.str(argv[1]);
	if (!(iss >> num)) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}
    iss >> num;
	double res = sqrt(num, 1e-7);
	cout << fixed << setprecision(8) << res << endl;
	return 0;
}















