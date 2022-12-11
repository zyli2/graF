#pragma once

#include "utilities.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <cstdlib>
#include <set>


class Graph {
public:
    Graph(const std::string& file);
    std::unordered_set<std::string>& getV();
    std::vector<std::pair<std::string, std::string>>& getE();
    std::unordered_map<std::string, std::vector<std::string>> getMatrix();
    std::unordered_map<std::string, std::vector<std::string>> getRMatrix();
    void print1();
    std::string print2();
    std::vector<std::string> BFS(std::string startPoint, std::string endPoint);
    int number_vertices();
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
    std::string betweenness_centrality_opt();

    void partition(unsigned int n);

private:
    std::vector<std::string>& GetAdjacencyList(const std::string& source);
    std::unordered_map<std::string, std::vector<std::string>> matrix;
    std::unordered_map<std::string, std::vector<std::string>> reverse_matrix;
    std::unordered_set<std::string> V;
    std::vector<std::pair<std::string, std::string>> E;
};



