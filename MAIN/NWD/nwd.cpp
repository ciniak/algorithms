//============================================================================
// Name        : julka.cpp
// Author      : Michal Marcinkowski
// Description :
//============================================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>

using namespace std;

class BigInt {
public:
	string n;

	BigInt(string num = "0") {
		n = num;
		reverse(n.begin(), n.end());
	}

	BigInt(long long num) {
		n = num ? "" : "0";
		while (num) {
			n += num % 10 + '0';
			num /= 10;
		}
	}

	BigInt operator +(BigInt addend) {
		BigInt result;
		result.n = n;
		int c, i, l1 = result.n.size(), l2 = addend.n.size();
		for (i = l1; i < l2; ++i)
			result.n += '0';
		for (i = l2; i < l1; ++i)
			addend.n += '0';
		for (c = i = 0; i < l1 || i < l2; ++i) {
			result.n[i] = ((c = result.n[i] - '0' + addend.n[i] - '0' + c) % 10) + '0';
			c /= 10;
		}
		if (c)
			result.n += c + '0', ++i;
		addend.n = addend.n.substr(0, l2);
		return result;
	}

	BigInt operator +=(BigInt addend) {
		return *this = *this + addend;
	}

	BigInt operator +(long long addend) {
		return *this + BigInt(addend);
	}

	BigInt operator +=(long long addend) {
		return *this = *this + BigInt(addend);
	}

	BigInt operator -(BigInt subtrahend) {
		BigInt result;
		if (*this == subtrahend)
			return BigInt("0");
		if (*this < subtrahend) {
			return BigInt("0");
		}
		assert(*this >= subtrahend);
		int i, l1 = n.size(), l2 = subtrahend.n.size();
		for (i = 0; i < l2; ++i)
			subtrahend.n[i] = '9' - subtrahend.n[i] + '0';
		for (i = l2; i < l1; ++i)
			subtrahend.n += '9';
		result = *this + subtrahend;
		l1 = result.n.size();
		result.n[l1 - 1]--;
		result += 1;
		result.trim();
		for (i = 0; i < l2; ++i)
			subtrahend.n[i] = '9' - subtrahend.n[i] + '0';
		subtrahend.n = subtrahend.n.substr(0, l2);
		return result;
	}

	BigInt operator -=(BigInt subtrahend) {
		return *this = *this - subtrahend;
	}

	BigInt operator -(long long subtrahend) {
		return *this - BigInt(subtrahend);
	}

	BigInt operator -=(long long subtrahend) {
		return *this = *this - BigInt(subtrahend);
	}

	BigInt operator *(BigInt multiplier) {
		BigInt result, s;
		int c, i, j, l1 = n.size(), l2 = multiplier.n.size();
		for (i = 0; i < l1; ++i) {
			s.n = string(i, '0');
			for (c = j = 0; j < l2; ++j) {
				s.n += (c = (n[i] - '0') * (multiplier.n[j] - '0') + c) % 10 + '0';
				c /= 10;
			}
			while (c)
				s.n += ((c % 10) + '0'), c /= 10;
			result = result + s;
		}
		result.trim();
		return result;
	}

	BigInt operator *=(BigInt multiplier) {
		return *this = *this * multiplier;
	}

	BigInt operator *(long long multiplier) {
		return *this * BigInt(multiplier);
	}

	BigInt operator *=(long long multiplier) {
		return *this = *this * BigInt(multiplier);
	}

	BigInt operator >>(int x) {
		BigInt r = *this;
		reverse(r.n.begin(), r.n.end());
		for (int i = 0; i < x; ++i) {
			string result = "";
			int d = 0, sz = r.n.size();
			for (int i = 0; i < sz; ++i) {
				d = d * 10 + r.n[i] - '0';
				result += (d >> 1) + '0';
				d &= 1;
			}
			r.n = result;
		}
		reverse(r.n.begin(), r.n.end());
		r.trim();
		return r;
	}

	BigInt operator /(BigInt divisor) {
		int l1, l2, diff;
		BigInt tmp, result;
		l1 = this->n.size();
		l2 = divisor.n.size();
		diff = l1 - l2;
		if (diff < 0) {
			return BigInt("0");
		}
		result.n.resize(diff + 1);
		//do not append, reserve!
		for (int i = l2; i > 0; i--) {
			tmp.n += this->n[l1 - i];
		}
		tmp.n = tmp.n.substr(1, tmp.n.size() - 1);
		while (diff >= 0) {
			int a = 0, b = 9;
			while (a < b) {
				int c = ((a + b) / 2) + 1;
				if ((divisor * c) > tmp) {
					b = c - 1;
				} else {
					a = c;
				}
			}
			result.n[diff] = a + '0';
			tmp = tmp - (divisor * a);
			tmp.n.resize(tmp.n.size() + 1);
			for (int i = tmp.n.size() - 1; i >= 0; i--) {
				tmp.n[i + 1] = tmp.n[i];
			}
			if (--diff >= 0) {
				tmp.n[0] = this->n[diff];
			}
		}
		result.trim();
		return result;
	}

	bool operator ==(BigInt b) {
		return mycmp(b) == 0;
	}

	bool operator !=(BigInt b) {
		return mycmp(b) != 0;
	}

	bool operator >(BigInt b) {
		return mycmp(b) > 0;
	}

	bool operator >=(BigInt b) {
		return mycmp(b) >= 0;
	}

	bool operator <(BigInt b) {
		return mycmp(b) < 0;
	}

	bool operator <=(BigInt b) {
		return mycmp(b) <= 0;
	}

	bool operator ==(long long a) {
		return *this == BigInt(a);
	}

	bool operator !=(long long a) {
		return *this != BigInt(a);
	}

	bool operator >(long long a) {
		return *this > BigInt(a);
	}

	bool operator >=(long long a) {
		return *this >= BigInt(a);
	}

	bool operator <(long long a) {
		return *this < BigInt(a);
	}

	bool operator <=(long long a) {
		return *this <= BigInt(a);
	}

	void trim() {
		int i;
		for (i = n.size(); --i && n[i] == '0';)
			n = n.substr(0, i);
	}

	int mycmp(BigInt b) {
		int i, l1 = n.size(), l2 = b.n.size();
		if (l1 != l2)
			return (l1 > l2) - (l1 < l2);
		for (i = l1; i-- && n[i] == b.n[i];)
			;
		if (i == -1)
			return 0;
		return (n[i] > b.n[i]) - (n[i] < b.n[i]);
	}

	void show() {
		printf("%s\n", to_string().c_str());
	}

	string to_string() {
		string s = n;
		reverse(s.begin(), s.end());
		return s;
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

int main(void) {
	char chainA[1028], chainB[1028];
	BigInt a, b;
	scanf("%s\n%s", chainA, chainB);
	a = string(chainA);
	b = string(chainB);
	BigInt r = myNwd(a, b);
	r.show();
	return 0;
}

