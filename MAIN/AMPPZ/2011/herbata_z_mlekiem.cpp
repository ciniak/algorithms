//============================================================================
// Name        : herbata_z_mlekiem.cpp
// Author      : Michal Marcinkowski
// Description : http://main.edu.pl/pl/archive/amppz/2011/her
//============================================================================

#include <cstdio>

using namespace std;

int main() {
	unsigned int numberOfLetters, h, m;
	char c;

	scanf("%d", &numberOfLetters);
	if (numberOfLetters == 1) {
		printf("HM");
		return 0;
	}
	getchar();
	h = m = 0;
	for (int i = 1; i < numberOfLetters; i++) {
		c = getchar();
		if (c == 'H') {
			h++;
		} else if (c == 'M') {
			m++;
		}
	}

	if (h > m) {
		printf("H");
	} else if (m > h) {
		printf("M");
	} else {
		if (c == 'H') {
			printf("M");
		} else {
			printf("H");
		}
	}
	return 0;
}
