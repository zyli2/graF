#pragma once

#include <vector>
struct Vertex {

    Vertex(std::string sourcename, int x, int y_) : source(sourcename), x(x), y(y_) {}

    int x;
    int y;

    std::string source;
    double bc_coeff;

    int radius = 3 * bc_coeff;

    friend bool operator==(const Vertex& lhs, const Vertex& rhs) { return lhs.source == rhs.source;}
    friend bool operator<(const Vertex& lhs, const Vertex& rhs) { return lhs.bc_coeff < rhs.bc_coeff;}
}; 