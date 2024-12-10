
# HW 6 Shortest Path Between Cities

## Members
- Kenneth Lopez
- Kerry Tran
- Sierra Brandt

## Design and Implementation
The program reads city and road data from input files, builds a graph representing the cities and
roads, and calculates the shortest path between two cities using Dijkstra's algorithm. It includes
error handling for invalid inputs and missing files and outputs the shortest distance and route.

## Problem Description
The problem is to find the shortest path between two cities based on road distances. The
program solves this by representing cities as graph vertices and roads as weighted edges,
using Dijkstra's algorithm to compute the shortest path.

## Program Design
The program uses a graph structure to represent cities and roads, implemented through the
Graph, Vertex, and Edge classes. We chose Dijkstra's algorithm because it efficiently finds the
shortest path in weighted graphs with non-negative weights. The classes encapsulate
graph-related data and operations, making the design modular and easy to maintain.

## System Implementation
The implementation reads data from city.txt and roads.txt, constructs the graph, and uses a
priority queue in Dijkstra's algorithm to calculate distances. Initially, issues like missing
predecessor tracking and improper file parsing were resolved by updating the algorithm and
adding robust error handling.

## Computational Complexity
Dijkstra's algorithm has a computational complexity of O((V+E)logV), where V is the number of
vertices (cities) and E is the number of edges (roads). This complexity comes from processing
all nodes and edges while maintaining a priority queue. This is acceptable for the problem
because the number of cities and roads is relatively small.

## Results
Did your results match the output in the “sampleresults.txt” file?
What are your answers to the following questions:
- The shortest distance and path from FI to GG - The shortest distance from IRWIN to GRPVE is 24 through the route: IRWIN->PARKER->GRPVE
- The shortest distance and path from PD to PM - The shortest distance from PARKER to POMONA is 133 through the route: PARKER->BOSSTOWN->TORRANCE->POMONA
- The shortest distance and path from PM to PD - The shortest distance from POMONA to PARKER is 357 through the route: POMONA->EDWIN->ANAHEIM->VICTORVILLE->CHINO->GRPVE->IRWIN->PARKER
- The Shortest distance and path from SB to PR - The shortest distance from BERNADINO to RIVERA is 152 through the route: BERNADINO->ISABELLA->BREA->CHINO->RIVERA

## Conclusion
The results matched the expected output of the test program, correctly displaying the shortest
distances and routes between cities. During implementation, issues included incorrectly parsed
input files, missing predecessor tracking in Dijkstra's algorithm, and handling invalid city codes.
These were resolved by improving file parsing, adding a predecessor vector for path
reconstruction, and enhancing error handling with debug outputs. These fixes ensured the
program's correctness and robustness.

## Appendix
See code files.
