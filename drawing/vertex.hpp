#include <vector>
struct Vertex {

    // two vectors for forces

    Vertex(std::string source_name, int x, int y);

    int radius = 3;
    std::string source_name;
    int disp = 0;
    int pos = 0;
       
};