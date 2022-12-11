#include "graph.hpp"
#include <limits.h>



Graph::Graph(const std::string& file) {
    matrix.clear();
    std::ifstream data{file};
    std::string line;
    if (!data.good()) throw std::runtime_error("failed reading");

    // Data parsing
    while (std::getline(data, line)) {
        // seperate source and target
        std::vector<std::string> data = utilities::Split(line, ',');
        std::string source_subreddit = data.at(0);
        std::string target_subreddit = data.at(1);

        // store data into our Adjacency list(as well as the reversed one)
        matrix[source_subreddit].push_back(target_subreddit);
        reverse_matrix[target_subreddit].push_back(source_subreddit);

        // store all the vertices
        V.insert(source_subreddit);
        V.insert(target_subreddit);

        E.push_back(std::make_pair(source_subreddit, target_subreddit));
    }
}

/** The following functions are for the test purposes
*/
    /** Getter functions
    */
std::unordered_map<std::string, std::vector<std::string>> Graph::getMatrix() {
    return matrix;
}
std::unordered_map<std::string, std::vector<std::string>> Graph::getRMatrix() {
    return reverse_matrix;
}

    /** print all the sources and targets, along with all the edges
    */
void Graph::print1() {

    std::cout << "source:" << std::endl;
    for (std::pair<std::string, std::vector<std::string>> key_val : matrix)    
        std::cout << key_val.first << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::cout << "target:" << std::endl;
    for (std::pair<std::string, std::vector<std::string>> key_val : reverse_matrix)    
        std::cout << key_val.first << std::endl;
    std::cout << "-----------------------" << std::endl;

    for (std::pair<std::string, std::vector<std::string>> key_val : matrix) 
        for (std::string key_val_target : matrix[key_val.first])
            std::cout << key_val.first << "------->" << key_val_target << std::endl;
}

    /** print random source elements
    */
std::string Graph::print2() {
    return matrix.begin()->first;
}

    /** number of vertices
    */
int Graph::number_vertices() {
    return V.size();
}


/** BFS traversal for the graph with designated source and destination
    Return one of the shortest paths from startPoint to endPoint
*/
std::vector<std::string> Graph::BFS(std::string startPoint, std::string endPoint) {
    // if startPoint is not a source vertex return an empty vector
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
    // std::cout << max_path_length << std::endl;
    // if (max_path_length < 3) return std::vector<std::vector<std::string>>();
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
    
    double count = 0;
    for (std::string s : V) {
        for (std::string d : V) {
            if (s != point && d != point) {
                unsigned app = 0;
                unsigned len = load_path(s, d).size();
                for (std::vector<std::string> path : load_path(s, d)) 
                    if (std::find(path.begin(), path.end(), point) != path.end()) app++;
                if (len > 0)
                    count += static_cast<double>(app) / len;
                std::cout << count << std::endl;
            }
        }
    }
    // for (std::pair<std::string, std::vector<std::string>> key_val_source : matrix) {
    //     if (key_val_source.first != point) {
    //         for (std::pair<std::string, std::unordered_map<std::string, bool>> key_val_target : reverse_matrix) {
    //             if (key_val_target.first != point) {
    //                 unsigned betweenness = 0;
    //                 for (std::vector<std::string> path : load_path(key_val_source.first, key_val_target.first)) {
    //                     if (std::find(path.begin(), path.end(), point) != path.end()) betweenness++;
    //                 }
    //                 if (load_path(key_val_source.first, key_val_target.first).size() > 0)
    //                     count += static_cast<double>(betweenness) / load_path(key_val_source.first, key_val_target.first).size();
    //                 std::cout << count << std::endl;
    //             }
    //         }
    //     }
    // }
    // std::cout << betweenness << "      " << count << std::endl;
    return count;
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

std::string Graph::betweenness_centrality_opt() {

    // initialize the betweenness-centrality coefficient
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
        // std::cout << source << "  -----------------" << std::endl;
        // for (std::pair<std::string, std::vector<std::string>> key_val : pre) {
        //     std::cout << key_val.first << " ";
        //     for (std::string s : key_val.second) {
        //         std::cout << s << " ";
        //     }
        //     std::cout << std::endl;
        // }
        std::unordered_map<std::string, double> coefficients;

        for (std::string v : V)
            coefficients[v] = 0.0;

        while (!stack.empty()) {
            std::string point = stack.top();
            stack.pop();
            for (std::string w : pre[point]) {
                double co = (1 + coefficients[point]) * (static_cast<double>(paths[w])/paths[point]);
                coefficients[w] += co;
                // std::cout << "point:" << point << "   pre:" << w << "   co:" << co << std::endl;
            }
                

            if (point != source)
                centrality_coe[point] += coefficients[point];
        }
    }

    std::string ret = *(V.begin());

    for (std::string v : V) {
        if (centrality_coe[v] > centrality_coe[ret])
            ret = v;
    }
    // for (std::string v : V) {
    //     std::cout << "vertex: " << v << "    bc: " << centrality_coe[v] << std::endl;
    // }
    std::cout << centrality_coe[ret] << std::endl;
    return ret;

}


