//============================================================================
// Name        : nwd.cpp
// Author      : Michal Marcinkowski
// Description : http://main.edu.pl/ -> Kursy -> Algorytmika -> Zadania -> NWD
//============================================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

class BigInt {
private:
	static const int BASE = 1000000000;
	static const int DIGS = 9;
	static const int LEN = 1000;

public:
	int number[LEN];
	int length;

	BigInt() {
		number[0] = 0;
		length = 1;
	}

	BigInt(const BigInt& b) {
		this->length = b.length;
		for (int i = 0; i < b.length; i++) {
			this->number[i] = b.number[i];
		}
	}

	//only for BASE = 1000000000
	BigInt(int num) {
		this->number[0] = num % BASE;
		this->number[1] = num / BASE;
		this->length = (this->number[1] == 0) ? 1 : 2;
	}

	BigInt operator +(const BigInt& addend) const {
		BigInt result;
		const BigInt& bigger = (this->length < addend.length) ? addend : *this;
		result.length = min(this->length, addend.length);
		int c = 0;
		//sum two numbers
		for (int i = 0; i < result.length; i++) {
			result.number[i] = (this->number[i] + addend.number[i] + c) % BASE;
			c = (this->number[i] + addend.number[i] + c) / BASE;
		}
		//go until end of bigger number
		while (result.length < bigger.length) {
			result.number[result.length] = (bigger.number[result.length] + c) % BASE;
			c = (bigger.number[result.length] + c) / BASE;
			result.length++;
		}
		//if is carry, add it to number
		if (c > 0) {
			result.number[result.length] = c;
			result.length++;
		}
		return result;
	}

	BigInt operator +=(BigInt addend) {
		return *this = *this + addend;
	}

	BigInt operator -(const BigInt& subtrahend) const {
		assert(*this >= subtrahend);
		BigInt result;
		result.length = this->length;
		int i, c = 0;
		//substract numbers
		for (i = 0; i < subtrahend.length; i++) {
			if ((this->number[i] + c) < subtrahend.number[i]) {
				result.number[i] = (this->number[i] + c) + (BASE - subtrahend.number[i]);
				c = -1;
			} else {
				result.number[i] = (this->number[i] + c) - subtrahend.number[i];
				c = 0;
			}
		}
		//rewrite rest of the number
		for (; i < this->length; i++) {
			if ((this->number[i] + c) < 0) {
				result.number[i] = this->number[i] + c + BASE;
				c = -1;
			} else {
				result.number[i] = this->number[i] + c;
				c = 0;
			}
		}
		//remove leading 0's
		while ((--i > 0) && (result.number[i] == 0)) {
			result.length--;
		}

		return result;
	}

	BigInt operator *(int multiplier) const {
		BigInt result;
		if (multiplier == 0) {
			return result;
		} else if (multiplier == 1) {
			return (result = *this);
		}
		result.length = this->length;
		int c = 0;
		for (int i = 0; i < this->length; i++) {
			result.number[i] = int(((long long) (this->number[i]) * multiplier + c) % BASE);
			c = int(((long long) (this->number[i]) * multiplier + c) / BASE);
		}

		while (c > 0) {
			result.number[result.length++] = c % BASE;
			c /= BASE;
		}

		while (result.length > 1 && result.number[result.length - 1] == 0) {
			result.length--;
		}

		return result;
	}

	BigInt operator *(const BigInt multiplier) const {
		BigInt result;
		if (multiplier == 0) {
			return result;
		} else if (multiplier == 1) {
			return (result = *this);
		}

		for (int i = 0; i < multiplier.length; i++) {
			BigInt tmp(*this * multiplier.number[i]);

			for (int j = tmp.length - 1; j >= 0; j--) {
				tmp.number[j + i] = tmp.number[j];
			}

			for (int j = 0; j < i; j++) {
				tmp.number[j] = 0;
			}
			tmp.length += i;
			result += tmp;
		}

		while (result.length > 1 && result.number[result.length - 1] == 0) {
			result.length--;
		}
		return result;
	}

	BigInt operator /(const BigInt divisor) const {
		assert(divisor > 0);
		BigInt tmp, result;
		if (*this < divisor) {
			return result;
		} else if (*this == divisor) {
			return 1;
		}

		tmp.length = divisor.length;
		for (int i = 0; i < tmp.length; i++) {
			tmp.number[tmp.length - 1 - i] = this->number[this->length - 1 - i];
		}
		int i = this->length - divisor.length;
		result.length = i + 1;
		while (i >= 0) {
			int a = 0, b = BASE - 1;
			if ((tmp != 0) && (divisor <= tmp)) {
				while (a < b) {
					int c = (a + b) / 2 + 1;
					if (divisor * c > tmp) {
						b = c - 1;
					} else {
						a = c;
					}
				}
			}
			result.number[i] = a;

			tmp = tmp - (divisor * a);
			for (int j = tmp.length - 1; j >= 0; j--) {
				tmp.number[j + 1] = tmp.number[j];
			}
			tmp.length++;
			i--;
			if (i >= 0) {
				tmp.number[0] = this->number[i];
			}
			//remove leading 0's
			while (tmp.length > 1 && tmp.number[tmp.length - 1] == 0) {
				tmp.length--;
			}
		}

		while (result.length > 1 && result.number[result.length - 1] == 0) {
			result.length--;
		}
		return result;
	}

	bool operator <(const BigInt& b) const {
		if (this->length != b.length) {
			return this->length < b.length;
		}
		int i = this->length - 1;
		while ((i > 0) && (this->number[i] == b.number[i])) {
			i--;
		}
		return this->number[i] < b.number[i];
	}

	bool operator >(const BigInt& b) const {
		return b < *this;
	}

	bool operator ==(const BigInt& b) const {
		if (this->length == b.length) {
			for (int i = this->length - 1; i >= 0; i--) {
				if (this->number[i] != b.number[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool operator !=(int num) {
		return !(*this == BigInt(num));
	}

	bool operator >=(const BigInt& b) const {
		return !(*this < b);
	}

	bool operator <=(const BigInt& b) const {
		return !(b < *this);
	}

	void print() const {
		printf("%d", this->number[this->length - 1]);
		for (int i = this->length - 2; i >= 0; i--) {
			printf("%0*d", DIGS, this->number[i]);
		}
		printf("\n");
	}

	void readNumber() {
		char charNumber[LEN * DIGS + 1];
		scanf("%s", charNumber);
		int charNumberLength = strlen(charNumber);

		if (charNumberLength % DIGS == 0) {
			this->length = charNumberLength / DIGS;
		} else {
			this->length = charNumberLength / DIGS + 1;
		}

		for (int i = 0; i < this->length; i++) {
			this->number[i] = 0;

			for (int j = max(0, charNumberLength - DIGS); j < charNumberLength; j++) {
				this->number[i] = 10 * this->number[i] + (charNumber[j] - '0');
			}
			charNumberLength -= DIGS;
		}
	}

};

BigInt myNwd(BigInt a, BigInt b) {
	BigInt q, r, tmp, nwd;
	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	q = a / b;
	r = a - (q * b);
	nwd = b;
	while (r != 0) {
		a = b;
		b = r;
		nwd = r;
		q = a / b;
		r = a - (q * b);
	}
	return nwd;
}

int main() {
	BigInt a, b;
	a.readNumber();
	b.readNumber();

	BigInt r = myNwd(a, b);
	r.print();

	return 0;
}

