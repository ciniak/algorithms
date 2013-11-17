//============================================================================
// Name        : dpeqn.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/DPEQN
//============================================================================

#include <stdexcept>
#include <cstdio>
#include <cstring>
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

int n, a[101], ma[101];
long x[101];
pair<int, pair<int, int> > nwds[100];

int main() {
	int numberOfCases, i, b, s, reduced, k, rest;
	long tmp;
	scanf("%d", &numberOfCases);
	while (numberOfCases--) {
		memset(x, 0, sizeof(x));
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		// a[n] = m (modulo value), b = reszta
		scanf("%d %d", &b, &a[n]);
		//calculate nwd and coefficients
		if (n > 1) {
			ma[0] = a[0] % a[n];
			ma[1] = a[1] % a[n];
			nwds[0] = extendedEuklidesNwd(ma[0], ma[1]);
			for (i = 2; i < n; i++) {
				ma[i] = a[i] % a[n];
				nwds[i - 1] = extendedEuklidesNwd(nwds[i - 2].first, ma[i]);
			}
			nwds[n - 1] = extendedEuklidesNwd(nwds[i - 2].first, a[n]);
		} else {
			ma[n - 1] = a[n - 1] % a[n];
			nwds[n - 1] = extendedEuklidesNwd(ma[n - 1], a[n]);
		}
		b %= a[n];
		if ((b % nwds[n - 1].first) == 0) {

			k = n - 1;
			rest = b;

			while (rest != 0) {
				if (k > 1) {
					if (rest % ma[k] == 0) {
						x[k] += rest / ma[k];
						break;
					} else if (rest % nwds[k - 2].first == 0) {
						k--;
						continue;
					} else {
						rest -= ma[k];
						x[k]++;
						if (rest < 0) {
							rest += a[n];
						}
					}
				} else if (k == 1) {
					if (rest % ma[k] == 0) {
						x[k] += rest / ma[k];
						break;
					} else if (rest % ma[k - 1] == 0) {
						x[k - 1] += rest / ma[k - 1];
						break;
					} else {
						rest -= ma[k];
						x[k]++;
						if (rest < 0) {
							rest += a[n];
						}
					}
				} else if (k == 0) {
					if (rest % ma[k] == 0) {
						x[k] += rest / ma[k];
						break;
					} else {
						rest -= ma[k];
						x[k]++;
						if (rest < 0) {
							rest += a[n];
						}
					}
				}

			}

			for (i = 0; i < n; i++) {
				printf("%ld ", x[i]);
			}
			printf("\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
