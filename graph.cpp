#include <iostream> 
#include <vector>   
#include <list>
#include <queue>
#include <stack>
#include "graph.h"

// The parameterized constructor initializes the number of vertices and resizes the adjacency list vector.
Graph::Graph(int nV) { 
    numVerts = nV; 
    adjList.resize(nV);
}
Graph::~Graph() { }

// addDirectedEdge adds a directed edge from vertex v1 to vertex v2 with a specified weight. It adds the edge to the adjacency list of v1.
void Graph::addDirectedEdge(int v1, int v2, float weight){ 
    adjList[v1].emplace_back(v1, v2, weight);
}

// printGraph prints the adjacency list representation of the graph.
void Graph::printGraph() {
    cout << "Graph:" << endl;
    for (int i = 0; i < numVerts; i++) {
        cout << i << ": ";
        for (size_t j = 0; j < adjList[i].size(); ++j) {
        Edge &edge = adjList[i][j];
            cout << edge.to_vertex << " ";
        }
        cout << endl;
    }
    cout << endl;
}
Edge::Edge(int from_vertex, int to_vertex, float weight) {
    this->from_vertex = from_vertex;
    this->to_vertex = to_vertex;
    this->weight = weight;
}