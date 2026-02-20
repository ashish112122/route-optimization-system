# Smart Route Optimization System

A C++ program that models a city road network as a weighted directed graph and finds the fastest routes between intersections using Dijkstra's Algorithm and A*.

## Features

- Graph-based city map with intersections as nodes and roads as weighted edges
- Shortest path computation using Dijkstra's Algorithm and A*
- Dynamic simulation of real-world conditions:
  - Traffic congestion (increases road weight)
  - Road closures (removes a road entirely)
  - Emergency vehicle priority (reduces road weight by 30%)
- Side-by-side performance comparison of both algorithms (execution time + path cost)

## How to Run

You need a C++ compiler that supports C++17.

```bash
g++ -std=c++17 main.cpp -o route_optimizer
./route_optimizer
```

## Example Output

```
=== Shortest Paths — Dijkstra vs A* ===
CityHall -> Airport
  Dijkstra: CityHall -> Station -> School -> Airport  [cost: 1150]
  A*      : CityHall -> Station -> School -> Airport  [cost: 1150]

=== Simulation Scenarios ===
Traffic on Hospital->Market (x2.0) applied
Roadblock on Station->Park applied
Emergency priority on School->Airport (x0.7) applied
```

## Project Structure

Everything lives in a single `main.cpp` file, organized into sections:

- `Graph` — adjacency list with add, remove, and update edge operations
- `dijkstra` — min-heap based shortest path
- `aStar` — heuristic-guided shortest path using f(n) = g(n) + h(n)
- `Simulation` — applies traffic, roadblocks, and emergency priority to the graph
- `compare` / `report` — benchmarks both algorithms and prints results
