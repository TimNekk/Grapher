#ifndef GRAPHER_APP_H
#define GRAPHER_APP_H


#include <iostream>
#include "graphs/Graph.h"
#include "graphs/AdjacencyMatrix.h"
#include "graphs/IncidenceMatrix.h"

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
};


#endif
