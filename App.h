#ifndef GRAPHER_APP_H
#define GRAPHER_APP_H


#include <iostream>
#include "Utilities.h"
#include "graphs/Graph.h"
#include "graphs/AdjacencyMatrix.h"
#include "graphs/IncidenceMatrix.h"
#include "graphs/AdjacencyList.h"

class App {
public:
    static void ShowMenu(const Graph& graph) {
        std::cout << "Options:\n";

        if (graph.is_directed) {
            std::cout << "1) Get Indgree and Outdegree\n";
            std::cout << "2) Get Arcs count\n";
        } else {
            std::cout << "1) Get Degree\n";
            std::cout << "2) Get Edges count\n";
        }

        std::cout << "3) Show as Adjacency matrix\n";
        std::cout << "4) Show as Incidence matrix\n";
        std::cout << "5) Show as Adjacency list\n";
        std::cout << "6) Show as Edges list\n";

        std::cout << "7) Enter new graph\n";

        std::cout << "\nEnter the option number:\n";
    }

    static void DoAction(unsigned int action, const Graph& graph) {
        switch (action) {
            case 1:
            {
                std::cout << "Enter vertex:\n";

                unsigned int vertex;
                std::cin >> vertex;
                std::cout << '\n';

                if (graph.is_directed) {
                    std::cout << "Indegree = " << graph.GetInDegree(vertex) << '\n';
                    std::cout << "Outdegree = " << graph.GetOutDegree(vertex) << '\n';
                } else {
                    std::cout << "Degree = " << graph.GetDegree(vertex) << '\n';
                }
                break;
            }
            case 2:
            {
                if (graph.is_directed) {
                    std::cout << "Arcs count = " << graph.arcs_count << '\n';
                } else {
                    std::cout << "Edges count = " << graph.edges_count << '\n';
                }
                break;
            }
            case 3:
            {
                std::cout << "Representation as Adjacency matrix\n\n" << AdjacencyMatrix::FromGraph(graph);
                break;
            }
            case 4:
            {
                std::cout << "Representation as Incidence matrix\n\n" << IncidenceMatrix::FromGraph(graph);
                break;
            }
            case 5:
            {
                std::cout << "Representation as Adjacency list\n\n" << AdjacencyList::FromGraph(graph);
                break;
            }
        }
    }

    static AdjacencyMatrix GetAdjacencyMatrix() {
        unsigned int vertex_count;
        unsigned int exist;
        std::set<Edge> edges;

        std::cout << "Enter the number of vertices:\n";
        std::cin >> vertex_count;
        std::cout << "Enter the adjacency matrix of size (" << vertex_count << "x" << vertex_count << "):\n";

        for (unsigned int i = 0; i < vertex_count; ++i) {
            for (unsigned int j = 0; j < vertex_count; ++j) {
                std::cin >> exist;

                if (exist == 1) {
                    edges.insert({i + 1, j + 1});
                }
            }
        }

        AdjacencyMatrix graph {edges};
        return graph;
    }

    static IncidenceMatrix GetIncidenceMatrix() {
        unsigned int vertex_count, edges_count;
        int exist;
        std::set<Edge> edges;

        std::cout << "Enter the number of vertices:\n";
        std::cin >> vertex_count;
        std::cout << "Enter the number of edges/arcs:\n";
        std::cin >> edges_count;
        std::cout << "Enter the incidence matrix of size (" << vertex_count << "x" << edges_count << "):\n";

        std::vector<std::vector<int>> matrix = Utilities::FillVector2D(vertex_count, edges_count, 0);

        for (unsigned int i = 0; i < vertex_count; ++i) {
            for (unsigned int j = 0; j < edges_count; ++j) {
                std::cin >> exist;
                matrix[i][j] = exist;
            }
        }

        for (unsigned int j = 0; j < edges_count; ++j) {
            unsigned int exist_start = 0, exist_start2 = 0, exist_end = 0;
            for (unsigned int i = 0; i < vertex_count; ++i) {
                if (matrix[i][j] == 1) {
                    if (exist_start == 0) {
                        exist_start = i + 1;
                    } else {
                        exist_start2 = i + 1;
                    }
                } else if (matrix[i][j] == -1) {
                    exist_end = i + 1;
                }
            }

            if (exist_end == 0) {
                edges.insert({exist_start, exist_start2});
                edges.insert({exist_start2, exist_start});
            } else {
                edges.insert({exist_start, exist_end});
            }
        }

        IncidenceMatrix graph {edges};
        return graph;
    }

    static AdjacencyList GetAdjacencyList() {
        unsigned int edges_count;
        unsigned int start, end;
        std::set<Edge> edges;

        std::cout << "Enter the number of edges:\n";
        std::cin >> edges_count;
        std::cout << "Enter " << edges_count << " pairs of start and end (e.g. 2 3):\n";

        for (int i = 0; i < edges_count; ++i) {
            std::cin >> start >> end;
            edges.insert({start, end});
        }

        AdjacencyList graph {edges};
        return graph;
    }
};


#endif
