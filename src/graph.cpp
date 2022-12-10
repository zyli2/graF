#include "graph.hpp"

#include <limits.h>

Graph::Graph(const std::string& file) {
    matrix.clear();
    std::ifstream data{file};
    std::string line;
    if (!data.good()) throw std::runtime_error("failed reading");
    while (std::getline(data, line)) {
        std::vector<std::string> data = utilities::Split(line, ',');
        std::string source_subreddit = data.at(0);
        std::string target_subreddit = data.at(1);
        matrix[source_subreddit].push_back(target_subreddit);
        reverse_matrix[target_subreddit][source_subreddit] = true;
        V.insert(source_subreddit);
        V.insert(target_subreddit);

        E.insert(std::make_pair(source_subreddit, target_subreddit));
    }
}

// std::unordered_map<std::string, std::unordered_map<std::string, bool>> Graph::getMatrix() {
//     return matrix;
// }
// std::unordered_map<std::string, std::unordered_map<std::string, bool>> Graph::getRMatrix() {
//     return reverse_matrix;
// }
// void Graph::print1() {
//     std::cout << "source:" << std::endl;
//     for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : matrix)    
//         std::cout << key_val.first << std::endl;
//     std::cout << "-----------------------" << std::endl;

//     std::cout << "target:" << std::endl;
//     for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : reverse_matrix)    
//         std::cout << key_val.first << std::endl;
//     std::cout << "-----------------------" << std::endl;

//     for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : matrix) 
//         for (std::pair<std::string, bool> key_val_target : key_val.second)
//             std::cout << key_val.first << "------->" << key_val_target.first << std::endl;
// }

// std::string Graph::print2() {
//     return matrix.begin()->second.begin()->first;
// }

// int Graph::size() {
//     int count = 0;
//     for (std::pair<std::string, std::vector<std::string>> key_val : matrix) count+=key_val.second.size();
//     return count;
// }

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
         for (std::string target : GetAdjacencyList(point)) {
            if (visited.find(target) == visited.end()) {
                std::vector<std::string> temp = visited[point];
                temp.push_back(target);
                visited[target] = temp;
                q.push(target);
            }
        }
    } 
    if (visited.find(endPoint) == visited.end()) 
        return std::vector<std::string>();
    
    return visited[endPoint];      
         
}

// int Graph::num_OutgoingEdges(std::string vertex) {
//     return GetAdjacencyMap(vertex).size();
// }


// int Graph::num_IncomingEdges(std::string vertex) {
//     if (reverse_matrix.find(vertex) == reverse_matrix.end()) return 0;
//     return reverse_matrix[vertex].size();
// }

// std::string Graph::degree_Centrality() {
//     int ret_count = 0;
//     std::string ret;
//     for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : matrix) {
//         if (ret == key_val.first) continue;
//         int temp_count = num_IncomingEdges(key_val.first) + num_OutgoingEdges(key_val.first);
//         if (temp_count > ret_count) {
//             ret = key_val.first;
//             ret_count = temp_count;
//         }   
//     }
//     for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val : reverse_matrix) {
//         if (ret == key_val.first) continue;
//         int temp_count = num_IncomingEdges(key_val.first) + num_OutgoingEdges(key_val.first);
//         if (temp_count > ret_count) {
//             ret = key_val.first;
//             ret_count = temp_count;
//         }   
//     }
//     return ret;
// }

std::vector<std::string>& Graph::GetAdjacencyList(const std::string& source) { 
    if (matrix.find(source) == matrix.end()) std::vector<std::string>();
    return matrix[source];
}

bool Graph::is_not_visited(std::string vertex, std::vector<std::string>& path) {
    for (unsigned i = 0; i < path.size(); i++) {
        if (path[i] == vertex) return false;
    }
    return true;
}

