#pragma once

#include <vector>
#include <vector>
struct Vertex {

    Vertex(std::string sourcename, int x, int y_) :  x(x), y(y_), source(sourcename){}

    int x = 0;
    int y = 0;

    std::string source;
    double bc_coeff = 1;


    friend bool operator==(const Vertex& lhs, const Vertex& rhs) { return lhs.source == rhs.source;}
    friend bool operator<(const Vertex& lhs, const Vertex& rhs) { return lhs.source <= rhs.source;}     //for using a set to store vertex objects

}; 