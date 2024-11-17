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
    Edge(int from_vertex = 0, int to_vertex = 0, float weight = 0) { //It has a constructor to initialize these members.
        this->from_vertex = from_vertex;
        this->to_vertex = to_vertex;
        this->weight = weight;
    }
};

class Graph { //This class represents a graph.
public: // It has public members numVerts (number of vertices), vertices (a vector of Vertex objects), and adjList (a 2D vector representing the adjacency list of the graph).
    int numVerts;
    vector<Vertex> vertices;
    vector<vector<Edge>> adjList; // It has a default constructor, a parameterized constructor, a destructor, and various member functions for graph operations:
    Graph()
    {
        numVerts = 0;
    }
    Graph(int n);
    ~Graph();
    void addVertex(Vertex v);                                    // Adds a vertex to the graph.
    void addDirectedEdge(int v1, int v2, float weight = 1.0f);   // Adds a directed edge between two vertices with an optional weight.
    void addUndirectedEdge(int v1, int v2, float weight = 1.0f); // Adds an undirected edge between two vertices with an optional weight.
    int outDegree(int v);                                        // Returns the out-degree of a vertex.
    vector<int> DepthFirstSearch(int v);                         // Performs Depth-First Search starting from a given vertex.
    vector<int> BreadthFirstSearch(int v);                       // Performs Breadth-First Search starting from a given vertex.
    bool checkCycle();                                           // Checks whether the graph contains a cycle.
    void printGraph();                                           // Prints the graph.
private:
    void DFSUtil(int v, vector<int> &visited, vector<int> &result);
};