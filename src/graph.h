#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

struct Edge {
    int destination;
    double distance;
    double time;
};

class Graph {
private:
    std::unordered_map<int, std::vector<Edge>> adjList;
public:
    void addEdge(int sourceId, const Edge& edge);
    const std::vector<Edge>& getEdges(int nodeId) const;
    double getPathDistance(const std::vector<int>& path) const;
    double getPathTime(const std::vector<int>& path) const;
};

#endif // GRAPH_H
