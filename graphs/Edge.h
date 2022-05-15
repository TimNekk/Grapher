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

    [[nodiscard]] bool IsArcWith(const Edge &other) const {
        return start == other.end && end == other.start;
    }
};


#endif