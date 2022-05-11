#ifndef GRAPHER_ADJACENCYMATRIX_H
#define GRAPHER_ADJACENCYMATRIX_H

#include "Graph.h"
#include "vector"


class AdjacencyMatrix : Graph {
public:
    std::vector<std::vector<bool>> matrix;

public:
    explicit AdjacencyMatrix(const std::set<Edge> &_edges) : Graph(_edges) {
        for (unsigned int i = 0; i < vertices_count; ++i) {
            std::vector<bool> row;
            row.reserve(vertices_count);
            for (int j = 0; j < vertices_count; ++j) {
                row.push_back(false);
            }
            matrix.push_back(row);
        }

        for (const Edge &edge: _edges) {
            matrix[edge.start - 1][edge.end - 1] = true;
        }
    }

    static AdjacencyMatrix FromGraph(const Graph &graph) {
        AdjacencyMatrix adjacency_matrix{graph.edges};
        return adjacency_matrix;
    }

    friend std::ostream &operator<<(std::ostream &os, const AdjacencyMatrix &graph) {
        for (int i = 0; i < graph.vertices_count; ++i) {
            os << '\t' << i + 1;
        }

        for (int i = 0; i < graph.vertices_count; ++i) {
            os << '\n' << i + 1;
            for (int j = 0; j < graph.vertices_count; ++j) {
                os << '\t' << graph.matrix[i][j];
            }
        }

        return os;
    }

};


#endif