//============================================================================
// Name        : benefact.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/BENEFACT
//============================================================================

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector< pair<int, int> >* cities;
int* path;
int numberOfPlaces;

void createGraph() {
    int firstVertex, secondVertex, cost, i;
    scanf("%d", &numberOfPlaces);
    path = new int[numberOfPlaces];
    memset(path, 0, sizeof(int) * numberOfPlaces);
    cities = new vector< pair<int, int> >[numberOfPlaces];
    for (i = 0; i < numberOfPlaces - 1; i++) {
        scanf("%d %d %d", &firstVertex, &secondVertex, &cost);
        cities[firstVertex - 1].push_back(make_pair(secondVertex - 1, cost));
        cities[secondVertex - 1].push_back(make_pair(firstVertex - 1, cost));
    }
}

void DFS(int vertex, int exclude) {
    vector< pair<int, int> > neighbours = cities[vertex];
    for(int i = 0; i < neighbours.size(); i++) {
        if (neighbours[i].first != exclude) {
            path[neighbours[i].first] = path[vertex] + neighbours[i].second;
            DFS(neighbours[i].first, vertex);
        }
    }
}


int main() {
    int numberOfCases, maximum, i;
    scanf("%d", &numberOfCases);
    while(numberOfCases--) {
        createGraph();
        DFS(0, 0);
        maximum = 0;
        for(int i = 0; i < numberOfPlaces; i++) {
            if (path[i] > path[maximum]) {
                maximum = i;
            }
        }
        memset(path, 0, sizeof(int) * numberOfPlaces);
        DFS(maximum, maximum);
        maximum = 0;
        for(i = 0; i < numberOfPlaces; i++) {
            if (path[i] > maximum) {
                maximum = path[i];
            }
        }
        printf("%d\n", maximum);
        delete[] path;
        delete[] cities;
    }
}

