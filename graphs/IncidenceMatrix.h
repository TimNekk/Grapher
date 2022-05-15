#ifndef GRAPHER_INCIDENCEMATRIX_H
#define GRAPHER_INCIDENCEMATRIX_H

#include "Graph.h"
#include "vector"

class IncidenceMatrix : public Graph {
public:
    std::vector<std::vector<int>> matrix;

public:
    // Constructor
    explicit IncidenceMatrix(const std::set<Edge> &_edges) : Graph(_edges) {
        // Filling vector with zeros
        matrix = Utilities::FillVector2D(vertices_count, edges_count - arcs_count, 0);

        std::set<Edge> added_edges;
        unsigned int count = 0;
        for (const Edge &edge: _edges) {
            if (added_edges.contains(edge)) {
                continue;
            }

            bool has_pair = false;

            // Find pair edge
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

    // Converting from graph
    static IncidenceMatrix FromGraph(const Graph &graph) {
        IncidenceMatrix incidence_matrix{graph.edges};
        return incidence_matrix;
    }

    // Output override
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
