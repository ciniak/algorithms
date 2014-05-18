#include <cstdio>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstring>

using namespace std;

struct head {
	int hitsToDestroy;
	int hitsToCut;
	vector<int> growingHeads;
};

int headsNumber;

head* hydrasHeads;
bool* calculated;
int* cost;

bool headsCompare(const int& a, const int& b) {
	return hydrasHeads[a].hitsToDestroy < hydrasHeads[b].hitsToDestroy;
}

int getCost(int);

int calculate(int i) {
	int result = hydrasHeads[i].hitsToCut;
	for (int j = 0; j < hydrasHeads[i].growingHeads.size(); j++) {
		if (j == i) {
			result = hydrasHeads[i].hitsToDestroy;
			break;
		}
		result += getCost(j);
		if (hydrasHeads[i].hitsToDestroy <= result) {
			result = hydrasHeads[i].hitsToDestroy;
			break;
		}
	}
	calculated[i] = true;
	cost[i] = result;
	return result;
}

int getCost(int i) {
	if (calculated[i]) {
		return cost[i];
	}
	return calculate(i);
}

int main() {
	int growingHeadsNumber, hydrasNumber, minDestroy, minHead;
	scanf("%d", &headsNumber);
	hydrasHeads = new head[headsNumber];
	calculated = new bool[headsNumber];
	cost = new int[headsNumber];
	memset(calculated, 0, sizeof(calculated));
	minHead = 0;
	minDestroy = numeric_limits<int>::max();
	for (int i = 0; i < headsNumber; i++) {
		scanf("%d %d %d", &hydrasHeads[i].hitsToCut, &hydrasHeads[i].hitsToDestroy, &growingHeadsNumber);
		if (hydrasHeads[i].hitsToDestroy < minDestroy) {
			minHead = i;
			minDestroy = hydrasHeads[minHead].hitsToDestroy;
		}
		for (int j = 0; j < growingHeadsNumber; j++) {
			scanf("%d", &hydrasNumber);
			hydrasHeads[i].growingHeads.push_back(hydrasNumber - 1);
		}
		sort(hydrasHeads[i].growingHeads.begin(), hydrasHeads[i].growingHeads.end(), headsCompare);
	}

	for (int i = 0; i < headsNumber; i++) {
		if ((hydrasHeads[i].hitsToDestroy == minDestroy)
				|| ((hydrasHeads[i].hitsToCut + (minDestroy * hydrasHeads[i].growingHeads.size())) >= hydrasHeads[i].hitsToDestroy)) {
			calculated[i] = true;
			cost[i] = hydrasHeads[i].hitsToDestroy;
		}
	}
	calculated[minHead] = true;
	cost[minHead] = hydrasHeads[minHead].hitsToDestroy;

	printf("%d", getCost(0));

	delete[] hydrasHeads;
	delete[] calculated;
	delete[] cost;
	return 0;
}
