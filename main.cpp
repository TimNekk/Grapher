#include <iostream>
#include "graphs/Graph.h"
#include "graphs/AdjacencyMatrix.h"

int main() {
    std::set<Edge> edges {
            {1, 2},
            {1, 4},
            {2, 3},
            {2, 4},
            {3, 2},
            {4, 1},
            {4, 3},
    };

    Graph g {edges};
    AdjacencyMatrix g2 {edges};

    std::cout << g.GetDegree(1);
}
