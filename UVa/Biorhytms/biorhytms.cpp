//============================================================================
// Name        : biorhytms.cpp
// Author      : Michal Marcinkowski
// Description : http://uva.onlinejudge.org - problem 756 - Biorhytms
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <utility>

using namespace std;

template<class T>
class ConstantSizeList {
public:
	ConstantSizeList(const int& pSize) {
		maxSize = pSize;
		list = new T[maxSize];
		insertIndex = 0;
		firstValueIndex = 0;
		size = 0;
	}

	void pushFront(const T& x) {
		list[insertIndex] = x;
		firstValueIndex = insertIndex++;
		if (insertIndex >= maxSize) {
			insertIndex %= maxSize;
		}
		if (size != maxSize) {
			size++;
		}
	}

	T& operator[](size_t pIndex) {
		int index;
		if (pIndex < size) {
			index = (firstValueIndex - pIndex);
			if (index < 0) {
				index += maxSize;
			}
			return list[index];
		}
		return list[0];
	}

	const T& operator[](size_t pIndex) const {
		int index;
		if (pIndex < size) {
			index = (firstValueIndex - pIndex);
			if (index < 0) {
				index += maxSize;
			}
			return list[index];
		}
		return list[0];
	}

	~ConstantSizeList() {
		delete[] list;
	}

private:
	T* list;
	size_t maxSize, size, insertIndex, firstValueIndex;
};

pair<int, pair<int, int> > extendedEuklidesNwd(int a, int b) {
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

int main() {
	int p, e, i, d, result, caseNumber = 1, rPE, rPEI, cAlfaPE, cBetaPE, cAlfaPEI, cBetaPEI, k;
	int pP = 23, eP = 28, iP = 33;
	pair<int, pair<int, int> > nwd = extendedEuklidesNwd(pP, eP);
	cAlfaPE = nwd.second.first;
	cBetaPE = nwd.second.second;
	nwd = extendedEuklidesNwd(pP * eP, iP);
	cAlfaPEI = nwd.second.first;
	cBetaPEI = nwd.second.second;
	scanf("%d %d %i %d", &p, &e, &i, &d);
	while ((p != -1) || (e != -1) || (i != -1) || (d != -1)) {
		p %= pP;
		e %= eP;
		i %= iP;
		rPE = ((p * cBetaPE * eP) + (e * cAlfaPE * pP));
		result = -1;
		k = 0;
		while (result <= d) {
			result = ((pP * eP) * ((k++ * iP) - (rPE * cAlfaPEI) + (i * cAlfaPEI))) + rPE;
			if (result < 0) {
				result *= -1;
				if (result >= ((pP * eP) * iP)) {
					result = result % ((pP * eP) * iP);
				}
				result = ((pP * eP) * iP) - result;
			} else if (result > ((pP * eP) * iP)) {
				result %= ((pP * eP) * iP);
			}
		}

		result -= d;
		printf("Case %d: the next triple peak occurs in %d days.\n", caseNumber, result);
		caseNumber++;
		scanf("%d %d %i %d", &p, &e, &i, &d);
	}
}
