#ifndef GRAPHER_UTILITIES_H
#define GRAPHER_UTILITIES_H


#include <vector>

class Utilities {
public:
    template<class T>
    static std::vector<std::vector<T>> FillVector2D(unsigned int rows_count, unsigned int columns_count, T fill_value) {
        std::vector<std::vector<T>> matrix;

        for (unsigned int i = 0; i < rows_count; ++i) {
            std::vector<int> row;
            row.reserve(columns_count);
            for (int j = 0; j < columns_count; ++j) {
                row.push_back(fill_value);
            }
            matrix.push_back(row);
        }

        return matrix;
    }
};


#endif
