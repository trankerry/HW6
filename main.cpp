#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <exception>
#include <utility>
#include <algorithm>
#include <string> 

#include "graph.h" // Include your graph header file here

using namespace std;

struct CityInfo {
	int id;
    string code;
    string name;
    int population;
    int elevation;
};

unordered_map<string, CityInfo> cities;
void readCityData(const string& filename) {
	ifstream file(filename); // Open the city data file
	if (!file.is_open()) {
		cerr << "Error: Unable to open city file\n";
		throw ios_base::failure("Unable to open city file");
	}

	while (file.good()) {
		int id, population, elevation;
		string code, name;

		// Parse city data
		file >> id >> code >> name >> population >> elevation;
		cities[code] = { id, code, name, population, elevation };
	}
	file.close();
}

void readRoadData(const string& filename, Graph& graph) {
	ifstream file(filename); // Open the road data file
	if (!file.is_open()) {
		cerr << "Error: Unable to open road file\n";
		throw ios_base::failure("Unable to open road file");
	}

	int from, to;
	float weight;
	while (file >> from >> to >> weight) {
		graph.addDirectedEdge(from, to, weight); // Add directed edges to the graph
	}
	file.close();
}


// Dijkstra function to calculate shortest paths and predecessors
std::pair<vector<int>, vector<int>> dijkstra(const Graph& graph, int src, int dest) {
	vector<int> distance(graph.numVerts, numeric_limits<int>::max());
	vector<int> predecessor(graph.numVerts, -1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

	// Initialize source node
	distance[src] = 0;
	pq.push({ 0, src });

	while (!pq.empty()) {
		int u = pq.top().second; // Get the node with the smallest distance
		pq.pop();

		// Explore neighbors of the current node
		for (const auto& edge : graph.adjList[u]) {
			int v = edge.to_vertex;
			int weight = edge.weight;

			// Relax the edge if a shorter path is found
			if (distance[v] > distance[u] + weight) {
				distance[v] = distance[u] + weight;
				predecessor[v] = u;
				pq.push({ distance[v], v }); // Push the updated node into the queue
			}
		}
	}

	return {distance, predecessor}; // Return both distance and predecessor vectors
}

//scheduled for rewrite
void printShortestRoute(const string &fromCity, const string &toCity, const vector<int> &distance, const vector<int> &predecessor) {
	int from = cities[fromCity].id; // Source city ID
	int to = cities[toCity].id;     // Destination city ID

	// Check if the destination is unreachable
	if (distance[to] == numeric_limits<int>::max()) {
		cout << "No route from " << cities[fromCity].name << " to " << cities[toCity].name << endl;
		return;
	}

	// Print city details
	cout << "From City: " << cities[fromCity].name << ", population " << cities[fromCity].population
		<< ", elevation " << cities[fromCity].elevation << endl;
	cout << "To City: " << cities[toCity].name << ", population " << cities[toCity].population
		<< ", elevation " << cities[toCity].elevation << endl;
	cout << "The shortest distance from " << cities[fromCity].name << " to " << cities[toCity].name
		<< " is " << distance[to] << " through the route: ";

	vector<string> path;
	int current = to;
	while (current != -1) {
		for (const auto& pair : cities) {
			if (pair.second.id == current) {
				path.push_back(pair.second.name);
				break;
			}
		}
		current = predecessor[current];
	}

	reverse(path.begin(), path.end());
	for (size_t i = 0; i < path.size(); ++i) {
		if (i > 0) cout << "->";
		cout << path[i];
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <from_city_code> <to_city_code>\n";
		return EXIT_FAILURE;
	}

	string fromCity = argv[1];
	string toCity = argv[2];

	try {
		// Load city and road data
		readCityData("city.txt");
		Graph graph(cities.size());
		readRoadData("roads.txt", graph);

		// Validate input city codes
		if (cities.find(fromCity) == cities.end()) {
			cerr << "Invalid city code: " << fromCity << "\n";
			return EXIT_FAILURE;
		}
		if (cities.find(toCity) == cities.end()) {
			cerr << "Invalid city code: " << toCity << "\n";
			return EXIT_FAILURE;
		}

		// Run Dijkstra's algorithm
		auto [distance, predecessor] = dijkstra(graph, cities[fromCity].id, cities[toCity].id);

		// Print the shortest route
		printShortestRoute(fromCity, toCity, distance, predecessor);
	}
	catch (const std::exception& e) {
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
