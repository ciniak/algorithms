//============================================================================
// Name        : NumbersTheory.cpp
// Author      : Michal Marcinkowski
// Description : class with algorithms connected with numbers theory
//============================================================================

#include "NumbersTheory.h"
#include "ConstantSizeList.h"

int NumbersTheory::euklidesNwd(int a, int b) {
	while (a != b) {
		if (a < b) {
			b = b - a;
		} else {
			a = a - b;
		}
	}
	return a;
}

int NumbersTheory::extendedEuklidesNwdWithoutCoefficients(int a, int b) {
	int q, r, nwd, tmp;
	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	q = a / b;
	r = a - (q * b);
	nwd = b;
	while (r != 0) {
		a = b;
		b = r;
		nwd = r;
		q = a / b;
		r = a - (q * b);
	}
	return nwd;
}

pair<int, pair<int, int> > NumbersTheory::extendedEuklidesNwd(int a, int b) {
	int q, r, nwd, tmp, xM, yM;
	bool changed;
	ConstantSizeList<int> x(3);
	ConstantSizeList<int> y(3);
	changed = false;
	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
		changed = true;
	}
	q = a / b;
	r = a - (q * b);
	nwd = b;
	x.pushFront(1);
	x.pushFront(0);
	x.pushFront(1);
	y.pushFront(0);
	y.pushFront(1);
	y.pushFront(1 - q);
	if (r != 0) {
		a = b;
		b = r;
		x[0] = x[2] - (q * x[1]);
		y[0] = y[2] - (q * y[1]);
		nwd = r;
		q = a / b;
		r = a - (q * b);
		while (r != 0) {
			a = b;
			b = r;
			x.pushFront(x[1] - (q * x[0]));
			y.pushFront(y[1] - (q * y[0]));
			nwd = r;
			q = a / b;
			r = a - (q * b);
		}
	}
	if (!changed) {
		xM = x[0];
		yM = y[0];
	} else {
		xM = y[0];
		yM = x[0];
	}
	return make_pair(nwd, make_pair(xM, yM));
}

