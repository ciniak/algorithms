//============================================================================
// Name        : mrowki_i_biedronka.cpp
// Author      : Michal Marcinkowski
// Description : http://main.edu.pl/pl/archive/oi/8/mro
//				 Tree structure used to represent leafs and branches
//				 Root as target point (calculated path for all nodes to ladybug)
//				 DFS to block path
//============================================================================

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

//n (0 < n < 5000)- number of leafs and branches, k (0 < k < n) - number of ants, l (0 < l < 500) - number of ladybug's arrivals
int n, k, l;

int antPos[5001];
int antAttacks[5001];
int nodeParent[5001];
bool nodeBlocked[5001];
int nodeAnt[5001];
vector<int> nodeNeighbors[5001];

void makeRoot(int node) {
	int parentParent, parent = nodeParent[node];
	nodeParent[node] = -1;
	int currentNode = node;
	while (parent != -1) {
		parentParent = nodeParent[parent];
		nodeParent[parent] = currentNode;
		currentNode = parent;
		parent = parentParent;
	}
}

void initRoot(int node) {
	for (unsigned i = 0; i < nodeNeighbors[node].size(); i++) {
		if (nodeNeighbors[node][i] != nodeParent[node]) {
			nodeParent[nodeNeighbors[node][i]] = node;
			initRoot(nodeNeighbors[node][i]);
		}
	}
}

void blockPath(int node) {
	for (unsigned i = 0; i < nodeNeighbors[node].size(); i++) {
		if ((nodeNeighbors[node][i] != nodeParent[node]) && (!nodeBlocked[nodeNeighbors[node][i]])) {
			nodeBlocked[nodeNeighbors[node][i]] = true;
			blockPath(nodeNeighbors[node][i]);
		}
	}
}

void updateBlockers() {
	for (int i = 1; i <= k; i++) {
		blockPath(antPos[i]);
	}
}

void initBlockers() {
	for (int i = 1; i <= k; i++) {
		if (!nodeBlocked[antPos[i]]) {
			nodeBlocked[antPos[i]] = true;
			blockPath(antPos[i]);
		}
	}
}

void printResult() {
	for (int i = 1; i <= k; i++) {
		printf("%d %d\n", antPos[i], antAttacks[i]);
	}
}

void attack(int lady) {
	for (int i = 1; i <= k; i++) {
		if (antPos[i] == lady) {
			antAttacks[i]++;
			return;
		}
	}
	initBlockers();
	bool finish = false;
	while (!finish) {
		for (int i = 1; i <= k; i++) {
			if (!nodeBlocked[nodeParent[antPos[i]]]) {
				antPos[i] = nodeParent[antPos[i]];
				nodeBlocked[antPos[i]] = true;
				if (antPos[i] == lady) {
					antAttacks[i]++;
					finish = true;
				}
			}
		}
		updateBlockers();
	}
}

int main() {
	int a, b, i, lady;
	memset(antAttacks, 0, sizeof(int) * 5001);
	memset(nodeParent, -1, sizeof(int) * 5001);
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		nodeNeighbors[i].clear();
	}
	for (i = 0; i < (n - 1); i++) {
		scanf("%d %d", &a, &b);
		nodeNeighbors[a].push_back(b);
		nodeNeighbors[b].push_back(a);
	}
	initRoot(1);

	scanf("%d", &k);
	for (i = 1; i <= k; i++) {
		scanf("%d", &antPos[i]);
	}
	scanf("%d", &l);
	while (l--) {
		scanf("%d", &lady);
		makeRoot(lady);
		memset(nodeBlocked, 0, sizeof(bool) * (n + 1));
		attack(lady);
	}
	printResult();
	return 0;
}
