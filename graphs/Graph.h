//
// Created by herew on 08.05.2022.
//

#ifndef GRAPHER_GRAPH_H
#define GRAPHER_GRAPH_H


#include <set>
#include "Edge.h"


class Graph {
public:
    std::set<Edge> edges;
    unsigned int vertices_count;

public:
    explicit Graph(const std::set<Edge> &_edges) {
        edges = _edges;
        vertices_count = GetVerticesCount();
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph &graph) {
        os << "\tStart\tEnd\n";

        int count = 1;
        for (const Edge &edge: graph.edges) {
            os << count << ")\t" << edge << '\n';
            count++;
        }
        return os;
    }

    unsigned int GetInDegree(unsigned int vertex) {
        if (!HasVertex(vertex)) {
            throw std::invalid_argument("Wrong vertex passed");
        }

        unsigned int count = 0;

        for (const Edge& edge : edges) {
            count += edge.end == vertex;
        }

        return count;
    }

    unsigned int GetDegree(unsigned int vertex) {
        if (!HasVertex(vertex)) {
            throw std::invalid_argument("Wrong vertex passed");
        }

        return GetInDegree(vertex) + GetOutDegree(vertex);
    }

    unsigned int GetOutDegree(unsigned int vertex) {
        if (!HasVertex(vertex)) {
            throw std::invalid_argument("Wrong vertex passed");
        }

        unsigned int count = 0;

        for (const Edge& edge : edges) {
            count += edge.start == vertex;
        }

        return count;
    }

private:
    unsigned int GetVerticesCount() {
        unsigned int max_vertex = 0;
        for (const Edge &edge: edges) {
            max_vertex = std::max(std::max(edge.start, edge.end), max_vertex);
        }
        return max_vertex;
    }

    bool HasVertex(unsigned int vertex) {
        return vertex != 0 && vertex <= vertices_count;
    }
};


#endif //GRAPHER_GRAPH_H
