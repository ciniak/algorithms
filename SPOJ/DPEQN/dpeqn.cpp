//============================================================================
// Name        : dpeqn.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/DPEQN
//============================================================================

#include <stdexcept>
#include <cstdio>
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

int n, a[101];
long x[101];
pair<int, pair<int, int> > nwds[100];

bool go(int k, int last) {
	long tmp, mul, s;
	int reducedA, reducedB, i, div, redB;
	bool one = false, m = true;
	if (k > 0) {
		div = nwds[k - 1].first / last;
		mul = x[k] / div;
		if ((x[k] % div) != 0) {
			mul = x[k];
			m = false;
		}
		x[k - 1] = nwds[k - 1].second.first;
		x[k] = nwds[k - 1].second.second;
		if (k > 1) {
			reducedA = a[k] / nwds[k - 1].first;
			reducedB = nwds[k - 2].first / nwds[k - 1].first;
			if (x[k - 1] <= 0) {
				s = ((-1) * x[k - 1]) / reducedA;
				x[k - 1] += reducedA * s;
				x[k] -= reducedB * s;
				one = true;
				while ((x[k - 1] < 0) || x[k] < 0) {
					x[k - 1] += reducedA;
					x[k] -= reducedB;
					if (x[k] < 0) {
						return false;
					}
				}
				x[k - 1] *= mul;
				x[k] += mul;
			} else {
				s = ((-1) * x[k]) / reducedB;
				x[k - 1] += reducedA * s;
				x[k] -= reducedB * s;
				printf("%ld, %ld\n", x[k - 1], x[k]);
				while ((x[k - 1] < 0) || x[k] < 0) {
					x[k - 1] -= reducedA;
					x[k] += reducedB;
					if (x[k - 1] < 0) {
						return false;
					}
				}
				x[k - 1] *= mul;
				x[k] += mul;
			}
			if (x[k - 1] != 0) {
				if (one) {
					tmp = x[k - 1];
					while (!go(k - 1, nwds[k - 1].first)) {
						tmp += reducedA;
						x[k - 1] = tmp;
						x[k] -= reducedB;
						if (x[k] < 0) {
							return false;
						}
					}
				} else {
					tmp = x[k - 1];
					while (!go(k - 1, nwds[k - 1].first)) {
						tmp -= reducedA;
						x[k - 1] = tmp;
						x[k] += reducedB;
						if (x[k - 1] < 0) {
							return false;
						}
					}
				}
				if ((x[k - 1] >= a[n]) || (x[k] >= a[n])) {
					return false;
				}
				if (m) {
					x[k] *= div;
					x[k - 1] *= div;
					if ((x[k - 1] >= a[n]) || (x[k] >= a[n])) {
						return false;
					}
					for (i = k - 2; i > 0; i--) {
						x[i] *= div;
					}
					x[0] *= div;
				}
			} else {
				if (m) {
					x[k] *= div;
				}
				if (x[k] >= a[n]) {
					return false;
				}
				for (i = k - 2; i >= 0; i--) {
					x[i] = 0;
				}
			}
		} else {
			reducedA = a[k] / nwds[k - 1].first;
			redB = (a[k - 1] / nwds[k - 1].first);
			if (x[k - 1] < 0) {
				s = ((-1) * x[k - 1]) / reducedA;
				x[k - 1] += reducedA * s;
				x[k] -= redB * s;
				while ((x[k - 1] < 0) || x[k] < 0) {
					x[k - 1] += reducedA;
					x[k] -= redB;
					if (x[k] < 0) {
						return false;
					}
				}
			} else if (x[k] < 0) {
				s = ((-1) * x[k]) / redB;
				x[k - 1] -= reducedA * s;
				x[k] += redB * s;
				while ((x[k - 1] < 0) || x[k] < 0) {
					x[k - 1] -= reducedA;
					x[k] += redB;
					if (x[k - 1] < 0) {
						return false;
					}
				}
			}
			x[k - 1] *= mul;
			x[k] += mul;
			if ((x[k - 1] >= a[n]) || (x[k] >= a[n])) {
				return false;
			}
			if (m) {
				x[k - 1] *= div;
				x[k] *= div;
				if ((x[k - 1] >= a[n]) || (x[k] >= a[n])) {
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
	int numberOfCases, i, b, s, reduced;
	long tmp;
	scanf("%d", &numberOfCases);
	while (numberOfCases--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		// a[n] = m (modulo value), b = reszta
		scanf("%d %d", &b, &a[n]);
		//calculate nwd and coefficients
		if (n > 1) {
			nwds[0] = extendedEuklidesNwd(a[0], a[1]);
			for (i = 2; i < n; i++) {
				nwds[i - 1] = extendedEuklidesNwd(nwds[i - 2].first, a[i]);
			}
			nwds[n - 1] = extendedEuklidesNwd(nwds[i - 2].first, a[n]);
		} else {
			nwds[n - 1] = extendedEuklidesNwd(a[n - 1], a[n]);
		}

		if ((b % nwds[n - 1].first) == 0) {
			x[n - 1] = nwds[n - 1].second.first * (b / nwds[n - 1].first);

			reduced = a[n] / nwds[n - 1].first;
			s = ((-1) * x[n - 1]) / reduced;
			x[n - 1] += reduced * s;
			while (x[n - 1] < 0) {
				x[n - 1] += reduced;
			}

			tmp = x[n - 1];
			while (!go(n - 1, nwds[n - 1].first)) {
				tmp += reduced;
				x[n - 1] = tmp;
				if (x[n - 1] > a[n]) {
					printf("err");
					break;
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
