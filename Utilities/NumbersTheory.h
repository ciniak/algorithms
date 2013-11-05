//============================================================================
// Name        : NumbersTheory.h
// Author      : Michal Marcinkowski
// Description : class with algorithms connected with numbers theory
//============================================================================

#include <utility>

using namespace std;

class NumbersTheory {
  public:
	NumbersTheory();
	static int euklidesNwd(int a, int b);
	static int extendedEuklidesNwdWithoutCoefficients(int a, int b);
	static pair<int, pair<int, int> > extendedEuklidesNwd(int a, int b);
};
