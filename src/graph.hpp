#pragma once


#include "utilities.hpp"


#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>


#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <map>

class Graph {
public:
    Graph(const std::string& file);
    std::string print1();
    std::string print2();
    std::vector<std::string> BFS(std::string startPoint, std::string endPoint);
    int size();
    int num_OutgoingEdges(std::string vertex);
    int num_IncomingEdges(std::string vertex);
    std::string degree_Centrality();
    std::string Graph::closeness_Centrality();
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> getMatrix();
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> getReverseMatrix();


private:
    std::vector<std::string>& GetAdjacencyList(const std::string& source);
    std::unordered_map<std::string, std::vector<std::string>> matrix;
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> reverse_matrix;

};

