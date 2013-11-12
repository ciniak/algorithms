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

int a[101], x[101];
pair<int, pair<int, int> > nwds[100];

bool go(int k, int last) {
	int tmp, mul;
	bool one = false, m = true;
	if (k > 0) {
		printf("k > 0 (%d)\n", k);
		mul = x[k] / (nwds[k - 1].first / last);
		if ((x[k] % (nwds[k - 1].first / last)) != 0) {
			mul = x[k];
			m = false;
		}
		x[k - 1] = nwds[k - 1].second.first * mul;
		x[k] = nwds[k - 1].second.second * mul;
		printf("k -1 = %d (%d), k = %d (%d)\n %d, %d, %d\n", x[k - 1], nwds[k - 1].second.first, x[k], nwds[k - 1].second.second, x[k],
				nwds[k - 1].first, last);
		if (k != 1) {
			printf("k != 1\n");
			if (x[k - 1] <= 0) {
				printf("x[k - 1] <= 0 (%d)\n", x[k - 1]);
				one = true;
				while ((x[k - 1] <= 0) || x[k] < 0) {
					printf("while ((x[k - 1] <= 0) || x[k] < 0) (%d, %d)\n", x[k - 1], x[k]);
					x[k - 1] += a[k] / nwds[k - 1].first;
					x[k] -= (nwds[k - 2].first / nwds[k - 1].first);
					if (x[k] < 0) {
						printf("return false\n");
						return false;
					}
				}
			} else {
				printf("x[k - 1] > 0 (%d)\n", x[k - 1]);
				while ((x[k - 1] <= 0) || x[k] < 0) {
					printf("while ((x[k - 1] <= 0) || x[k] < 0) (%d, %d)\n", x[k - 1], x[k]);
					x[k - 1] -= a[k] / nwds[k - 1].first;
					x[k] += (nwds[k - 2].first / nwds[k - 1].first);
					if (x[k - 1] <= 0) {
						printf("return false\n");
						return false;
					}
				}
			}
			if (one) {
				printf("one = true\n");
				tmp = x[k - 1];
				while (!go(k - 1, nwds[k - 1].first)) {
					tmp += a[k] / nwds[k - 1].first;
					x[k - 1] = tmp;
					x[k] -= (nwds[k - 2].first / nwds[k - 1].first);
					if (x[k] < 0) {
						return false;
					}
				}
			} else {
				tmp = x[k - 1];
				while (!go(k - 1, nwds[k - 1].first)) {
					tmp -= a[k] / nwds[k - 1].first;
					x[k - 1] = tmp;
					x[k] += (nwds[k - 2].first / nwds[k - 1].first);
					if (x[k - 1] <= 0) {
						return false;
					}
				}
			}
			if (m) {
				for (int i = k; i > 0; i--) {
					x[i] *= nwds[i - 1].first / last;
				}
				x[0] *= nwds[1].first / last;
			}
		} else {
			printf("k == 1\n");
			if (x[k - 1] < 0) {
				printf("x[k - 1] < 0 (%d)\n", x[k - 1]);
				while ((x[k - 1] < 0) || x[k] < 0) {
					printf("x[k - 1] < 0) || x[k] < 0 (%d, %d)\n", x[k - 1], x[k]);
					x[k - 1] += a[k] / nwds[k - 1].first;
					x[k] -= (a[k - 1] / nwds[k - 1].first);
					if (x[k] < 0) {
						printf("return false\n");
						return false;
					}
				}
			} else if (x[k] < 0) {
				printf("x[k - 1] < 0 (%d)\n", x[k - 1]);
				while ((x[k - 1] < 0) || x[k] < 0) {
					printf("x[k - 1] < 0) || x[k] < 0 (%d, %d)\n", x[k - 1], x[k]);
					x[k - 1] -= a[k] / nwds[k - 1].first;
					x[k] += (a[k - 1] / nwds[k - 1].first);
					if (x[k - 1] < 0) {
						printf("return false\n");
						return false;
					}
				}
			}
			if (m) {
				x[k - 1] *= nwds[k - 1].first / last;
				x[k] *= nwds[k - 1].first / last;
			}
		}
	}
	return true;
}

int main() {
	int numberOfCases, n, i, b, m;
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
		//calculate a's
		if ((b % nwds[n - 1].first) == 0) {
			bool bad = false;
			// base value (coefficient first) [* search value/nwds[i].first + (a[i + 1] / nwds[i + 1]) = x[i]

			//in this case x = 0 mod y (no solution)

			printf("x1 = %d, x2 = %d\n", nwds[n - 1].second.first, nwds[n - 1].second.second);
			x[n - 1] = nwds[n - 1].second.first * (b / nwds[n - 1].first);
			printf("nwd = %d, a[n] = %d\n", nwds[n - 1].first, a[n]);
			printf("x = %d\n", x[n - 1]);
			while (x[n - 1] <= 0) {
				x[n - 1] += a[n] / nwds[n - 1].first;
				printf("x = %d\n", x[n - 1]);
			}
			printf("N (%d, %d)\n", nwds[n - 1].first, a[n]);
			int tmp = x[n - 1];
			printf("tmp = %d\n", tmp);
			while (!go(n - 1, nwds[n - 1].first)) {
				printf("x[n - 1] = %d --> ", x[n - 1]);
				tmp += a[n] / nwds[n - 1].first;
				x[n - 1] = tmp;
				printf("x[n - 1] = %d\n", x[n - 1]);
				getchar();
			}
			for (i = 0; i < n; i++) {
				printf("x[%d] = %d ", i, x[i]);
			}
			printf("\n");
			int sum = 0;
			for (i = 0; i < n; i++) {
				sum += a[i] * x[i];
			}

			printf("\nresult = %d (%d)\n", sum % a[n], b);

		} else {
			printf("NO\n");
		}
	}
	return 0;
}
