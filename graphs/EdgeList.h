#ifndef GRAPHER_EDGELIST_H
#define GRAPHER_EDGELIST_H

#include "Graph.h"

class EdgeList : public Graph {
public:
    // Constructor
    explicit EdgeList(const std::set<Edge> &_edges) : Graph(_edges) {}

    // Converting from graph
    static EdgeList FromGraph(const Graph &graph) {
        EdgeList edge_list{graph.edges};
        return edge_list;
    }
};


#endif