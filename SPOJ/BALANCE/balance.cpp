//============================================================================
// Name        : balance.cpp
// Author      : Michal Marcinkowski
// Description : pl.spoj.com/problems/BALANCE
//============================================================================

#include <stdexcept>
#include <cstdio>
#include <cstdlib>

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
		throw new out_of_range("Index out of range!");
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
		throw new out_of_range("Index out of range!");
	}

	~ConstantSizeList() {
		delete[] list;
	}

private:
	T* list;
	size_t maxSize, size, insertIndex, firstValueIndex;
};

int main() {
	int a, b, d, i, originalA, originalB, firstSum, firstX, firstY, tmpX, tmpY, nwd, m, q, r, tmp, xM, yM, sum, nextSum, goodSum, xMNext,
			yMNext, goodX, goodY, aNwd, bNwd, one, two;
	bool changed;
	ConstantSizeList<int> x(3);
	ConstantSizeList<int> y(3);
	scanf("%d %d %d", &a, &b, &d);
	while ((a != 0) || (b != 0) || (d != 0)) {
		changed = false;
		if (a < b) {
			tmp = a;
			a = b;
			b = tmp;
			changed = true;
		}
		originalA = a;
		originalB = b;
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
		xM = x[0];
		yM = y[0];
		if ((d % nwd) == 0) {
			m = d / nwd;
			xM = xM * m;
			yM = yM * m;
			bNwd = (originalB / nwd);
			aNwd = (originalA / nwd);
			one = (xM / ((-1) * bNwd));
			two = (yM / aNwd);
			firstX = abs(xM + (one * bNwd));
			firstY = abs(yM + (one * aNwd));
			firstSum = firstX + firstY;
			goodX = firstX;
			goodY = firstY;
			goodSum = firstSum;
			nextSum = 0;
			for (i = one + 1; nextSum <= goodSum; i++) {
				xMNext = abs(xM + (i * bNwd));
				yMNext = abs(yM - (i * aNwd));
				nextSum = yMNext + xMNext;
				if (nextSum < goodSum) {
					goodSum = nextSum;
					goodX = xMNext;
					goodY = yMNext;
				}
			}
			sum = firstSum;
			nextSum = 0;
			for (i = one - 1; nextSum <= sum; i--) {
				xMNext = abs(xM + (i * bNwd));
				yMNext = abs(yM - (i * aNwd));
				nextSum = yMNext + xMNext;
				if (nextSum < sum) {
					sum = nextSum;
					tmpX = xMNext;
					tmpY = yMNext;
				}
			}
			if (sum < goodSum) {
				goodX = tmpX;
				goodY = tmpY;
				goodSum = sum;
			}

			tmpX = abs(xM + (two * bNwd));
			tmpY = abs(yM - (two * aNwd));
			firstSum = tmpX + tmpY;
			sum = firstSum;
			if (sum < goodSum) {
				goodX = tmpX;
				goodY = tmpY;
				goodSum = sum;
			}
			nextSum = 0;
			for (i = two + 1; nextSum <= sum; i++) {
				xMNext = abs(xM + (i * bNwd));
				yMNext = abs(yM - (i * aNwd));
				nextSum = yMNext + xMNext;
				if (nextSum < sum) {
					sum = nextSum;
					tmpX = xMNext;
					tmpY = yMNext;
				}
			}
			if (sum < goodSum) {
				goodX = tmpX;
				goodY = tmpY;
				goodSum = sum;
			}
			sum = firstSum;
			nextSum = 0;
			for (i = two - 1; nextSum <= sum; i--) {
				xMNext = abs(xM + (i * bNwd));
				yMNext = abs(yM - (i * aNwd));
				nextSum = yMNext + xMNext;
				if (nextSum < sum) {
					sum = nextSum;
					tmpX = xMNext;
					tmpY = yMNext;
				}
			}
			if (sum < goodSum) {
				goodX = tmpX;
				goodY = tmpY;
				goodSum = sum;
			}

			if (changed) {
				tmp = goodX;
				goodX = goodY;
				goodY = tmp;
			}
			printf("%d %d\n", goodX, goodY);
		} else {
			printf("BRAK\n");
		}
		scanf("%d %d %d", &a, &b, &d);
	}

}