void Graph::partition(unsigned int n) {
    // the variable we want to set as our matrix after paritioning vertices in our big graph into a subgraph
    std::unordered_map<std::string, std::vector<std::string>> toAssign;
    std::unordered_set<std::string> Vi;
    std::vector<std::pair<std::string, std::string>> Ei;

    std::string curr;

    // for (int i = 0; i < 10; i++) {
    //     auto it = matrix.begin();
    //     std::random_device dev;
    //     std::mt19937 rng(dev());
    //     std::uniform_int_distribution<std::mt19937::result_type> dist2(0,matrix.size()-1);
    //     std::advance(it, dist2(rng));
    //     curr = it->first;
    //     std::cout << curr << std::endl;
    // }
    // n in the amount of verticies we want to have after a parition
    while (Vi.size() < n) {
        auto it = matrix.begin();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,matrix.size()-1);
        std::advance(it, dist2(rng));
        curr = it->first;

        while (toAssign.find(curr) != toAssign.end()) {
            auto it2 = matrix.begin();
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist2(0,matrix.size()-1);
            std::advance(it2, dist2(rng));
            curr = it2->first;
        }

        Vi.insert(curr);
        std::vector<std::string> toInsert;
        // std::random_device dev;
        // std::mt19937 rng(dev());
        // std::uniform_int_distribution<std::mt19937::result_type> dist2(0,matrix[curr].size()-1);
        int i = 10;
        if (matrix[curr].size() > 10)
            i = std::max(matrix[curr].size() / 10, matrix[curr].size());
        int count = 0;
        for (auto p : matrix[curr]) {
            // randomly create edges if a RNG generates an even number
            if (count == i) break;
            if (Vi.size() < n) {
                toInsert.push_back(p);
                Vi.insert(p);

                Ei.push_back(std::make_pair(curr, p));
                count++;
            }

        }

        toAssign.insert({curr, toInsert});
        // std::cout << toInsert.size() << std::endl;
    }
    matrix = toAssign;
    V = Vi;
    E = Ei;
    std::unordered_map<std::string, std::vector<std::string>> reverse_toAssign;
    for (std::pair<std::string, std::vector<std::string>> key_val : toAssign) {
        for (std::string new_s : key_val.second) {
            if (reverse_toAssign.find(new_s) == reverse_toAssign.end()) {
                reverse_toAssign[new_s].push_back(key_val.first);
            } else {
                if (std::find(reverse_toAssign[new_s].begin(), reverse_toAssign[new_s].end(), key_val.first) == reverse_toAssign[new_s].end())
                    reverse_toAssign[new_s].push_back(key_val.first);
            }
        }
    }
    reverse_matrix = reverse_toAssign;
}


std::vector<std::pair<std::string, std::string>>& Graph::getE() {
    return E;
}

std::unordered_set<std::string>& Graph::getV() {
    return V;
}

