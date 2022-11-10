#include "utilities.hpp"

#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <map>

class Graph {
public:
    Graph(const std::string& file);

private:
    std::map<std::string, bool>& GetAdjacencyMap(const std::string& source);
    std::map<std::string, std::map<std::string, bool>> matrix;
    
};

