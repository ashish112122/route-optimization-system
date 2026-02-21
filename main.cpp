#include "comparator.h"
#include "graph.h"
#include "simulation.h"

#include <iostream>
#include <string>
#include <vector>

static void section(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

static void printPath(const std::string& label, const PathResult& result) {
    std::cout << label << ": ";
    if (!result.found) {
        std::cout << "(no path found)\n";
        return;
    }
    for (size_t i = 0; i < result.nodes.size(); ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << result.nodes[i];
    }
    std::cout << "  [cost: " << result.cost << "]\n";
}

int main() {
    std::cout << "Smart Route Optimization System\n";

    section("Building City Graph");

    Graph graph;
    graph.addEdge("CityHall", "Hospital",  300.0);
    graph.addEdge("CityHall", "Station",   500.0);
    graph.addEdge("Hospital", "Airport",   800.0);
    graph.addEdge("Hospital", "Market",    200.0);
    graph.addEdge("Airport",  "Port",      600.0);
    graph.addEdge("Station",  "Park",      150.0);
    graph.addEdge("Station",  "School",    250.0);
    graph.addEdge("Park",     "Market",    100.0);
    graph.addEdge("Market",   "School",    180.0);
    graph.addEdge("School",   "Airport",   400.0);
    graph.addEdge("School",   "Port",      700.0);
    graph.addEdge("Port",     "CityHall",  900.0);
    graph.addEdge("Market",   "CityHall",  350.0);

    std::cout << "Nodes and outgoing edges:\n";
    for (const auto& [node, edges] : graph.all()) {
        std::cout << "  " << node << " -> ";
        for (size_t i = 0; i < edges.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << edges[i].first << " (" << edges[i].second << "s)";
        }
        std::cout << "\n";
    }

    section("Shortest Paths — Dijkstra vs A*");

    auto zeroH = [](const std::string&) { return 0.0; };

    std::cout << "CityHall -> Airport\n";
    printPath("  Dijkstra", dijkstra(graph, "CityHall", "Airport"));
    printPath("  A*      ", aStar(graph, "CityHall", "Airport", zeroH));

    std::cout << "Station -> Port\n";
    printPath("  Dijkstra", dijkstra(graph, "Station", "Port"));
    printPath("  A*      ", aStar(graph, "Station", "Port", zeroH));

    std::cout << "Park -> CityHall\n";
    printPath("  Dijkstra", dijkstra(graph, "Park", "CityHall"));
    printPath("  A*      ", aStar(graph, "Park", "CityHall", zeroH));

    section("Simulation Scenarios");

    Simulation sim(graph);

    sim.applyTraffic("Hospital", "Market", 2.0);
    std::cout << "Traffic on Hospital->Market (x2.0) applied\n";

    sim.applyRoadblock("Station", "Park");
    std::cout << "Roadblock on Station->Park applied\n";

    sim.applyEmergencyPriority("School", "Airport");
    std::cout << "Emergency priority on School->Airport (x0.7) applied\n";

    std::cout << "\nUpdated weights:\n";
    std::cout << "  Hospital->Market : " << graph.getWeight("Hospital", "Market") << "s\n";
    std::cout << "  Station->Park    : " << (graph.getWeight("Station", "Park") < 0 ? "removed" : "still there") << "\n";
    std::cout << "  School->Airport  : " << graph.getWeight("School", "Airport") << "s\n";

    section("Shortest Paths After Simulations");

    std::cout << "CityHall -> Airport\n";
    printPath("  Dijkstra", dijkstra(graph, "CityHall", "Airport"));

    std::cout << "Station -> Port\n";
    printPath("  Dijkstra", dijkstra(graph, "Station", "Port"));

    section("Performance Comparison");

    std::vector<std::pair<std::string, std::string>> pairs = {
        {"CityHall", "Airport"},
        {"CityHall", "Port"},
        {"Station",  "Port"},
        {"Hospital", "CityHall"},
        {"Park",     "Airport"},
    };

    std::vector<std::pair<RunResult, RunResult>> results;
    for (const auto& [src, dst] : pairs) {
        results.push_back(compare(graph, src, dst));
    }
    std::cout << report(results);

    section("Done");
    return 0;
}
