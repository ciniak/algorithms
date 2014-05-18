//============================================================================
// Name        : generator_bitow.cpp
// Author      : Michal Marcinkowski
// Description : http://main.edu.pl/pl/archive/amppz/2011/gen
//				 Only partially working solution.
//============================================================================

#include <iostream>
#include <cstdio>

using namespace std;

int nextSeed[1000000], bit[1000000];

int main() {
	int a, c, k, m, n, z, i, j;
	string text;

	scanf("%d %d %d %d %d\n", &a, &c, &k, &m, &n);
	getline(cin, text);

	int ak = a / k;
	int amk = a % k;
	int ck = c / k;
	int cmk = c % k;
	int akmm = ak % m;
	int ckmm = ck % m;

	int azmk = 0;
	int sec = (azmk + cmk) / k;
	int azkm = 0;
	for (i = 0; i < m; i++) {
		nextSeed[i] = (azkm + ckmm + sec) % m;
		bit[i] = (nextSeed[i] < (m / 2)) ? '0' : '1';
		azkm = (azkm + akmm) % m;
		azmk = (azmk + amk);
		azkm += azmk / k;
		azmk %= k;
		sec = (azmk + cmk) / k;
	}

	int count = 0;
	int seed, pos;
	bool yes;
	for (i = 0; i < m; i++) {
		if (bit[i] == text[0]) {
			seed = nextSeed[i];
			pos = 1;
			yes = true;
			while (true) {
				if (seed == nextSeed[seed]) {
					for (j = pos; j < n; j++) {
						if (bit[seed] != text[j]) {
							yes = false;
							break;
						}
					}
					break;
				}
				if (n <= pos) {
					break;
				}
				if (bit[seed] != text[pos]) {
					yes = false;
					break;
				}
				pos++;
				seed = nextSeed[seed];
			}
			if (yes) {
				count++;
			}
		}
	}
	printf("%d", count);
	return 0;
}
