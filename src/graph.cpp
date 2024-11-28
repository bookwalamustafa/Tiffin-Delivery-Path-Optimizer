#include "graph.h"

void Graph::addEdge(int sourceId, const Edge& edge) {
    adjList[sourceId].push_back(edge);
}

const std::vector<Edge>& Graph::getEdges(int nodeId) const {
    static const std::vector<Edge> empty;
    auto it = adjList.find(nodeId);
    if (it != adjList.end()) {
        return it->second;
    } else {
        return empty;
    }
}

double Graph::getPathDistance(const std::vector<int>& path) const {
    double totalDistance = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int source = path[i];
        int dest = path[i + 1];
        for (const auto& edge : adjList.at(source)) {
            if (edge.destination == dest) {
                totalDistance += edge.distance;
                break;
            }
        }
    }
    return totalDistance;
}

double Graph::getPathTime(const std::vector<int>& path) const {
    double totalTime = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int source = path[i];
        int dest = path[i + 1];
        for (const auto& edge : adjList.at(source)) {
            if (edge.destination == dest) {
                totalTime += edge.time;
                break;
            }
        }
    }
    return totalTime;
}
