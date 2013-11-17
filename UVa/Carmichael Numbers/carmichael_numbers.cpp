//============================================================================
// Name        : carmichael_numbers.cpp
// Author      : Michal Marcinkowski
// Description : http://uva.onlinejudge.org - problem 10006 - Carmichael Numbers
//============================================================================

#include <cstdio>
#include <cstring>
#include <limits>

const int MAX = 65000;
bool primeTable[MAX + 1];

void makePrimeTable() {
	for (int i = 2; i * i <= MAX; ++i) {
		if (primeTable[i]) {
			continue;
		}
		for (int j = 2 * i; j <= MAX; j += i) {
			primeTable[j] = true;
		}
	}
}

const unsigned int MAX_BITS = 16;

int main() {
	unsigned int a, n, x, mask, i, bitsNum, result, one = 1;
	char binaryN[MAX_BITS];
	bool notC;

	memset(binaryN, 0, (MAX_BITS) * sizeof(binaryN[0]));
	memset(primeTable, 0, (MAX + 1) * sizeof(primeTable[0]));
	makePrimeTable();

	scanf("%u", &n);
	while (n != 0) {
		notC = false;
		//if is prime it is not carmichael number
		if (!primeTable[n]) {
			printf("%u is normal.\n", n);
			scanf("%u", &n);
			continue;
		}
		mask = n;
		bitsNum = 0;
		for (i = 0; i < MAX_BITS; i++) {
			if ((mask & one) >= 1) {
				binaryN[i] = 1;
				bitsNum = i + 1;
			} else {
				binaryN[i] = 0;
			}
			mask >>= 1;
		}
		a = 2;
		while (a < n) {
			result = 1;
			x = a;
			for (i = 0; i <= bitsNum; i++) {
				if(binaryN[i]) {
					result *= x;
					result %= n;
				}
				x *= x;
				x %= n;
			}
			if (result != a) {
				notC = true;
				break;
			}
			a++;
		}
		if (!notC) {
			printf("The number %u is a Carmichael number.\n", n);
		} else {
			printf("%u is normal.\n", n);
		}
		scanf("%u", &n);
	}
	return 0;
}
