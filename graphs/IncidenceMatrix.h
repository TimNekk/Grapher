#ifndef GRAPHER_INCIDENCEMATRIX_H
#define GRAPHER_INCIDENCEMATRIX_H

#include "Graph.h"
#include "vector"

class IncidenceMatrix : public Graph {
public:
    std::vector<std::vector<int>> matrix;

public:
    explicit IncidenceMatrix(const std::set<Edge> &_edges) : Graph(_edges) {
        for (unsigned int i = 0; i < vertices_count; ++i) {
            std::vector<int> row;
            row.reserve(vertices_count);
            for (int j = 0; j < edges_count - arcs_count; ++j) {
                row.push_back(0);
            }
            matrix.push_back(row);
        }

        std::set<Edge> added_edges;
        unsigned int count = 0;
        for (const Edge &edge: _edges) {
            if (added_edges.contains(edge)) {
                continue;
            }

            bool has_pair = false;

            for (const Edge &edge2: _edges) {
                if (!added_edges.contains(edge2) && edge.IsArcWith(edge2)) {
                    added_edges.insert(edge2);
                    has_pair = true;
                    break;
                }
            }

            matrix[edge.start - 1][count] = 1;
            matrix[edge.end - 1][count] = has_pair ? 1 : -1;
            added_edges.insert(edge);
            count++;
        }
    }

    static IncidenceMatrix FromGraph(const Graph &graph) {
        IncidenceMatrix incidence_matrix{graph.edges};
        return incidence_matrix;
    }

    friend std::ostream &operator<<(std::ostream &os, const IncidenceMatrix &graph) {
        for (int i = 0; i < graph.edges_count - graph.arcs_count; ++i) {
            os << '\t' << i + 1;
        }

        for (int i = 0; i < graph.vertices_count; ++i) {
            os << '\n' << i + 1;
            for (int j = 0; j < graph.edges_count - graph.arcs_count; ++j) {
                os << '\t' << graph.matrix[i][j];
            }
        }

        return os;
    }
};


#endif
