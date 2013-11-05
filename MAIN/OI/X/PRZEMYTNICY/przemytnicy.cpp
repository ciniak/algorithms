//============================================================================
// Name        : przemytnicy.cpp
// Author      : Michal Marcinkowski
// Description : http://main.edu.pl/pl/archive/oi/10/prz
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int num;

struct vertex{
    typedef pair<int,vertex*> edge;
    vector<edge> edges; //cost of edge, destination vertex
    int pathCost;
    int number;
    vertex()
    {
        pathCost = numeric_limits<int>::max();
        number = num;
        num++;
    }
};

class Graph
{
    public:
        Graph (int numberOfVertexes);
        vertex* vertexes;
        int vertexesNumber;
        void addEdge(const int& first, const int& second, int cost);
        ~Graph();
};

Graph::~Graph() {
   delete[] vertexes;
}

Graph::Graph(int numberOfVertexes) {
    num = 1;
    vertexesNumber = numberOfVertexes;
    vertexes = new vertex[numberOfVertexes];
}

void Graph::addEdge(const int& from, const int& to, int cost)
{
    vertex* fromVertex = &vertexes[from - 1];
    vertex* toVertex = &vertexes[to - 1];
    vertex::edge edge = make_pair(cost, toVertex);
    fromVertex->edges.push_back(edge);
}

struct compareVertexes
{
    bool operator ()( const vertex* vertex1, const vertex* vertex2 )
    {
        if( vertex1->pathCost > vertex2->pathCost ) return true;

        if( vertex1->pathCost < vertex2->pathCost ) return false;

        return false;
    }
};

Graph* transposedGraph;
int* clo;

Graph* createGraph() {
    int fromVertex, toVertex, cost, numberOfMetals, numberOfTransformations;
    cin >> numberOfMetals;
    Graph* graph = new Graph(numberOfMetals);
    transposedGraph = new Graph(numberOfMetals);
    clo = new int[numberOfMetals];
    for (int i = 0; i < numberOfMetals; i++) {
        cin >> cost;
        clo[i] = cost >> 1;
    }
    cin >> numberOfTransformations;
    while(numberOfTransformations > 0) {
        cin >> fromVertex >> toVertex >> cost;
        graph->addEdge(fromVertex, toVertex, cost);
        transposedGraph->addEdge(toVertex, fromVertex, cost);
        numberOfTransformations--;
    }
    return graph;
}

typedef priority_queue<vertex*, vector<vertex*>, compareVertexes> vertexesQueue;

void findShortestPaths(vertex* v) {
     vertexesQueue vertexesToVisit;
     v->pathCost = 0;
     vertexesToVisit.push(v);
     while(!vertexesToVisit.empty()) {
         vertex* currentVertex = vertexesToVisit.top();
         vertexesToVisit.pop();
         for (unsigned int i = 0; i < currentVertex->edges.size(); i++) {
             vertex::edge edge = currentVertex->edges[i];
             vertex* nextVertex = edge.second;
             if (nextVertex->pathCost != numeric_limits<int>::max()) {
                if (currentVertex->pathCost + edge.first < nextVertex->pathCost) {
                    nextVertex->pathCost = currentVertex->pathCost + edge.first;
                    vertexesToVisit.push(nextVertex);
                }
             } else {
                nextVertex->pathCost = currentVertex->pathCost + edge.first;
                vertexesToVisit.push(nextVertex);
             }
         }
     }
}

int mininum(Graph* graph) {
    int tmp, pathCost, returnCost, minimum = clo[0];
    for (int i = 1; i < graph->vertexesNumber; i++) {
        pathCost = graph->vertexes[i].pathCost;
        returnCost = transposedGraph->vertexes[i].pathCost;
        if ((numeric_limits<int>::max() == pathCost) || (numeric_limits<int>::max() == returnCost)) {
            continue;
        }
        tmp = pathCost + clo[i] + returnCost;
        if (tmp < minimum) {
            minimum = tmp;
        }
    }
    return minimum;
}

int main() {
    int startVertexNumber = 0;
    int numberOfCases;
    Graph* graph;
    graph = createGraph();
    findShortestPaths(&graph->vertexes[startVertexNumber]);
    findShortestPaths(&transposedGraph->vertexes[startVertexNumber]);
    cout << mininum(graph) << endl;
    delete transposedGraph;
    delete[] clo;


}
