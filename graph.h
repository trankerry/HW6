#include <vector>
#include <list>
#include <queue>
#include <iostream>
using namespace std;

class Vertex { // This class represents a vertex in the graph.
public:
    int id; 
    string name;
    Vertex(int id = 0, string name = "") { // It has a constructor to initialize the id and name of the vertex.
        this->id = id;
        this->name = name;
    }
};

struct Edge { // This structure represents an edge in the graph.
    int from_vertex;
    int to_vertex;
    float weight; //It has public members from_vertex, to_vertex, and weight.
    Edge() : from_vertex(0), to_vertex(0), weight(0.0f) {} //It has a default constructor to initialize these members.
    Edge(int from_vertex, int to_vertex, float weight);
};

class Graph { //This class represents a graph.
public: // It has public members numVerts (number of vertices), vertices (a vector of Vertex objects), and adjList (a 2D vector representing the adjacency list of the graph).
    int numVerts;
    vector<Vertex> vertices;
    vector<vector<Edge> > adjList; // It has a default constructor, a parameterized constructor, a destructor, and various member functions for graph operations:
    Graph()
    {
        numVerts = 0;
    }
    Graph(int n);
    ~Graph();
    void addDirectedEdge(int v1, int v2, float weight = 1.0f);   // Adds a directed edge between two vertices with an optional weight.
    void printGraph();                                           // Prints the graph.
};