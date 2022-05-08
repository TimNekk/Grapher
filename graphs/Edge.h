//
// Created by herew on 08.05.2022.
//

#ifndef GRAPHER_EDGE_H
#define GRAPHER_EDGE_H


struct Edge {
    unsigned int start;
    unsigned int end;

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge) {
        return os << edge.start << '\t' << edge.end;
    };

    bool operator<(const Edge &other) const {
        if (start == other.start) {
            return end < other.end;
        }
        return start < other.start;
    }
};


#endif //GRAPHER_EDGE_H
