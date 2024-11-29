#include "dijkstra.h"
#include <queue>
#include <unordered_map>
#include <limits>

struct NodeInfo {
    int nodeId;
    double cost;
    bool operator>(const NodeInfo& other) const {
        return cost > other.cost;
    }
};

std::vector<int> Dijkstra::findShortestPath(const Graph& graph, int sourceId, int destinationId, bool optimizeForDistance) {
    std::priority_queue<NodeInfo, std::vector<NodeInfo>, std::greater<NodeInfo>> pq;
    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> previous;

    distances[sourceId] = 0.0;
    pq.push({sourceId, 0.0});

    while (!pq.empty()) {
        NodeInfo current = pq.top();
        pq.pop();

        if (current.nodeId == destinationId) {
            break;
        }

        for (const auto& edge : graph.getEdges(current.nodeId)) {
            double weight = optimizeForDistance ? edge.distance : edge.time;
            double newDist = distances[current.nodeId] + weight;

            if (distances.find(edge.destination) == distances.end() || newDist < distances[edge.destination]) {
                distances[edge.destination] = newDist;
                previous[edge.destination] = current.nodeId;
                pq.push({edge.destination, newDist});
            }
        }
    }

    // Reconstruct path
    std::vector<int> path;
    int currentNode = destinationId;
    while (previous.find(currentNode) != previous.end()) {
        path.push_back(currentNode);
        currentNode = previous[currentNode];
    }

    if (currentNode != sourceId) {
        return {}; // No path found
    }

    path.push_back(sourceId);
    std::reverse(path.begin(), path.end());
    return path;
}
