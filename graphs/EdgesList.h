#ifndef GRAPHER_EDGESLIST_H
#define GRAPHER_EDGESLIST_H

#include "Graph.h"
#include "map"


class EdgesList : public Graph {
public:
    std::map<unsigned int, std::set<unsigned int>> map;

public:
    explicit EdgesList(const std::set<Edge> &_edges) : Graph(_edges) {
        for (const Edge &edge: _edges) {
            if (map.contains(edge.start)) {
                map[edge.start].insert(edge.end);
            } else {
                map[edge.start] = {edge.end};
            }
        }
    }

    static EdgesList FromGraph(const Graph &graph) {
        EdgesList edges_list{graph.edges};
        return edges_list;
    }

    friend std::ostream &operator<<(std::ostream &os, const EdgesList &graph) {
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