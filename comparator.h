#pragma once

#include "astar.h"
#include "dijkstra.h"
#include "graph.h"

#include <chrono>
#include <sstream>
#include <string>
#include <vector>

struct RunResult {
    std::string algorithm;
    std::string source;
    std::string destination;
    double cost;
    long long timeUs;
    bool success;
};

std::pair<RunResult, RunResult> compare(const Graph& graph,
                                         const std::string& source,
                                         const std::string& destination) {
    auto zeroH = [](const std::string&) { return 0.0; };

    RunResult dResult, aResult;
    dResult.algorithm = "Dijkstra";
    aResult.algorithm = "A*";
    dResult.source = aResult.source = source;
    dResult.destination = aResult.destination = destination;

    {
        auto start = std::chrono::high_resolution_clock::now();
        PathResult r = dijkstra(graph, source, destination);
        auto end = std::chrono::high_resolution_clock::now();
        dResult.success = r.found;
        dResult.cost = r.cost;
        dResult.timeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        PathResult r = aStar(graph, source, destination, zeroH);
        auto end = std::chrono::high_resolution_clock::now();
        aResult.success = r.found;
        aResult.cost = r.cost;
        aResult.timeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    return {dResult, aResult};
}

std::string report(const std::vector<std::pair<RunResult, RunResult>>& results) {
    std::ostringstream oss;
    for (const auto& [d, a] : results) {
        for (const RunResult& r : {d, a}) {
            oss << r.algorithm
                << " | " << r.source << " -> " << r.destination
                << " | Cost: " << r.cost
                << " | Time: " << r.timeUs << " us"
                << " | " << (r.success ? "OK" : "FAILED") << "\n";
        }
    }
    return oss.str();
}
