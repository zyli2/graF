

#include <vector>
struct Vertex {

    // two 'vectors' for forces
    
    Vertex(std::string source_name, int x_, int y_) : source(source_name), x(x_), y(y_) {}

    int x;
    int y;
    int radius = 3;
    std::string source;
    int disp = 0;
    int pos = 0;
    friend bool operator==(const Vertex& lhs, const Vertex& rhs) { return lhs.source == rhs.source;}   
};