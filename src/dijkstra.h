#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <vector>

namespace Dijkstra {
    std::vector<int> findShortestPath(const Graph& graph, int sourceId, int destinationId, bool optimizeForDistance);
}

#endif // DIJKSTRA_H
