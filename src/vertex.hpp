#include "Edge.hpp"

struct Vertex {
            Vertex(std::string d, std::list<Edge> a) : data(d), adjacent(a) {}

            std::string data;
            std::list<Edge> adjacent;
            
        };