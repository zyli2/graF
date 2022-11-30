#include "graph.hpp"

Graph::Graph(const std::string& file) {
    matrix.clear();
    std::ifstream data{file};
    std::string line;
    if (!data.good()) throw std::runtime_error("failed reading");
    while (std::getline(data, line)) {
        std::vector<std::string> data = utilities::Split(line, ',');
        std::string source_subreddit = data.at(0);
        std::string target_subreddit = data.at(1);
        matrix[source_subreddit][target_subreddit] = true;
        reverse_matrix[target_subreddit][source_subreddit] = true;
    }
}

std::string Graph::print1() {
    return matrix.begin()->first;
}

std::string Graph::print2() {
    return matrix.begin()->second.begin()->first;
}
int Graph::size() {
    int count = 0;
    for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : matrix) count+=key_val.second.size();
    return count;
}
std::vector<std::string> Graph::BFS(std::string startPoint, std::string endPoint) {
    if (matrix.find(startPoint) == matrix.end()) return std::vector<std::string>();
    std::queue<std::string> q;
    std::unordered_map<std::string,std::vector<std::string>> visited;
    q.push(startPoint); 
    std::vector<std::string> path;
    path.push_back(startPoint);
    visited[startPoint] = path;
    while (!q.empty()) {
        std::string point = q.front();
        q.pop();
        if (point == endPoint) {
            break;
        }
        if (matrix.find(point) == matrix.end()) continue;
        for (std::pair<std::string, bool> target : GetAdjacencyMap(point)) {
            if (visited.find(target.first) == visited.end()) {
                std::vector<std::string> temp = visited[point];
                temp.push_back(target.first);
                visited[target.first] = temp;
                q.push(target.first);
            }
        }
    } 
    if (visited.find(endPoint) == visited.end()) 
        return std::vector<std::string>();
    
    return visited[endPoint];      
         
}

int Graph::num_OutgoingEdges(std::string vertex) {
    return GetAdjacencyMap(vertex).size();
}


int Graph::num_IncomingEdges(std::string vertex) {
    if (reverse_matrix.find(vertex) == reverse_matrix.end()) return 0;
    return reverse_matrix[vertex].size();
}

std::string Graph::degree_Centrality() {
    int ret_count = 0;
    std::string ret;
    for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : matrix) {
        if (ret == key_val.first) continue;
        int temp_count = num_IncomingEdges(key_val.first) + num_OutgoingEdges(key_val.first);
        if (temp_count > ret_count) {
            ret = key_val.first;
            ret_count = temp_count;
        }   
    }
    for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : reverse_matrix) {
        if (ret == key_val.first) continue;
        int temp_count = num_IncomingEdges(key_val.first) + num_OutgoingEdges(key_val.first);
        if (temp_count > ret_count) {
            ret = key_val.first;
            ret_count = temp_count;
        }   
    }
    return ret;
}

std::unordered_map<std::string, bool>& Graph::GetAdjacencyMap(const std::string& source) { 
    if (matrix.find(source) == matrix.end()) std::unordered_map<std::string, bool>();
    return matrix[source];
}

std::unordered_map<std::string, std::unordered_map<std::string, bool>> Graph::getMatrix() [
    return matrix;
]

std::unordered_map<std::string, std::unordered_map<std::string, bool>> Graph::getReverseMatrix() {
    return reverse_matrix;
}