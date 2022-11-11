#include "utilities.hpp"


#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>


class Graph {
public:
    Graph(const std::string& file);
    std::string print1();
    std::string print2();
    std::vector<std::string> BFS(std::string startPoint, std::string endPoint);
    int size();

private:
    std::unordered_map<std::string, bool>& GetAdjacencyMap(const std::string& source);
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> matrix;
    
};


