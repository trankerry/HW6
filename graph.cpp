#include <iostream> 
#include <vector>   
#include <list>
#include <queue>
#include <stack>
#include "graph.h"

Graph::Graph(int nV) {// The constructor for the Graph class initializes the number of vertices (numVerts) and resizes the adjacency list (adjList) to have nV elements.
    numVerts = nV; // It resizes the adjacency list (adjList) vector to have nV elements.
    adjList.resize(nV);
}
Graph::~Graph() { }

void Graph::addVertex(Vertex v) {// addVertex adds a vertex to the graph. It appends the vertex to the vertices vector, adds an empty list to the adjList vector (representing the adjacency list for this new vertex), and increments the total number of vertices.
    vertices.push_back(v); // It appends the vertex to the vertices vector.
    adjList.emplace_back();
    numVerts++; // It increments the total number of vertices.
}

void Graph::addDirectedEdge(int v1, int v2, float weight){// addDirectedEdge adds a directed edge from vertex v1 to vertex v2 with a specified weight. It adds an edge to the adjacency list of v1.
    adjList[v1].emplace_back(v1, v2, weight);
}

void Graph::addUndirectedEdge(int v1, int v2, float weight) {// addUndirectedEdge adds an undirected edge between vertices v1 and v2 with a specified weight. It adds edges to both the adjacency list of v1 and v2.
    adjList[v1].emplace_back(v1, v2, weight);
    adjList[v2].emplace_back(v2, v1, weight);
}

int Graph::outDegree(int v) { // This function returns the out-degree (number of outgoing edges) of a given vertex v.
    return adjList[v].size();
}

vector<int> Graph::DepthFirstSearch(int v) { // DepthFirstSearch performs a depth-first search starting from vertex v and returns a vector containing the order in which the vertices were visited.
    vector<int> visited(numVerts, 0);
    vector<int> result;
    DFSUtil(v, visited, result);
    return result;
}

void Graph::DFSUtil(int v, vector<int> &visited, vector<int> &result) {// This is a utility function for depth-first search.
    visited[v] = 1;      //It marks the current vertex as visited and adds it to the result vector.
    result.push_back(v); // It recursively explores the unvisited neighbors.
    for (auto &edge : adjList[v]) {
        if (visited[edge.to_vertex] == 0)
            DFSUtil(edge.to_vertex, visited, result);
    }
}

vector<int> Graph::BreadthFirstSearch(int v) {// performs a breadth-first search starting from vertex v and returns a vector containing the order in which the vertices were visited.
    vector<int> visited(numVerts, 0);
    vector<int> result;
    queue<int> que;
    que.push(v);
    while (!que.empty()) {
        v = que.front();
        que.pop();
        if (visited[v] == 0) {
            result.push_back(v);
            visited[v] = 1;
            for (auto &edge : adjList[v]) {
                if (visited[edge.to_vertex] == 0)
                    que.push(edge.to_vertex);
            }
        }
    }
    return result;
}

bool Graph::checkCycle() {// checks whether the graph contains a cycle using breadth-first search. It returns true if a cycle is found and false otherwise.
    vector<int> parent(numVerts, -1);
    vector<int> visited(numVerts, 0);
    for (int i = 0; i < numVerts; ++i) {
        if (visited[i] == 0) {
            queue<int> que;
            que.push(i);
            visited[i] = 1;
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto &edge : adjList[v]) {
                    if (visited[edge.to_vertex] == 0) {
                        visited[edge.to_vertex] = 1;
                        que.push(edge.to_vertex);
                        parent[edge.to_vertex] = v;
                    }
                    else if (parent[v] != edge.to_vertex){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Graph::printGraph() {// prints the graph by iterating through each vertex and printing its adjacent vertices.
    cout << "Graph:" << endl;
    for (int i = 0; i < numVerts; i++) {
        cout << i << ": ";
        for (auto &edge : adjList[i]) {
            cout << edge.to_vertex << " ";
        }
        cout << endl;
    }
    cout << endl;
}