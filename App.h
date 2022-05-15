#ifndef GRAPHER_APP_H
#define GRAPHER_APP_H


#include <iostream>
#include <fstream>
#include "Utilities.h"
#include "graphs/Graph.h"
#include "graphs/AdjacencyMatrix.h"
#include "graphs/IncidenceMatrix.h"
#include "graphs/AdjacencyList.h"
#include "graphs/EdgeList.h"

class App {
private:
    std::string input_file_name, output_file_name;

public:
    // Constructor
    App(const std::string &_input_file_name, const std::string &_output_file_name) {
        input_file_name = _input_file_name;
        output_file_name = _output_file_name;
    }

    // Main program loop
    [[noreturn]] void Start() {
        while (true) {
            Graph graph = GetGraph();

            bool continue_actions = true;
            while (continue_actions) {
                std::cout << "\n\n";
                unsigned int action = GetAction(graph);
                continue_actions = DoAction(action, graph);
            }
        }
    }

private:
    // Gets graph from user
    Graph GetGraph() {
        std::cout << "1) From console\n2) From file\n\nEnter input type:\n";
        unsigned int input_type;
        std::cin >> input_type;
        std::ifstream file_stream(input_file_name);
        std::istream &stream = input_type == 1 ? std::cin : file_stream;

        std::cout << "\n\n1) Input as Adjacency matrix\n";
        std::cout << "2) Input as Incidence matrix\n";
        std::cout << "3) Input as Adjacency list\n";
        std::cout << "4) Input as Edges list\n";
        std::cout << "\nEnter the graph type number:\n";

        unsigned int graph_type;
        std::cin >> graph_type;

        switch (graph_type) {
            case 1: {
                return GetAdjacencyMatrix(stream);
            }
            case 2: {
                return GetIncidenceMatrix(stream);
            }
            case 3: {
                return GetAdjacencyList(stream);
            }
            case 4: {
                return GetEdgeList(stream);
            }
        }
    }

    // Gets action number from user
    static unsigned int GetAction(const Graph &graph) {
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
        std::cout << "6) Show as Edge list\n";
        std::cout << "7) Enter new graph\n";
        std::cout << "8) Stop program\n";
        std::cout << "\nEnter the option number:\n";

        unsigned int action;
        std::cin >> action;
        return action;
    }

    // Does action that was passed
    bool DoAction(unsigned int action, const Graph &graph) {
        switch (action) {
            case 1: {
                std::cout << "Enter vertex (1-" << graph.vertices_count << "):\n";

                unsigned int vertex;
                std::cin >> vertex;
                std::cout << '\n';

                if (graph.is_directed) {
                    std::cout << "Indegree = " << graph.GetInDegree(vertex) << '\n';
                    std::cout << "Outdegree = " << graph.GetOutDegree(vertex) << '\n';
                } else {
                    std::cout << "Degree = " << graph.GetDegree(vertex) << '\n';
                }
                return true;
            }
            case 2: {
                if (graph.is_directed) {
                    std::cout << "Arcs count = " << graph.arcs_count << '\n';
                } else {
                    std::cout << "Edges count = " << graph.edges_count << '\n';
                }
                return true;
            }
            case 3: {
                OutputGraph(AdjacencyMatrix::FromGraph(graph));
                return true;
            }
            case 4: {
                OutputGraph(IncidenceMatrix::FromGraph(graph));;
                return true;
            }
            case 5: {
                OutputGraph(AdjacencyList::FromGraph(graph));
                return true;
            }
            case 6: {
                OutputGraph(EdgeList::FromGraph(graph));
                return true;
            }
            case 7: {
                return false;
            }
            case 8: {
                exit(0);
            }
        }
        return true;
    }

    // Outputs given graph to console of file
    template<class GraphType>
    void OutputGraph(const GraphType &graph) {
        std::cout << "1) To console\n2) To file\n\nEnter output type:\n";
        unsigned int output_type;
        std::cin >> output_type;
        std::ofstream file_stream(output_file_name);
        std::ostream &stream = output_type == 1 ? std::cout : file_stream;

        stream << "Representation as " << typeid(GraphType).name() << "\n\n" << graph;
    }

    // Gets Adjacency matrix from user
    static AdjacencyMatrix GetAdjacencyMatrix(std::istream &stream) {
        unsigned int vertex_count;
        unsigned int exist;
        std::set<Edge> edges;

        std::cout << "Enter the number of vertices:\n";
        stream >> vertex_count;
        std::cout << "Enter the adjacency matrix of size (" << vertex_count << "x" << vertex_count << "):\n";

        for (unsigned int i = 0; i < vertex_count; ++i) {
            for (unsigned int j = 0; j < vertex_count; ++j) {
                stream >> exist;

                if (exist == 1) {
                    edges.insert({i + 1, j + 1});
                }
            }
        }

        AdjacencyMatrix graph{edges};
        return graph;
    }

    // Gets Incidence matrix from user
    static IncidenceMatrix GetIncidenceMatrix(std::istream &stream) {
        unsigned int vertex_count, edges_count;
        int exist;
        std::set<Edge> edges;

        std::cout << "Enter the number of vertices:\n";
        stream >> vertex_count;
        std::cout << "Enter the number of edges/arcs:\n";
        stream >> edges_count;
        std::cout << "Enter the incidence matrix of size (" << vertex_count << "x" << edges_count << "):\n";

        std::vector<std::vector<int>> matrix = Utilities::FillVector2D(vertex_count, edges_count, 0);

        for (unsigned int i = 0; i < vertex_count; ++i) {
            for (unsigned int j = 0; j < edges_count; ++j) {
                stream >> exist;
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

        IncidenceMatrix graph{edges};
        return graph;
    }

    // Gets Adjacency list from user
    static AdjacencyList GetAdjacencyList(std::istream &stream) {
        unsigned int edges_count;
        unsigned int start, end;
        std::set<Edge> edges;

        std::cout << "Enter the number of edges:\n";
        stream >> edges_count;
        std::cout << "Enter " << edges_count << " pairs of start and end (e.g. 2 3):\n";

        for (int i = 0; i < edges_count; ++i) {
            stream >> start >> end;
            edges.insert({start, end});
        }

        AdjacencyList graph{edges};
        return graph;
    }

    // Gets Edge list from user
    static EdgeList GetEdgeList(std::istream &stream) {
        unsigned int vertices_count;
        unsigned int count, vertex;
        std::set<Edge> edges;

        std::cout << "Enter the number of vertices:\n";
        stream >> vertices_count;

        for (unsigned int i = 0; i < vertices_count; ++i) {
            std::cout << "Enter the number of connected vertices and the vertices themselves for vertex #" << i + 1
                      << ":\n";
            stream >> count;

            for (unsigned int j = 0; j < count; ++j) {
                stream >> vertex;
                edges.insert({i + 1, vertex});
            }
        }

        EdgeList graph{edges};
        return graph;
    }
};


#endif
