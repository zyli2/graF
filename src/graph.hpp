#pragma once

#include "utilities.hpp"

#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

class Graph {
public:
    Graph(const std::string& file);
    // std::unordered_map<std::string, std::unordered_map<std::string, bool>> getMatrix();
    // std::unordered_map<std::string, std::unordered_map<std::string, bool>> getRMatrix();
    std::vector<std::string>& getV();
    std::vector<std::pair<std::string, std::string>>& getE();
    // void print1();
    // std::string print2();
    std::vector<std::string> BFS(std::string startPoint, std::string endPoint);
    // int size();
    // void test();
    
    // /** degree_centrality**/
    // int num_OutgoingEdges(std::string vertex);
    // int num_IncomingEdges(std::string vertex);
    // std::string degree_Centrality();

    /** betweenness_centrality**/
    std::vector<std::vector<std::string>> load_path(std::string startPoint, std::string endPoint);
    bool is_not_visited(std::string vertex, std::vector<std::string>& path);
    double betweenness_centrality(std::string);
    void shortest_paths_count(std::string source, std::unordered_map<std::string, int>& dist, std::unordered_map<std::string, int>& paths, std::unordered_map<std::string, std::vector<std::string>>& pre, std::stack<std::string>& s);
    // void find_paths(std::string source);
    void betweenness_centrality_opt();



private:
    std::vector<std::string>& GetAdjacencyList(const std::string& source);
    std::unordered_map<std::string, std::vector<std::string>> matrix;
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> reverse_matrix;\
    std::unordered_set<std::string> V;
    std::vector<std::pair<std::string, std::string>> E;
};



