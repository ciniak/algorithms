//============================================================================
// Name        : bsheep.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/BSHEEP
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

const int MAX = 100000;

struct sheep {
	int x;
	int y;
	int number;
}typedef sheep;

sheep sheeps[MAX];

float angles[MAX];

int numberOfSheeps;

struct compareSheeps {
	bool operator ()(const pair<int, float> &p1, const pair<int, float> &p2) {
		if (p1.second > p2.second) {
			return true;
		}
		if (p1.second < p2.second) {
			return false;
		}
		if (sheeps[p1.first].x > sheeps[p2.first].x) {
			return true;
		}
		return false;
	}
};

typedef priority_queue<pair<int, float>, vector<pair<int, float> >, compareSheeps> sheepsQueue;

int rootX, rootY;

float calcAlpha(int xx, int yy) {
	int x = xx - rootX;
	int y = yy - rootY;
	int d = abs(x) + abs(y);
	if ((x >= 0) && (y >= 0)) {
		return ((y * 1.0) / d);
	} else if ((x < 0) && (y >= 0)) {
		return (2 - ((y * 1.0) / d));
	} else if ((x < 0) && (y < 0)) {
		return (2 + ((abs(y) * 1.0) / d));
	} else if ((x >= 0) && (y < 0)) {
		return (4 - ((abs(y) * 1.0) / d));
	}
	return 0;
}

int calcDet(int p1, int p2, int p3) {
	return (sheeps[p1].x * sheeps[p2].y + sheeps[p2].x * sheeps[p3].y + sheeps[p3].x * sheeps[p1].y - sheeps[p2].y * sheeps[p3].x
			- sheeps[p3].y * sheeps[p1].x - sheeps[p1].y * sheeps[p2].x);
}

int main() {
	int numberOfCases, i;
	float result;
	sheepsQueue sortedSheeps;
	scanf("%d", &numberOfCases);
	while (numberOfCases--) {
		scanf("%d", &numberOfSheeps);
		int firstSheep = 0;
		for (i = 0; i < numberOfSheeps; i++) {
			scanf("%d %d", &sheeps[i].x, &sheeps[i].y);
			sheeps[i].number = i + 1;
			if ((sheeps[i].y < sheeps[firstSheep].y)) {
				firstSheep = i;
			} else if (sheeps[i].y == sheeps[firstSheep].y) {
				if (sheeps[i].x < sheeps[firstSheep].x) {
					firstSheep = i;
				}
			}
		}

		rootX = sheeps[firstSheep].x;
		rootY = sheeps[firstSheep].y;
		for (i = 0; i < numberOfSheeps; i++) {
			if (i == firstSheep) {
				continue;
			}
			sortedSheeps.push(make_pair(i, calcAlpha(sheeps[i].x, sheeps[i].y)));
		}
/*
		while(!sortedSheeps.empty()) {
			pair<int, float> p = sortedSheeps.top();
			printf("%d %.2f\n", p.first + 1, p.second);
			sortedSheeps.pop();
		}*/




	}
}
