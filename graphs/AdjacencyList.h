#ifndef GRAPHER_ADJACENCYLIST_H
#define GRAPHER_ADJACENCYLIST_H

#include "Graph.h"
#include "vector"

class AdjacencyList : public Graph {
public:
    explicit AdjacencyList(const std::set<Edge> &_edges) : Graph(_edges) {}

    static AdjacencyList FromGraph(const Graph &graph) {
        AdjacencyList adjacency_list{graph.edges};
        return adjacency_list;
    }
};


#endif