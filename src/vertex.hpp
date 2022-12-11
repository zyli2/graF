#pragma once

#include <vector>
struct Vertex {

    // two 'vectors' for forces
    Vertex() ;
    
    Vertex(std::string source_name, int x_, int y_) : x(x_), y(y_),  source(source_name) {}

    int x = 0;
    int y = 0;
    int radius = 3;
    std::string source;
    int disp = 0;
    int pos = 0;
    friend bool operator==(const Vertex& lhs, const Vertex& rhs) { return lhs.source == rhs.source;}  
    friend bool operator<(const Vertex& lhs, const Vertex& rhs) { return lhs.source < rhs.source;}  
    
};