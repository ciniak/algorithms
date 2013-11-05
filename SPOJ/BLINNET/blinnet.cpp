//============================================================================
// Name        : blinnet.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/BLINNET
//============================================================================

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> cityToCity;
typedef pair<int, cityToCity> edge;

vector<edge> edges;
int* parent;

int getParent(int city) {
	if(city != parent[city]) {
        parent[city] = getParent(parent[city]);
	}
	return parent[city];
}

int main() {
	int numberOfCases, numberOfCities, numberOfConnections, secondCity, firstCity, pathCost, connectionsNumber, overallCost, i;
	char cityName[12];
	scanf("%d", &numberOfCases);
	while(numberOfCases) {
		scanf("%d", &numberOfCities);
		parent = new int[numberOfCities + 1];
		for(i = 1; i <= numberOfCities; i++) {
			parent[i] = i;
			scanf("%s", cityName);
			scanf("%d", &numberOfConnections);
			while(numberOfConnections--) {
				scanf("%d %d", &secondCity, &pathCost);
				if(secondCity > i) {
                    edges.push_back(edge(pathCost, cityToCity(i, secondCity)));
				}
			}
		}
		sort(edges.begin(), edges.end());
		connectionsNumber = edges.size();
		overallCost = 0;
		for(i = 0; i < connectionsNumber; i++) {
			firstCity = getParent(edges[i].second.first);
			secondCity = getParent(edges[i].second.second);
			pathCost = edges[i].first;
			if(firstCity != secondCity) {
				overallCost += pathCost;
				parent[firstCity] = parent[secondCity];
			}
		}
		printf("%d\n", overallCost);
		delete[] parent;
		edges.clear();
		numberOfCases--;
	}
}

