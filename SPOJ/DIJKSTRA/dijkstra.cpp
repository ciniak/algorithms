//============================================================================
// Name        : dijkstra.cpp
// Author      : Michal Marcinkowski
// Description : pl.spoj.com/problems/DIJKSTRA
//============================================================================

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int num = 1;

struct vertex{
    typedef pair<int,vertex*> edge;
    vector<edge> edges; //cost of edge, destination vertex
    bool visited;
    int minimal;
    int number;
    vertex()
    {
        visited = false;
        minimal = 0;
        number = num;
        num++;
    }
};

class Graph
{
    public:
        Graph (int numberOfVertexes);
        vertex* vertexes;
        void addEdge(const int& first, const int& second, int cost);
        ~Graph();
};

Graph::~Graph() {
   delete[] vertexes;
}

Graph::Graph(int numberOfVertexes) {
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
        if( vertex1->minimal > vertex2->minimal ) return true;

        if( vertex1->minimal < vertex2->minimal ) return false;

        return false;
    }
};

int startVertexNumber, endVertexNumber;

Graph* createGraph() {
    int fromVertex, toVertex, cost, numberOfVertexes, numberOfEdges;
    cin >> numberOfVertexes >> numberOfEdges;
    Graph* graph = new Graph(numberOfVertexes);
    while (numberOfEdges > 0) {
        cin >> fromVertex >> toVertex >> cost;
        graph->addEdge(fromVertex, toVertex, cost);
        numberOfEdges--;
    }
    cin >> startVertexNumber >> endVertexNumber;
    return graph;
}

typedef priority_queue<vertex*, vector<vertex*>, compareVertexes> vertexesQueue;

void BFS(vertex* v) {
     v->minimal = 0;
     v->visited = true;
     vertexesQueue vertexesToVisit;
     vertexesToVisit.push(v);
     while(!vertexesToVisit.empty()) {
         vertex* currentVertex = vertexesToVisit.top();
         vertexesToVisit.pop();
         if (currentVertex->number == endVertexNumber) {
            break;
         }
         for (unsigned int i = 0; i < currentVertex->edges.size(); i++) {
             vertex::edge edge = currentVertex->edges[i];
             vertex* nextVertex = edge.second;
             if (nextVertex->visited) {
                if (currentVertex->minimal + edge.first < nextVertex->minimal) {
                    nextVertex->minimal = currentVertex->minimal + edge.first;
                }
             } else {
                nextVertex->minimal = currentVertex->minimal + edge.first;
                nextVertex->visited = true;
                vertexesToVisit.push(nextVertex);
             }
         }
     }
}

int main() {
    int numberOfCases;
    Graph* graph;
    cin >> numberOfCases;
    while(numberOfCases > 0) {
        graph = createGraph();
        BFS(&graph->vertexes[startVertexNumber - 1]);
        vertex* endVertex = &graph->vertexes[endVertexNumber - 1];
        if (endVertex->visited) {
            cout << endVertex->minimal << endl;
        } else {
            cout << "NIE" << endl;
        }
        numberOfCases--;
    }
}

