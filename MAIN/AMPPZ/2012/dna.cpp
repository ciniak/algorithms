#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int main() {
	int size, array[4];
	cin >> size;
	char code;
	int n;
	memset(array, 0, sizeof(array));
	for (int i = 0; i < size; i++) {
		cin >> code;
		n = 0;
		switch (code) {
		case 'T':
			n++;
			/* no break */
		case 'G':
			n++;
			/* no break */
		case 'C':
			n++;
		}
		array[n]++;
	}
	int minIndex = 0;

	for (int i = 1; i < 4; i++) {
		if (array[i] < array[minIndex]) {
			minIndex = i;
		}
	}

	switch (minIndex) {
	case 0:
		code = 'A';
		break;
	case 1:
		code = 'C';
		break;
	case 2:
		code = 'G';
		break;
	case 3:
		code = 'T';
		break;
	}

	cout << array[minIndex] << endl;

	for (int i = 0; i < size; i++) {
		cout << code;
	}
	return 0;
}

