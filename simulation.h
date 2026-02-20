#pragma once

#include "graph.h"

#include <string>

class Simulation {
public:
    Simulation(Graph& graph) : graph(graph) {}

    void applyTraffic(const std::string& from, const std::string& to, double factor) {
        double w = graph.getWeight(from, to);
        if (w > 0) graph.updateEdge(from, to, w * factor);
    }

    void applyRoadblock(const std::string& from, const std::string& to) {
        graph.removeEdge(from, to);
    }

    void applyEmergencyPriority(const std::string& from, const std::string& to) {
        double w = graph.getWeight(from, to);
        if (w > 0) graph.updateEdge(from, to, w * 0.7);
    }

private:
    Graph& graph;
};
