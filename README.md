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
Smart Route Optimization System

=== Building City Graph ===
Nodes and outgoing edges:
  School -> Airport (400s), Port (700s)
  Park -> Market (100s)
  Port -> CityHall (900s)
  Market -> School (180s), CityHall (350s)
  Airport -> Port (600s)
  Station -> Park (150s), School (250s)
  Hospital -> Airport (800s), Market (200s)
  CityHall -> Hospital (300s), Station (500s)

=== Shortest Paths - Dijkstra vs A* ===
CityHall -> Airport
  Dijkstra: CityHall -> Hospital -> Market -> School -> Airport  [cost: 1080]
  A*      : CityHall -> Hospital -> Market -> School -> Airport  [cost: 1080]
Station -> Port
  Dijkstra: Station -> School -> Port  [cost: 950]
  A*      : Station -> School -> Port  [cost: 950]
Park -> CityHall
  Dijkstra: Park -> Market -> CityHall  [cost: 450]
  A*      : Park -> Market -> CityHall  [cost: 450]

=== Simulation Scenarios ===
Traffic on Hospital->Market (x2.0) applied
Roadblock on Station->Park applied
Emergency priority on School->Airport (x0.7) applied

Updated weights:
  Hospital->Market : 400s
  Station->Park    : removed
  School->Airport  : 280s

=== Shortest Paths After Simulations ===
CityHall -> Airport
  Dijkstra: CityHall -> Station -> School -> Airport  [cost: 1030]
Station -> Port
  Dijkstra: Station -> School -> Port  [cost: 950]

=== Performance Comparison ===
Dijkstra | CityHall -> Airport  | Cost: 1030 | Time: 27 us | OK
A*       | CityHall -> Airport  | Cost: 1030 | Time: 21 us | OK
Dijkstra | CityHall -> Port     | Cost: 1450 | Time: 21 us | OK
A*       | CityHall -> Port     | Cost: 1450 | Time: 20 us | OK
Dijkstra | Station -> Port      | Cost: 950  | Time: 11 us | OK
A*       | Station -> Port      | Cost: 950  | Time: 11 us | OK
Dijkstra | Hospital -> CityHall | Cost: 750  | Time: 15 us | OK
A*       | Hospital -> CityHall | Cost: 750  | Time: 14 us | OK
Dijkstra | Park -> Airport      | Cost: 560  | Time: 18 us | OK
A*       | Park -> Airport      | Cost: 560  | Time: 18 us | OK

=== Done ===
```
