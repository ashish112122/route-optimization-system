#pragma once

#include "graph.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct PathResult {
    std::vector<std::string> nodes;
    double cost;
    bool found;
};

static std::vector<std::string> reconstructPath(
    const std::unordered_map<std::string, std::string>& parent,
    const std::string& source,
    const std::string& destination) {

    std::vector<std::string> path;
    std::string current = destination;

    while (current != source) {
        path.push_back(current);
        current = parent.at(current);
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return path;
}

PathResult dijkstra(const Graph& graph, const std::string& source, const std::string& destination) {
    if (!graph.hasNode(source) || !graph.hasNode(destination)) {
        return {{}, -1.0, false};
    }

    std::unordered_map<std::string, double> dist;
    for (const auto& [node, _] : graph.all()) {
        dist[node] = std::numeric_limits<double>::infinity();
    }
    dist[source] = 0.0;

    std::unordered_map<std::string, std::string> parent;
    std::priority_queue<
        std::pair<double, std::string>,
        std::vector<std::pair<double, std::string>>,
        std::greater<>> pq;
    pq.push({0.0, source});

    while (!pq.empty()) {
        auto [cost, current] = pq.top();
        pq.pop();

        if (cost > dist[current]) continue;
        if (current == destination) break;

        for (const auto& [neighbor, weight] : graph.neighbors(current)) {
            double newCost = dist[current] + weight;
            if (newCost < dist[neighbor]) {
                dist[neighbor] = newCost;
                parent[neighbor] = current;
                pq.push({newCost, neighbor});
            }
        }
    }

    if (dist[destination] == std::numeric_limits<double>::infinity()) {
        return {{}, -1.0, false};
    }

    return {reconstructPath(parent, source, destination), dist[destination], true};
}
