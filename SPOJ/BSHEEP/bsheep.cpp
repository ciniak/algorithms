//============================================================================
// Name        : bsheep.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/BSHEEP
//============================================================================

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>

template<class T>
class MyStack {
public:
	MyStack() {
		size = 0;
	}

	void push(T item) {
		if (size < stack.size()) {
			stack[size] = item;
		} else {
			stack.push_back(item);
		}
		size++;
	}

	int getSize() {
		return size;
	}

	T& pop() {
		return stack[--size];
	}

	T& getLast() {
		return stack[size - 1];
	}

	T& getPreLast() {
		return stack[size - 2];
	}

	std::vector<T>& getStack() {
		return stack;
	}

	void clear() {
		size = 0;
	}

	void print() {
		for (unsigned i = 0; i < size; i++) {
			printf("%d ", stack[i] + 1);
		}
		printf("\n\n");
	}

	~MyStack() {

	}
private:
	unsigned size;
	std::vector<T> stack;
};

using namespace std;

const int MAX = 100000;

struct sheep {
	int x;
	int y;
	int number;
	double alpha;

	void calcAlpha(int rootX, int rootY) {
		int xx = this->x - rootX;
		int yy = this->y - rootY;
		int d = abs(xx) + abs(yy);
		if ((xx >= 0) && (yy >= 0)) {
			this->alpha = ((yy * 1.0) / d);
		} else if ((xx < 0) && (yy >= 0)) {
			this->alpha = (2 - ((yy * 1.0) / d));
		} else if ((xx < 0) && (yy < 0)) {
			this->alpha = (2 + ((abs(yy) * 1.0) / d));
		} else if ((xx >= 0) && (yy < 0)) {
			this->alpha = (4 - ((abs(yy) * 1.0) / d));
		} else {
			this->alpha = -1;
		}
	}

}typedef sheep;

sheep points[MAX];

double angles[MAX];

int numberOfPoints;

struct compareSheeps {
	bool operator ()(const int &p1, const int &p2) {
		if (points[p1].alpha < points[p2].alpha) {
			return true;
		}
		if (points[p1].alpha > points[p2].alpha) {
			return false;
		}
		if (points[p1].x < points[p2].x) {
			return true;
		}
		if (points[p1].x > points[p2].x) {
			return false;
		}
		if (points[p1].y < points[p2].y) {
			return true;
		}
		if (points[p1].y > points[p2].y) {
			return false;
		}
		return false;
	}
};

typedef set<int, compareSheeps> sheepsSet;

int calcDet(int p1, int p2, int p3) {
	return (points[p1].x * points[p2].y + points[p2].x * points[p3].y + points[p3].x * points[p1].y - points[p2].y * points[p3].x
			- points[p3].y * points[p1].x - points[p1].y * points[p2].x);
}

double calcLength(int i1, int i2) {
	int xDif = points[i1].x - points[i2].x;
	int yDif = points[i1].y - points[i2].y;
	return hypot(xDif, yDif);
}

double calcFence(vector<int> v, int size) {
	if (v.size() == 1) {
		return 0;
	} else if (v.size() == 2) {
		return (2 * (calcLength(v[0], v[1])));
	}
	double result = 0;
	int index1, index2;
	for (unsigned int i = 0; i < size; i++) {
		index1 = v[i];
		index2 = v[(i + 1) % size];
		result += calcLength(index1, index2);
	}
	return result;
}

int main() {
	int numberOfCases, i, rootX, rootY,	p1, p2, p3;
	sheepsSet sortedSheeps;
	MyStack<int> stack;
	sheepsSet::iterator it;
	scanf("%d", &numberOfCases);
	while (numberOfCases--) {
		sortedSheeps.clear();
		stack.clear();
		scanf("%d", &numberOfPoints);
		int firstSheep = 0;
		for (i = 0; i < numberOfPoints; i++) {
			scanf("%d %d", &points[i].x, &points[i].y);
			points[i].number = i + 1;
			if ((points[i].y < points[firstSheep].y)) {
				firstSheep = i;
			} else if (points[i].y == points[firstSheep].y) {
				if (points[i].x < points[firstSheep].x) {
					firstSheep = i;
				}
			}
		}

		rootX = points[firstSheep].x;
		rootY = points[firstSheep].y;
		points[firstSheep].alpha = 0;
		sortedSheeps.insert(firstSheep);
		for (i = 0; i < numberOfPoints; i++) {
			if (i == firstSheep) {
				continue;
			}
			points[i].calcAlpha(rootX, rootY);
			sortedSheeps.insert(i);
		}

		it = sortedSheeps.begin();
		stack.push((*it));
		++it;
		if (it != sortedSheeps.end()) {
			stack.push((*it));
			++it;
			while ((it != sortedSheeps.end()) && (calcDet(stack.getPreLast(), stack.getLast(), (*it)) == 0)) {
				stack.pop();
				stack.push((*it));
				++it;
			}
			if (it != sortedSheeps.end()) {
				stack.push((*it));
				++it;
			}
		}
		while (it != sortedSheeps.end()) {
			p1 = stack.getPreLast();
			p2 = stack.getLast();
			p3 = (*it);
			++it;
			while (calcDet(p1, p2, p3) < 0) {
				stack.pop();
				p1 = stack.getPreLast();
				p2 = stack.getLast();
			}
			if (calcDet(p1, p2, p3) == 0) {
				stack.pop();
			}
			stack.push(p3);
		}
		if ((stack.getSize() > 2) && (calcDet(stack.getPreLast(), stack.getLast(), firstSheep) == 0)) {
			stack.pop();
		}
		printf("%.2f\n", calcFence(stack.getStack(), stack.getSize()));
		stack.print();
	}
}
