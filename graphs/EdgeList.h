#ifndef GRAPHER_EDGELIST_H
#define GRAPHER_EDGELIST_H

#include "Graph.h"
#include "map"


class EdgeList : public Graph {
public:
    std::map<unsigned int, std::set<unsigned int>> map;

public:
    explicit EdgeList(const std::set<Edge> &_edges) : Graph(_edges) {
        for (const Edge &edge: _edges) {
            if (map.contains(edge.start)) {
                map[edge.start].insert(edge.end);
            } else {
                map[edge.start] = {edge.end};
            }
        }
    }

    static EdgeList FromGraph(const Graph &graph) {
        EdgeList edge_list{graph.edges};
        return edge_list;
    }

    friend std::ostream &operator<<(std::ostream &os, const EdgeList &graph) {
        for (const auto &[start, ends] : graph.map) {
            os << start << ") ";

            for (const auto end : ends) {
                os << end << ", ";
            }

            os << '\n';
        }
        return os;
    }
};


#endif