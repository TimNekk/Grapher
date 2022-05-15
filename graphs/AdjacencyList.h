#ifndef GRAPHER_ADJACENCYLIST_H
#define GRAPHER_ADJACENCYLIST_H

#include "Graph.h"
#include "map"


class AdjacencyList : public Graph {
public:
    std::map<unsigned int, std::set<unsigned int>> map;

public:
    // Constructor
    explicit AdjacencyList(const std::set<Edge> &_edges) : Graph(_edges) {
        for (const Edge &edge: _edges) {
            if (map.contains(edge.start)) {
                map[edge.start].insert(edge.end);
            } else {
                map[edge.start] = {edge.end};
            }
        }
    }

    // Converting from graph
    static AdjacencyList FromGraph(const Graph &graph) {
        AdjacencyList adjacency_list{graph.edges};
        return adjacency_list;
    }

    // Output override
    friend std::ostream &operator<<(std::ostream &os, const AdjacencyList &graph) {
        for (const auto &[start, ends]: graph.map) {
            os << start << ") ";

            for (const auto end: ends) {
                os << end << ", ";
            }

            os << '\n';
        }
        return os;
    }
};


#endif