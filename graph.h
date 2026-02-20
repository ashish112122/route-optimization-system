#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Graph {
public:
    void addEdge(const std::string& from, const std::string& to, double weight) {
        adj[from].emplace_back(to, weight);
        if (adj.find(to) == adj.end()) adj[to] = {};
    }

    void removeEdge(const std::string& from, const std::string& to) {
        auto it = adj.find(from);
        if (it == adj.end()) return;
        auto& neighbors = it->second;
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(),
                [&to](const std::pair<std::string, double>& e) { return e.first == to; }),
            neighbors.end());
    }

    void updateEdge(const std::string& from, const std::string& to, double newWeight) {
        auto it = adj.find(from);
        if (it == adj.end()) return;
        for (auto& edge : it->second) {
            if (edge.first == to) {
                edge.second = newWeight;
                return;
            }
        }
    }

    double getWeight(const std::string& from, const std::string& to) const {
        auto it = adj.find(from);
        if (it == adj.end()) return -1.0;
        for (const auto& edge : it->second) {
            if (edge.first == to) return edge.second;
        }
        return -1.0;
    }

    bool hasNode(const std::string& node) const {
        return adj.find(node) != adj.end();
    }

    const std::vector<std::pair<std::string, double>>& neighbors(const std::string& node) const {
        return adj.at(node);
    }

    const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& all() const {
        return adj;
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adj;
};
