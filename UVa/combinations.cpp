//============================================================================
// Name        : combinations.cpp
// Author      : Michal Marcinkowski
// Description : http://uva.onlinejudge.org - problem 369 - Combinations
//============================================================================

#include <cstdio>
#include <cstdlib>

using namespace std;

int euklides(int a, int b) {
	int i, q, r, nwd, tmp;
	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	q = a / b;
	r = a - (q * b);
	nwd = b;
	if (r != 0) {
		a = b;
		b = r;
		nwd = r;
		q = a / b;
		r = a - (q * b);
		while (r != 0) {
			a = b;
			b = r;
			nwd = r;
			q = a / b;
			r = a - (q * b);
		}
	}
	return nwd;
}

int main() {
	int n, m, nwd, diff, result, i, j, up, down, toUp, toDown;
	scanf("%d %d", &n, &m);
	while ((n != 0) || (m != 0)) {
		diff = n - m;
		if (diff != 0) {
			up = down = 1;
			if (diff > m) {
				j = m;
			} else {
				j = diff;
			}
			for (i = n; j > 0; i--, j--) {
				nwd = euklides(i, j);
				toUp = i / nwd;
				toDown = j / nwd;
				nwd = euklides(up, toDown);
				up = up / nwd;
				toDown = toDown / nwd;
				nwd = euklides(down, toUp);
				down = down / nwd;
				toUp = toUp / nwd;
				up *= toUp;
				down *= toDown;
			}
			result = up / down;
		} else {
			result = 1;
		}
		printf("%d things taken %d at a time is %d exactly.\n", n, m, result);
		scanf("%d %d", &n, &m);
	}
}
