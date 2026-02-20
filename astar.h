#pragma once

#include "dijkstra.h"
#include "graph.h"

#include <functional>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

PathResult aStar(const Graph& graph,
                 const std::string& source,
                 const std::string& destination,
                 std::function<double(const std::string&)> heuristic) {

    if (!graph.hasNode(source) || !graph.hasNode(destination)) {
        return {{}, -1.0, false};
    }

    std::unordered_map<std::string, double> gCost;
    for (const auto& [node, _] : graph.all()) {
        gCost[node] = std::numeric_limits<double>::infinity();
    }
    gCost[source] = 0.0;

    std::unordered_map<std::string, std::string> parent;
    std::priority_queue<
        std::pair<double, std::string>,
        std::vector<std::pair<double, std::string>>,
        std::greater<>> pq;
    pq.push({heuristic(source), source});

    while (!pq.empty()) {
        auto [f, current] = pq.top();
        pq.pop();

        if (current == destination) break;

        for (const auto& [neighbor, weight] : graph.neighbors(current)) {
            double tentativeG = gCost[current] + weight;
            if (tentativeG < gCost[neighbor]) {
                gCost[neighbor] = tentativeG;
                parent[neighbor] = current;
                pq.push({tentativeG + heuristic(neighbor), neighbor});
            }
        }
    }

    if (gCost[destination] == std::numeric_limits<double>::infinity()) {
        return {{}, -1.0, false};
    }

    return {reconstructPath(parent, source, destination), gCost[destination], true};
}
