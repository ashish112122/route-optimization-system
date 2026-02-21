# Smart Route Optimization System

A graph-based route optimization system that simulates how emergency vehicles find the fastest path in a city under real-world constraints.

## Features

- Shortest path computation using **Dijkstra** and **A\*** algorithms
- Simulation of:
  - Traffic congestion (dynamic edge weights)
  - Road closures (edge removal)
  - Emergency vehicle prioritization
- Performance comparison between algorithms

## Concepts Used

- Graphs (Adjacency List)
- Priority Queue (Min Heap)
- Dijkstra's Algorithm
- A* Algorithm (Heuristics)

## Tech Stack

- C++17
- STL (priority_queue, unordered_map, vector)

## How to Run

```bash
g++ -std=c++17 main.cpp -o route_optimizer
./route_optimizer.exe
```

## Sample Output

```
=== Shortest Paths - Dijkstra vs A* ===
CityHall -> Airport
  Dijkstra: CityHall -> Hospital -> Market -> School -> Airport  [cost: 1080]
  A*      : CityHall -> Hospital -> Market -> School -> Airport  [cost: 1080]

=== Simulation Scenarios ===
Traffic on Hospital->Market (x2.0) applied
Roadblock on Station->Park applied
Emergency priority on School->Airport (x0.7) applied

=== Performance Comparison ===
Dijkstra | CityHall -> Airport | Cost: 1030 | Time: 27 us | OK
A*       | CityHall -> Airport | Cost: 1030 | Time: 21 us | OK
```
