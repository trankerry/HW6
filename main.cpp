#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include "graph.h" // Include your graph header file here

struct CityInfo {
    std::string code;
    std::string name;
    int population;
    int elevation;
};

std::unordered_map<std::string, CityInfo> cities;
void readCityData(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open city file\n";
        exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id, population, elevation;
        std::string code, name;
        iss >> id >> code >> name >> population >> elevation;
        cities[code] = {code, name, population, elevation};
    }
    file.close();
}

void readRoadData(const std::string &filename, Graph &graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open road file\n";
        exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int from, to, distance;
        iss >> from >> to >> distance;
        graph.addDirectedEdge(from, to, distance);
    }
    file.close();
}

std::vector<int> dijkstra(const Graph &graph, int src, int dest) {
    std::vector<int> distance(graph.numVerts, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    distance[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (const auto &edge : graph.adjList[u]) {
            int v = edge.to_vertex;
            int weight = edge.weight;
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

void printShortestRoute(const std::string &fromCity, const std::string &toCity, const std::vector<int> &shortestPath) {
    int from = cities[fromCity].code[0] - 'A';
    int to = cities[toCity].code[0] - 'A';
    if (shortestPath[to] == std::numeric_limits<int>::max()) {
        std::cout << "No route from " << fromCity << " to " << toCity << std::endl;
        return;
    }
    std::cout << "From City: " << cities[fromCity].name << ", population " << cities[fromCity].population
              << ", elevation " << cities[fromCity].elevation << std::endl;
    std::cout << "To City: " << cities[toCity].name << ", population " << cities[toCity].population
              << ", elevation " << cities[toCity].elevation << std::endl;
    std::cout << "The shortest distance from " << cities[fromCity].name << " to " << cities[toCity].name
              << " is " << shortestPath[to] << " through the route: ";
    std::vector<std::string> path;
    int current = to;
    while (current != from) {
        path.push_back(cities[current].name);
        current = shortestPath[current];
    }
    path.push_back(cities[fromCity].name);
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        if (it != path.rbegin()) {
            std::cout << "->";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <from_city_code> <to_city_code>\n";
        return EXIT_FAILURE;
    }
    std::string fromCity = argv[1];
    std::string toCity = argv[2];
    // Read city data from the file
    readCityData("city.txt");
    // Create a graph and read road data
    Graph graph(20); // Assuming 20 cities
    readRoadData("road.txt", graph);
    if (cities.find(fromCity) == cities.end() || cities.find(toCity) == cities.end()) {
        std::cerr << "Invalid city code\n";
        return EXIT_FAILURE;
    }
    int from = cities[fromCity].code[0] - 'A';
    int to = cities[toCity].code[0] - 'A';
    auto shortestPath = dijkstra(graph, from, to);
    printShortestRoute(fromCity, toCity, shortestPath);
    return EXIT_SUCCESS;
}