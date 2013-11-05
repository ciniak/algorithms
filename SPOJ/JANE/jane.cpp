//============================================================================
// Name        : jane.cpp
// Author      : Micha³ Marcinkowski
// Description : www.spoj.com/problems/JANE
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <set>

using namespace std;

int main() {
	int treesHeight[100001];
	set<int> addedPairs[100001];
	queue<pair<int, int> > pairsToVisit;
	pair<int, int> currentPair;
	int i, j, jane, tarzan, nextJane, nextTarzan, lastJane, lastTarzan, numberOfTrees, maxDifference;
	scanf("%d %d", &numberOfTrees, &maxDifference);
	for (i = 1; i <= numberOfTrees; i++) {
		scanf("%d", &treesHeight[i]);
	}
	// adding all possible swaps
	for (i = 1; i < numberOfTrees - 1; i++) {
		if (abs(treesHeight[i] - treesHeight[i + 1]) <= maxDifference) {
			addedPairs[i].insert(i + 1);
			pairsToVisit.push(make_pair(i, i + 1));
		}
		if (abs(treesHeight[i] - treesHeight[i + 2]) <= maxDifference) {
			addedPairs[i].insert(i + 2);
			pairsToVisit.push(make_pair(i, i + 2));
		}
	}
	if (abs(treesHeight[numberOfTrees - 1] - treesHeight[numberOfTrees]) <= maxDifference) {
		addedPairs[numberOfTrees - 1].insert(numberOfTrees);
		pairsToVisit.push(make_pair(numberOfTrees - 1, numberOfTrees));
	}
	//going to all possible trees
	while (!pairsToVisit.empty()) {
		currentPair = pairsToVisit.front();
		jane = currentPair.first;
		tarzan = currentPair.second;
		pairsToVisit.pop();
		nextJane = jane + 1;
		nextTarzan = tarzan - 1;
		if ((nextJane < nextTarzan) && (abs(treesHeight[nextJane] - treesHeight[nextTarzan]) <= maxDifference)) {
			if (addedPairs[nextJane].find(nextTarzan) == addedPairs[nextJane].end()) {
				pairsToVisit.push(make_pair(nextJane, nextTarzan));
				addedPairs[nextJane].insert(nextTarzan);
			}
		}
		nextJane = jane + 1;
		nextTarzan = tarzan + 1;
		if ((nextTarzan <= numberOfTrees) && (abs(treesHeight[nextJane] - treesHeight[nextTarzan]) <= maxDifference)) {
			if (addedPairs[nextJane].find(nextTarzan) == addedPairs[nextJane].end()) {
				pairsToVisit.push(make_pair(nextJane, nextTarzan));
				addedPairs[nextJane].insert(nextTarzan);
			}
		}
		nextJane = jane - 1;
		nextTarzan = tarzan - 1;
		if ((nextJane > 0) && (abs(treesHeight[nextJane] - treesHeight[nextTarzan]) <= maxDifference)) {
			if (addedPairs[nextJane].find(nextTarzan) == addedPairs[nextJane].end()) {
				pairsToVisit.push(make_pair(nextJane, nextTarzan));
				addedPairs[nextJane].insert(nextTarzan);

			}
		}
		nextJane = jane - 1;
		nextTarzan = tarzan + 1;
		if ((nextJane > 0) && (nextTarzan <= numberOfTrees) && (abs(treesHeight[nextJane] - treesHeight[nextTarzan]) <= maxDifference)) {
			if (addedPairs[nextJane].find(nextTarzan) == addedPairs[nextJane].end()) {
				pairsToVisit.push(make_pair(nextJane, nextTarzan));
				addedPairs[nextJane].insert(nextTarzan);

			}
		}
	}

	set<int>::iterator it;
	for (i = 1; i <= numberOfTrees; i++) {
		for (it = addedPairs[i].begin(); it != addedPairs[i].end(); ++it) {
			printf("%d %d\n", i, (*it));
		}
	}
}

