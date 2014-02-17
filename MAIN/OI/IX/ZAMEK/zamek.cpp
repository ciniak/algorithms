//============================================================================
// Name        : zamek.cpp
// Author      : Michal Marcinkowski
// Description : http://main.edu.pl/pl/archive/oi/9/zam
//				 BFS used to find all paths
//				 map (chamber, cash) used to get predecessor
//============================================================================

#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct chamber {
	int number, cost;
	vector<int> neighbours;
};

chamber chambers[128];
int mapp[100][1000];

void BFS(int start, int end, int cash) {
	queue<pair<int, int> > queue;
	queue.push(make_pair(start, cash - chambers[start].cost));
	while (!queue.empty()) {
		pair<int, int> pair = queue.front();
		queue.pop();
		const vector<int> chambN = chambers[pair.first].neighbours;
		for (unsigned i = 0; i < chambN.size(); i++) {
			if (pair.second - chambers[chambN[i]].cost >= 0) {
				if (mapp[chambN[i]][pair.second - chambers[chambN[i]].cost] == -1) {
					if (((pair.second - chambers[chambN[i]].cost) == 0) && (end == chambN[i])) {
						mapp[end][0] = pair.first;
						return;
					} else {
						queue.push(make_pair(chambN[i], pair.second - chambers[chambN[i]].cost));
						mapp[chambN[i]][pair.second - chambers[chambN[i]].cost] = pair.first;
					}
				}
			}
		}
	}
	printf("Path not found!");
}

int main() {
	//n - komnaty, m - korytarze ( < 5000), w - wierzcholek wejsciowy, k - koncowy, s - ilosc kasy w sakwie
	int n, m, w, k, s, i, c1, c2;
	scanf("%d %d %d %d %d", &n, &m, &w, &k, &s);
	for (i = 0; i < n; i++) {
		scanf("%d", &chambers[i].cost);
		chambers[i].number = i;
	}
	while (m--) {
		scanf("%d %d", &c1, &c2);
		chambers[c1 - 1].neighbours.push_back(c2 - 1);
		chambers[c2 - 1].neighbours.push_back(c1 - 1);
	}
	memset(mapp, -1, sizeof(int) * 100000);
	BFS(w - 1, k - 1, s);

	int tmp, chamber = k - 1, cash = 0;
	stack<int> path;
	while (cash != s) {
		path.push(chamber + 1);
		if ((tmp = mapp[chamber][cash]) != -1) {
			cash += chambers[chamber].cost;
			chamber = tmp;
		} else {
			cash += chambers[chamber].cost;
		}
	}

	while (!path.empty()) {
		printf("%d ", path.top());
		path.pop();
	}

	return 0;
}

