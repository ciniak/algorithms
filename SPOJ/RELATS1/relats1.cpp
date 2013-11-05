//============================================================================
// Name        : relats1.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/RELATS1
//============================================================================

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int vertices[1000];
bool connections[1000][1000];
int enteringEdges[1000];
int verticesValues[1000];

int numberOfVertices;
bool bad;

int getVertice(int v) {
    if (vertices[v] < 0) {
        return getVertice((vertices[v] * (-1)) - 1);
    } else {
        return v;
    }
}

void topologicalSort(int startVertex) {
    int vertex, i, v;
    queue<int> q;
    q.push(startVertex);
    while (!q.empty()) {
        vertex = q.front();
        q.pop();
        vertices[vertex] = 1;
        for (i = 0; i < numberOfVertices; i++) {
            if (connections[vertex][i] == true) {
                v = getVertice(i);
                verticesValues[v] = max(verticesValues[v], verticesValues[vertex] + 1);
                enteringEdges[v]--;
                if (enteringEdges[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
}

int getMax() {
    int maxx = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        if (verticesValues[i] > maxx) {
            maxx = verticesValues[i];
        }
    }
    return maxx;
}

int main() {
    int numberOfCases, numberOfEdges, i, from, to, weight;
    scanf("%d", &numberOfCases);
    while(numberOfCases--) {
        scanf("%d %d", &numberOfVertices, &numberOfEdges);

        memset(vertices, 0, numberOfVertices * sizeof(int));
        memset(enteringEdges, 0, numberOfVertices * sizeof(int));
        memset(verticesValues, 0, numberOfVertices * sizeof(int));
        for (i = 0; i < numberOfVertices; i++) {
            memset(connections[i], 0, numberOfVertices * sizeof(int));
        }

        for (i = 0; i < numberOfEdges; i++) {
            scanf("%d %d %d", &from, &to, &weight);
            to = getVertice(to - 1) + 1;
            from = getVertice(from - 1) + 1;
            if (weight == 1) {
                if (connections[to - 1][from - 1] == false) {
                    enteringEdges[from - 1]++;
                    connections[to - 1][from - 1] = true;
                }
            } else if (weight == -1) {
                if (connections[from - 1][to - 1] == false) {
                    enteringEdges[to - 1]++;
                    connections[from - 1][to - 1] = true;
                }
            } else {
                if (to != from) {
                    for (int j = 0; j < numberOfVertices; j++) {
                        if (connections[to - 1][j] == true) {
                            connections[from - 1][j] = true;
                        }
                    }
                    vertices[to - 1] = (-1) * from;
                }
            }
        }
        bad = false;
        for (i = 0; i < numberOfVertices; i++) {
            if ((vertices[i] == 0) && (enteringEdges[i] == 0)) {
                topologicalSort(i);
            }
        }
        for (i = 0; i < numberOfVertices; i++) {
            if (vertices[i] == 0) {
                bad = true;
                break;
            }
        }
        if (bad) {
            printf("NO\n");
        } else {
            printf("%d\n", getMax());
        }
    }


}

