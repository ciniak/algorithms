//============================================================================
// Name        : biorhytms.cpp
// Author      : Michal Marcinkowski
// Description : http://uva.onlinejudge.org - problem 756 - Biorhytms
//============================================================================

#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
	int p, e, i, d, result, rPE, k;
	int cAlfaPEI = 2, iP = 33, pPeP = 644, pPePiP = 21252, caseNumber = 1;
	scanf("%d %d %i %d", &p, &e, &i, &d);
	while ((p != -1) || (e != -1) || (i != -1) || (d != -1)) {
		rPE = ((p * -252) + (e * 253));
		result = 0;
		k = 0;
		while (result <= d) {
			result = (pPeP * ((k++ * iP) - (rPE * cAlfaPEI) + (i * cAlfaPEI))) + rPE;
			if (result < 0) {
				result *= -1;
				if (result >= pPePiP) {
					result %= pPePiP;
				}
				result = pPePiP - result;
			}
		}
		result -= d;
		if (result > pPePiP) {
			result %= pPePiP;
		}
		if (result == 0) {
			result = pPePiP;
		}
		printf("Case %d: the next triple peak occurs in %d days.\n", caseNumber, result);
		caseNumber++;
		scanf("%d %d %i %d", &p, &e, &i, &d);
	}
}
