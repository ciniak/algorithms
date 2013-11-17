//============================================================================
// Name        : irreducable_basic_fractions.cpp
// Author      : Michal Marcinkowski
// Description : http://uva.onlinejudge.org - problem 10179 - Irreducable Basic Fractions
//============================================================================

#include<cstdio>
#include<vector>

using namespace std;

const int SIZE = 31623;
int correspondingPrimes[SIZE + 1];
vector<int> primes;

void calculatePrimes() {
	for (int i = 2; i <= SIZE; i++) {
		correspondingPrimes[i] = i;
	}
	for (int i = 2; i * i <= SIZE; i++) {
		if (correspondingPrimes[i] == i) {
			for (int j = i * i; j <= SIZE; j = j + i) {
				if (correspondingPrimes[j] == j) {
					correspondingPrimes[j] = i;
				}
			}
		}
	}
	for (int p = 2; p <= SIZE; p++) {
		if (correspondingPrimes[p] == p) {
			primes.push_back(p);
		}
	}
}

int phi_tab[SIZE + 1];

int phi(int n) {
	int prime, q, qq, nn = n, result = 1;
	if (n <= 1) {
		return n;
	}
	if (n == 2) {
		return 1;
	}
	if (nn < SIZE && phi_tab[nn]) {
		return phi_tab[nn];
	}
	int i = 0;
	while (n > 1) {
		if (n <= SIZE) {
			prime = correspondingPrimes[n];
		}
		else {
			while (i < primes.size() && n % (p = primes[i]) != 0) {
				i++;
			}
			if (i == primes.size()) {
				prime = n;
			}
		}
		q = 1, qq = prime;
		n /= prime;
		while (n % primep == 0) {
			q = qq;
			qq = qq * prime;
			n = n / prime;
		}
		result *= qq - q;
	}
	if (nn < SIZE) {
		phi_tab[nn] = result;
	}
	return result;
}

int main(void) {
	calculatePrimes();
	int a;
	scanf("%d", &a);
	while (a != 0) {
		printf("%d\n", phi(a));
		scanf("%d", &a);
	}
	return 0;
}
