/*
 * NumbersTheoryTest.cpp
 *
 *  Created on: 5 lis 2013
 *      Author: marcinkowskim
 */

#include "NumbersTheory.h"

#include <iostream>

int main(void) {
	int a = 10;
	int b = 13;
	cout << NumbersTheory::euklidesNwd(a, b) << "\n";
	cout << NumbersTheory::extendedEuklidesNwdWithoutCoefficients(a, b) << "\n";
	pair<int, pair<int, int> > extEuk = NumbersTheory::extendedEuklidesNwd(a, b);
	cout << extEuk.first << "\n";
	cout << extEuk.second.first << " " << extEuk.second.second << "\n";
	return 0;
}
