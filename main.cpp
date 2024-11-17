#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <exception>
#include "graph.h" // Include your graph header file here

using namespace std;

struct CityInfo {
    string code;
    string name;
    int population;
    int elevation;
};

unordered_map<string, CityInfo> cities;
void readCityData(const string &filename) {
	//Attempt to open the given file
    ifstream file(filename);
	
	//Register exceptions
	file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

    if (!file.is_open()) {
        cerr << "Error: Unable to open city file\n";
        throw ios_base::failure("Unable to open city file"); //throw to terminate
    }
	
	//Read each line of the file until we run out of data
    string line;
	unsigned int linePosition = 0;
    while (file.good()) {
		//Data to extract
        int id, population, elevation;
        string code, name;
		
		//Try to extract data from the line using spaces as the delimiter
		try
		{
			file >> id >> ws; //Extract id, purge whitespace
			getline(file, code, ' '); file >> ws; //Extract code, purge whitespace
			getline(file, name, ' '); file >> ws; //Extract name, purge whitespace
			file >> population >> ws >> elevation; //Extract population and elevation
		}
		catch (ios_base::failure& e)
		{
			//Could not extract the required data. File malformed?
			cerr << "Error: City file contains malformed data at line "
					  << linePosition << "\n";
					  
			throw ios_base::failure("Unable to parse City file"); //throw to terminate
		}
		
		cities[code] = {code, name, population, elevation}; //follows format of CityInfo struct
		
		//Purge newline char, if it's there
		try
		{
			if (file.peek() == '\n') file.ignore();
		}
		catch (ios_base::failure& e)
		{
			//Check if we just ran out of data
			if (file.rdstate() == ifstream::eofbit)
			{
				//Only ran out of data, we're in a good spot to just stop reading
				++linePosition;
				break;
			}

			//Malformed data
			cerr << "Error: City file contains malformed data at end of line "
					  << linePosition << "\n";
					  
			throw ios_base::failure("Unable to parse City file"); //throw to terminate
		}
		
		++linePosition;
    }
    file.close();
}


void readRoadData(const string &filename, Graph &graph) {
	//Attempt to open the given file
    ifstream file(filename);
	
	//Register exceptions
	file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	
    if (!file.is_open()) {
        cerr << "Error: Unable to open road file\n";
        throw ios_base::failure("Unable to open city file"); //throw to terminate
    }

	//Read the file
	unsigned int linePosition = 0;
    while (file.good()) {
		//Data to read
        int from, to, distance;
		
		//Read data, purge whitespace
		try
		{
			file >> from >> ws >> to >> ws >> distance;
		}
		catch (ios_base::failure& e)
		{
			//Could not extract the required data. File malformed?
			cerr << "Error: Road file contains malformed data at line "
					  << linePosition << "\n";
					  
			throw ios_base::failure("Unable to parse Road file"); //throw to terminate
		}
		
		//Commit data to graph
        graph.addDirectedEdge(from, to, distance);
		
		//Purge newline char, if it's there
		try
		{
			if (file.peek() == '\n') file.ignore();
		}
		catch (ios_base::failure& e)
		{
			//Check if we just ran out of data
			if (file.rdstate() == ifstream::eofbit)
			{
				//Only ran out of data, we're in a good spot to just stop reading
				++linePosition;
				break;
			}

			//Malformed data
			cerr << "Error: Road file contains malformed data at end of line "
					  << linePosition << "\n";
					  
			throw ios_base::failure("Unable to parse road file"); //throw to terminate
		}
		
		++linePosition;
    }
    file.close();
}

vector<int> dijkstra(const Graph &graph, int src, int dest) {
    vector<int> distance(graph.numVerts, numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    distance[src] = 0;
    pq.push({0, src});
	
    while (!pq.empty()) {
		//Start out from the layer 0 node
        int u = pq.top().second;
        pq.pop();
		
		//Loop through all edges adjacent to the closest node (all nodes in the next layer)
        for (const auto &edge : graph.adjList[u]) {
			//Get a neighboring node and the cost to get to it
            int v = edge.to_vertex;
            int weight = edge.weight;
			
			//Check if it's cheaper than what we already knew, use it if it is
			if (distance[v] > distance[u] + weight) {
				distance[v] = distance[u] + weight;
				
				//Since it's cheaper, traverse through it to find more nodes (greedy)
				pq.push({distance[v], v});
			}
        }
    }
    return distance;
}

void printShortestRoute(const string &fromCity, const string &toCity, const vector<int> &shortestPath) {
    int from = cities[fromCity].code[0] - 'A';
    int to = cities[toCity].code[0] - 'A';
    if (shortestPath[to] == numeric_limits<int>::max()) {
        cout << "No route from " << fromCity << " to " << toCity << endl;
        return;
    }
    cout << "From City: " << cities[fromCity].name << ", population " << cities[fromCity].population
              << ", elevation " << cities[fromCity].elevation << endl;
    cout << "To City: " << cities[toCity].name << ", population " << cities[toCity].population
              << ", elevation " << cities[toCity].elevation << endl;
    cout << "The shortest distance from " << cities[fromCity].name << " to " << cities[toCity].name
              << " is " << shortestPath[to] << " through the route: ";
    vector<string> path;
    int current = to;
    while (current != from) {
        path.push_back(cities[current].name);
        current = shortestPath[current];
    }
    path.push_back(cities[fromCity].name);
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        if (it != path.rbegin()) {
            cout << "->";
        }
        cout << *it;
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <from_city_code> <to_city_code>\n";
        return EXIT_FAILURE;
    }
    string fromCity = argv[1];
    string toCity = argv[2];
    // Read city data from the file
    readCityData("city.txt");
    // Create a graph and read road data
    Graph graph(20); // Assuming 20 cities
    readRoadData("road.txt", graph);
    if (cities.find(fromCity) == cities.end() || cities.find(toCity) == cities.end()) {
        cerr << "Invalid city code\n";
        return EXIT_FAILURE;
    }
    int from = cities[fromCity].code[0] - 'A';
    int to = cities[toCity].code[0] - 'A';
    auto shortestPath = dijkstra(graph, from, to);
    printShortestRoute(fromCity, toCity, shortestPath);
    return EXIT_SUCCESS;
}