std::vector<std::vector<std::string>> Graph::load_path(std::string startPoint, std::string endPoint) {
    if (matrix.find(startPoint) == matrix.end() || reverse_matrix.find(endPoint) == reverse_matrix.end()) return std::vector<std::vector<std::string>>();
    
    std::vector<std::vector<std::string>> ret;

    std::queue<std::vector<std::string>> q;
    std::vector<std::string> path;
    path.push_back(startPoint);
    q.push(path);
    unsigned max_path_length = BFS(startPoint, endPoint).size();
    std::cout << max_path_length << std::endl;
    if (max_path_length > 3) return std::vector<std::vector<std::string>>();
    while (!q.empty()) {
        path = q.front();
        q.pop();
        std::string last_vertex = path[path.size() - 1];

        if (last_vertex == endPoint) {
            ret.push_back(path);
            continue;
        }

        if (matrix.find(last_vertex) == matrix.end()) continue;

        for (std::string target : GetAdjacencyList(last_vertex)) {
            if (is_not_visited(target, path) && path.size() < max_path_length) {
                std::vector<std::string> new_path(path);
                new_path.push_back(target);
                q.push(new_path);
            }
        }
    } 
    return ret;
}
    

double Graph::betweenness_centrality(std::string point) {
    unsigned long betweenness = 0;
    unsigned long count = 0;
    for (std::pair<std::string, std::vector<std::string>> key_val_source : matrix) {
        if (key_val_source.first != point) {
            for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val_target : reverse_matrix) {
                if (key_val_target.first != point) {
                    for (std::vector<std::string> path : load_path(key_val_source.first, key_val_target.first)) {
                        if (path.size() < 3) continue;
                        if (std::find(path.begin(), path.end(), point) != path.end()) betweenness++;
                        count++;
                    }
                }
            }
        }
    }
    std::cout << betweenness << "      " << count << std::endl;
    return static_cast<double>(betweenness) / count;
}


void Graph::shortest_paths_count(std::string source, std::unordered_map<std::string, int>& dist, std::unordered_map<std::string, int>& paths, std::unordered_map<std::string, std::vector<std::string>>& pre, std::stack<std::string>& s) {
    dist[source] = 0;
    paths[source] = 1;
    
    std::queue<std::string> q;
    q.push(source);

    while (!q.empty()) {
        std::string point = q.front();
        q.pop();
        s.push(point);
        for (std::string adj : GetAdjacencyList(point)) {
            // if not visited
            if (dist[adj] < 0) {
                q.push(adj);
                dist[adj] = dist[point] + 1;
            }
            
            // if point is on the shortest path bewteen source and adj
            if (dist[adj] == dist[point] + 1) {
                paths[adj] += paths[point];
                pre[adj].push_back(point);
            }
        }
    }
}

// void Graph::find_paths(std::string source) {
//     std::unordered_map<std::string, int> dist;
//     std::unordered_map<std::string, int> paths;

//     for (std::string v : V) {
//         dist[v] = INT_MAX;
//         paths[v] = 0;
//     }

//     shortest_paths_count(source, dist, paths);
        
//     for (auto v : V) 
//         std::cout << paths[v] << std::endl;
// }

// void Graph::test() {
//     for (auto v : V) {
//         if (matrix.find(v) != matrix.end())
//             find_paths(v);
//     }
// }

void Graph::betweenness_centrality_opt() {

    std::unordered_map<std::string, double> centrality_coe;
    for (std::string v : V)
        centrality_coe[v] = 0.0;

    for (std::string source : V) {
        std::stack<std::string> stack;
        std::unordered_map<std::string, std::vector<std::string>> pre;
        std::unordered_map<std::string, int> paths;
        std::unordered_map<std::string, int> dist;
        
        for (std::string v : V) {
            dist[v] = -1;
            paths[v] = 0;
        }

        shortest_paths_count(source, dist, paths, pre, stack);

        std::unordered_map<std::string, double> coefficients;

        for (std::string v : V)
            coefficients[v] = 0.0;

        while (!stack.empty()) {
            std::string point = stack.top();
            stack.pop();
            for (std::string w : pre[point])
                coefficients[w] += (1 + coefficients[point]) * (static_cast<double>(paths[w])/paths[point]);

            if (point != source)
                centrality_coe[point] += coefficients[point];
        }
    }

    // for (std::string v : V) {
    //     std::cout << "vertex: " << v << "    bc: " << centrality_coe[v] << std::endl;
    // }

}


std::unordered_set<std::pair<std::string, std::string>>& Graph::getE() {
    return E;
}