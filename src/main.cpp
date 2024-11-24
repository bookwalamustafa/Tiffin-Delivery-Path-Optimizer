#include <iostream>
#include "graph.h"
#include "dijkstra.h"
#include "astar.h"
#include "data_loader.h"

void displayMenu() {
    std::cout << "Welcome to the Tiffin Delivery Path Optimizer!\n\n";
    std::cout << "Please select an option:\n";
    std::cout << "1. Optimize for Distance using Dijkstra's Algorithm\n";
    std::cout << "2. Optimize for Time using Dijkstra's Algorithm\n";
    std::cout << "3. Optimize for Distance using A* Algorithm\n";
    std::cout << "4. Optimize for Time using A* Algorithm\n";
    std::cout << "5. Exit\n\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Graph graph;
    DataLoader::loadDistances(graph, "data/distances.csv");
    DataLoader::loadTimes(graph, "data/times.csv");

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 5) {
            std::cout << "Thank you for using the optimizer!\n";
            break;
        }

        int sourceId, destId;
        std::cout << "Enter Source Customer ID: ";
        std::cin >> sourceId;
        std::cout << "Enter Destination Customer ID: ";
        std::cin >> destId;

        std::vector<int> path;
        double totalCost = 0.0;

        switch (choice) {
            case 1:
                path = Dijkstra::findShortestPath(graph, sourceId, destId, true);
                totalCost = graph.getPathDistance(path);
                std::cout << "Optimized for Distance using Dijkstra's Algorithm.\n";
                break;
            case 2:
                path = Dijkstra::findShortestPath(graph, sourceId, destId, false);
                totalCost = graph.getPathTime(path);
                std::cout << "Optimized for Time using Dijkstra's Algorithm.\n";
                break;
            case 3:
                path = AStar::findShortestPath(graph, sourceId, destId, true);
                totalCost = graph.getPathDistance(path);
                std::cout << "Optimized for Distance using A* Algorithm.\n";
                break;
            case 4:
                path = AStar::findShortestPath(graph, sourceId, destId, false);
                totalCost = graph.getPathTime(path);
                std::cout << "Optimized for Time using A* Algorithm.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                continue;
        }

        if (path.empty()) {
            std::cout << "No path found between the specified customers.\n";
        } else {
            std::cout << "Optimal path: ";
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i];
                if (i != path.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << "\nTotal " << (choice % 2 == 1 ? "Distance: " : "Time: ") << totalCost << (choice % 2 == 1 ? " km\n" : " minutes\n");

            // Save results to CSV for Python scripts
            DataLoader::saveResults("results/route_data.csv", sourceId, destId, path, totalCost, choice);
        }

        std::cout << "\n";
    }

    return 0;
}
