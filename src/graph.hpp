<<<<<<< HEAD
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

    /** Getter functions **/
    std::unordered_set<std::string>& getV();
    std::vector<std::pair<std::string, std::string>>& getE();
    std::unordered_map<std::string, std::vector<std::string>> getTargets_map();
    std::unordered_map<std::string, std::vector<std::string>> getR_Targets_map();

    /** Printer functions **/
    void print1();
    std::string print2();

    /** return the number of vertices in the graph */
    int number_vertices();

    std::vector<std::string> BFS(std::string startPoint, std::string endPoint);
    
    /** degree_centrality **/
    int num_OutgoingEdges(std::string vertex);
    int num_IncomingEdges(std::string vertex);
    std::string degree_Centrality();

    /** betweenness_centrality **/
    std::vector<std::vector<std::string>> load_path(std::string startPoint, std::string endPoint);
    bool is_not_visited(std::string vertex, std::vector<std::string>& path);
    double betweenness_centrality(std::string);


    void shortest_paths_count(std::string source, std::unordered_map<std::string, int>& dist, std::unordered_map<std::string, int>& paths, std::unordered_map<std::string, std::vector<std::string>>& pre, std::stack<std::string>& s);
    std::unordered_map<std::string, double> betweenness_centrality_opt();

    /** this function is invalid right now, but maybe it will be used for test purpose
    void find_paths(std::string source); 
     */
    
    /** partition **/
    void partition(unsigned int n);

private:
    std::vector<std::string>& GetAdjacencyList(const std::string& source);
    std::unordered_map<std::string, std::vector<std::string>> targets_map;
    std::unordered_map<std::string, std::vector<std::string>> reverse_targets_map;
    std::unordered_set<std::string> V;
    std::vector<std::pair<std::string, std::string>> E;
};



=======
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

    /** Getter functions **/
    std::unordered_set<std::string>& getV();
    std::vector<std::pair<std::string, std::string>>& getE();
    std::unordered_map<std::string, std::vector<std::string>> getTargets_map();
    std::unordered_map<std::string, std::vector<std::string>> getR_Targets_map();

    /** Printer functions **/
    void print1();
    std::string print2();

    /** return the number of vertices in the graph */
    unsigned number_vertices();

    std::vector<std::string> BFS(std::string startPoint, std::string endPoint);
    
    /** degree_centrality **/
    int num_OutgoingEdges(std::string vertex);
    int num_IncomingEdges(std::string vertex);
    std::string degree_Centrality();

    /** betweenness_centrality **/
    std::vector<std::vector<std::string>> load_path(std::string startPoint, std::string endPoint);
    bool is_not_visited(std::string vertex, std::vector<std::string>& path);
    double betweenness_centrality(std::string);


    void shortest_paths_count(std::string source, std::unordered_map<std::string, int>& dist, std::unordered_map<std::string, int>& paths, std::unordered_map<std::string, std::vector<std::string>>& pre, std::stack<std::string>& s);
    std::unordered_map<std::string, double> betweenness_centrality_opt();

    /** this function is invalid right now, but maybe it will be used for test purpose
    void find_paths(std::string source); 
     */
    
    /** partition **/
    void partition(unsigned int n);

private:
    std::vector<std::string>& GetAdjacencyList(const std::string& source);
    std::unordered_map<std::string, std::vector<std::string>> targets_map;
    std::unordered_map<std::string, std::vector<std::string>> reverse_targets_map;
    std::unordered_set<std::string> V;
    std::vector<std::pair<std::string, std::string>> E;
};



>>>>>>> 1a00dfe22018f88c890b4f932c4f0f674671a586
