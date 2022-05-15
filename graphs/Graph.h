#ifndef GRAPHER_GRAPH_H
#define GRAPHER_GRAPH_H

#include <set>
#include "Edge.h"


class Graph {
public:
    std::set<Edge> edges;
    bool is_directed;

    unsigned int vertices_count;
    unsigned int edges_count;
    unsigned int arcs_count;

public:
    // Constructor
    explicit Graph(const std::set<Edge> &_edges) {
        edges = _edges;
        vertices_count = GetVerticesCount();
        is_directed = CheckDirectionality();
        edges_count = edges.size();
        arcs_count = GetArcsCount();
    }

    // Output override
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph) {
        os << "\tStart\tEnd\n";

        int count = 1;
        for (const Edge &edge: graph.edges) {
            os << count << ")\t" << edge << '\n';
            count++;
        }
        return os;
    }

    // Gets in degree of graph
    [[nodiscard]] unsigned int GetInDegree(unsigned int vertex) const {
        if (!HasVertex(vertex)) {
            throw std::invalid_argument("Wrong vertex passed");
        }

        unsigned int count = 0;

        for (const Edge &edge: edges) {
            count += edge.end == vertex;
        }

        return count;
    }

    // Gets out degree of graph
    [[nodiscard]] unsigned int GetOutDegree(unsigned int vertex) const {
        if (!HasVertex(vertex)) {
            throw std::invalid_argument("Wrong vertex passed");
        }

        unsigned int count = 0;

        for (const Edge &edge: edges) {
            count += edge.start == vertex;
        }

        return count;
    }

    // Gets degree of graph
    [[nodiscard]] unsigned int GetDegree(unsigned int vertex) const {
        if (!HasVertex(vertex)) {
            throw std::invalid_argument("Wrong vertex passed");
        }

        return GetInDegree(vertex) + GetOutDegree(vertex);
    }

private:
    // Gets number of arcs in graph
    unsigned int GetArcsCount() {
        unsigned int count = 0;

        for (auto edge1: edges) {
            for (const auto &edge2: edges) {
                if (edge1.IsArcWith(edge2)) {
                    count++;
                    break;
                }
            }
        }

        return count / 2;
    }

    // Checks if graph is directed
    bool CheckDirectionality() {
        for (auto edge1: edges) {
            bool found = false;

            for (const auto &edge2: edges) {
                if (edge1.IsArcWith(edge2)) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return true;
            }
        }

        return false;
    }

    // Gets number of vertices in graph
    unsigned int GetVerticesCount() {
        unsigned int max_vertex = 0;
        for (const Edge &edge: edges) {
            max_vertex = std::max(std::max(edge.start, edge.end), max_vertex);
        }
        return max_vertex;
    }

    // Checks if graph has given vertex
    [[nodiscard]] bool HasVertex(unsigned int vertex) const {
        return vertex != 0 && vertex <= vertices_count;
    }
};


#endif