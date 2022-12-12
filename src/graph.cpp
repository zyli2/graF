#include "graph.hpp"
#include <limits.h>

/** Constructor **/
Graph::Graph(const std::string& file) {
    targets_map.clear();
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
        targets_map[source_subreddit].push_back(target_subreddit);
        reverse_targets_map[target_subreddit].push_back(source_subreddit);

        // store all the vertices
        V.insert(source_subreddit);
        V.insert(target_subreddit);

        // store all the edges
        E.push_back(std::make_pair(source_subreddit, target_subreddit));
    }
}

/** The following functions are for the test purposes **/

    /** Getter functions **/
std::unordered_map<std::string, std::vector<std::string>> Graph::getTargets_map() {
    return targets_map;
}
std::unordered_map<std::string, std::vector<std::string>> Graph::getR_Targets_map() {
    return reverse_targets_map;
}

    /** print all the sources and targets, along with all the edges **/
void Graph::print1() {

    std::cout << "source:" << std::endl;
    for (std::pair<std::string, std::vector<std::string>> key_val : targets_map)    
        std::cout << key_val.first << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::cout << "target:" << std::endl;
    for (std::pair<std::string, std::vector<std::string>> key_val : reverse_targets_map)    
        std::cout << key_val.first << std::endl;
    std::cout << "-----------------------" << std::endl;

    for (std::pair<std::string, std::vector<std::string>> key_val : targets_map) 
        for (std::string key_val_target : targets_map[key_val.first])
            std::cout << key_val.first << "------->" << key_val_target << std::endl;
}

    /** print random source elements **/
std::string Graph::print2() {
    return targets_map.begin()->first;
}

    /** number of vertices **/
int Graph::number_vertices() {
    return V.size();
}

/** Get the adjacency list for one source vertex **/
std::vector<std::string>& Graph::GetAdjacencyList(const std::string& source) { 
    if (targets_map.find(source) == targets_map.end()) std::vector<std::string>();
    return targets_map[source];
}


/** BFS traversal for the graph with designated source and destination
 *   Return one of the shortest paths from startPoint to endPoint
 */
std::vector<std::string> Graph::BFS(std::string startPoint, std::string endPoint) {
    // if startPoint is not a source vertex return an empty vector
    if (targets_map.find(startPoint) == targets_map.end()) return std::vector<std::string>();

    std::queue<std::string> q;
    q.push(startPoint); 
    
    // the vector for the potential path, starting with the startPoint
    std::vector<std::string> path;
    path.push_back(startPoint);
    
    std::unordered_map<std::string, std::vector<std::string>> visited;
    visited[startPoint] = path;

    while (!q.empty()) {
        std::string point = q.front();
        q.pop();

        // if the point matches the endPoint, then we have found out one of the shortest path
        if (point == endPoint) {
            break;
        }

        // if the point doesn't have any outgoing edges, 
        //    then we move on to the next element in the queue
        if (targets_map.find(point) == targets_map.end()) continue;

        // traverse through all the vertices in the adjacency list
        for (std::string target : GetAdjacencyList(point)) {
            // determine if we have already visited this vertex
            // if we have visited this vertex,
            //     then the length of the existing path must be less or equal to the new path
            if (visited.find(target) == visited.end()) {
                // create a path ends at the new vertex based on the previous point
                std::vector<std::string> temp = visited[point];
                temp.push_back(target);
                visited[target] = temp;
                q.push(target);
            }
        }
    } 

    // if no path has been found
    if (visited.find(endPoint) == visited.end()) 
        return std::vector<std::string>();
    
    return visited[endPoint];
}

/** Degree centrality algorithm **/

int Graph::num_OutgoingEdges(std::string vertex) {
    if (targets_map.find(vertex) == targets_map.end()) return 0;
    return GetAdjacencyList(vertex).size();
}

int Graph::num_IncomingEdges(std::string vertex) {
    if (reverse_targets_map.find(vertex) == reverse_targets_map.end()) return 0;
    return reverse_targets_map[vertex].size();
}

/** Function for degree_centrality 
 *  Return the vertex with maximum degree centrality
 */
std::string Graph::degree_Centrality() {
    int ret_count = 0;
    std::string ret;
    for (std::pair<std::string, std::vector<std::string>> key_val : targets_map) {
        if (ret == key_val.first) continue;
        int temp_count = num_IncomingEdges(key_val.first) + num_OutgoingEdges(key_val.first);
        if (temp_count > ret_count) {
            ret = key_val.first;
            ret_count = temp_count;
        }   
    }
    for (std::pair<std::string, std::vector<std::string>> key_val : reverse_targets_map) {
        if (ret == key_val.first) continue;
        int temp_count = num_IncomingEdges(key_val.first) + num_OutgoingEdges(key_val.first);
        if (temp_count > ret_count) {
            ret = key_val.first;
            ret_count = temp_count;
        }   
    }
    return ret;
}

/** Betweenness centrality algorithm **/

    /** determine whether the vertex is already in the path **/
bool Graph::is_not_visited(std::string vertex, std::vector<std::string>& path) {
    for (unsigned i = 0; i < path.size(); i++) {
        if (path[i] == vertex) return false;
    }
    return true;
}

    /** load all the shortest paths from startPoint to endPoint 
     *  return a vector that stores all the paths
     */
std::vector<std::vector<std::string>> Graph::load_path(std::string startPoint, std::string endPoint) {
    if (targets_map.find(startPoint) == targets_map.end() || reverse_targets_map.find(endPoint) == reverse_targets_map.end()) return std::vector<std::vector<std::string>>();
    
    std::vector<std::vector<std::string>> ret;

    // note that queue stores paths not vertices
    std::queue<std::vector<std::string>> q;
    std::vector<std::string> path;
    path.push_back(startPoint);
    q.push(path);
    unsigned max_path_length = BFS(startPoint, endPoint).size();

    while (!q.empty()) {
        path = q.front();
        q.pop();

        // get the last vertex in the current path, and traverse its neighbors
        std::string last_vertex = path[path.size() - 1];

        // if the last vertex matches the endPoint,
        //      then we already find out one shortest path
        if (last_vertex == endPoint) {
            ret.push_back(path);
            continue;
        }

        // if the vertex doesn't have any neighbors,
        //      then the path ends here
        if (targets_map.find(last_vertex) == targets_map.end()) continue;

        // traverse through the neighbors of the last vertex
        for (std::string target : GetAdjacencyList(last_vertex)) {
            // determine if we need to add the target into the path
            if (is_not_visited(target, path) && path.size() < max_path_length) {
                std::vector<std::string> new_path(path);
                new_path.push_back(target);
                q.push(new_path);
            }
        }
    } 
    return ret;
}
    
    /** calculate betweenness centrality for one vertex **/
double Graph::betweenness_centrality(std::string point) {
    double count = 0;
    // if the vertex doesn't have any neighbors,
    //      then its betweenness centrality will be 0
    if (targets_map.find(point) == targets_map.end()) return count;

    // iterates all the possible pairs in the graph
    for (std::string s : V) {
        for (std::string d : V) {
            // the vertex can not be source nor destination 
            // and the shortest path contains at least one intermediate vertex
            if (s != point && d != point && BFS(s, d).size() > 2) {
                unsigned appearance = 0;
                unsigned len = load_path(s, d).size();
                
                for (std::vector<std::string> path : load_path(s, d)) 
                    if (std::find(path.begin(), path.end(), point) != path.end()) appearance++;

                count += static_cast<double>(appearance) / len;
            }
        }
    }
    return count;
}

    /** counting the number of shortest paths with a designated source vertex to all the possible destinations
     *  keep track of the predecessors of vertices
     *  modifying other data for further calculation
     */
void Graph::shortest_paths_count(std::string source, std::unordered_map<std::string, int>& dist, std::unordered_map<std::string, int>& paths, std::unordered_map<std::string, std::vector<std::string>>& pre, std::stack<std::string>& s) {
    // the distance from one vertex to itself will be 0
    // the number of shortest paths from one vertex to itself is 1
    dist[source] = 0;
    paths[source] = 1;
    
    std::queue<std::string> q;
    q.push(source);

    while (!q.empty()) {
        std::string point = q.front();
        q.pop();

        // push the vertex to stack in BFS order
        s.push(point);

        for (std::string adj : GetAdjacencyList(point)) {
            // if not visited
            if (dist[adj] < 0) {
                q.push(adj);
                dist[adj] = dist[point] + 1;
            }
            
            // if point is a predecessor of the adj
            if (dist[adj] == dist[point] + 1) {
                paths[adj] += paths[point];
                pre[adj].push_back(point);
            }
        }
    }
}

/** the purpose of this function is to calculate the number of shortest paths with a fixed source vertex
    leaving it for future test purpose
    need to modify some variables before using it
     
void Graph::find_paths(std::string source) {
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, int> paths;

    for (std::string v : V) {
        dist[v] = INT_MAX;
        paths[v] = 0;
    }

    shortest_paths_count(source, dist, paths);
        
    for (auto v : V) 
        std::cout << paths[v] << std::endl;
}

 */

    /** the optimized version of calculating betweenness centrality **/
std::unordered_map<std::string, double> Graph::betweenness_centrality_opt() {

    // initialize the betweenness-centrality coefficient
    std::unordered_map<std::string, double> centrality_coe;
    for (std::string v : V)
        centrality_coe[v] = 0.0;

    // traversing through all the source vertices
    for (std::string source : V) {
        std::stack<std::string> stack;
        std::unordered_map<std::string, std::vector<std::string>> pre;
        std::unordered_map<std::string, int> paths;
        std::unordered_map<std::string, int> dist;
        
        // we use distance from source to one vertex to determine if we have visited the vertex
        //    use paths to keep track of the number of shortest paths
        for (std::string v : V) {
            dist[v] = -1;
            paths[v] = 0;
        }

        // updating all the data
        shortest_paths_count(source, dist, paths, pre, stack);
       
        // betweenness coefficent for a vertex with a fixed source
        std::unordered_map<std::string, double> coefficients;
        for (std::string v : V)
            coefficients[v] = 0.0;

        while (!stack.empty()) {
            std::string point = stack.top();
            stack.pop();
            for (std::string w : pre[point]) {
                // the formula for betweenness centrality based on pair-dependency
                double co = (1 + coefficients[point]) * (static_cast<double>(paths[w])/paths[point]);
                coefficients[w] += co;
            }
                
            // sum up the coefficents with fixed source
            if (point != source)
                centrality_coe[point] += coefficients[point];
        }
    }

    /** This part is for finding the vertex with the biggest bc

    std::string ret = *(V.begin());

    for (std::string v : V) {
        if (centrality_coe[v] > centrality_coe[ret])
            ret = v;
    }
    std::cout << centrality_coe[ret] << std::endl;
    std::cout << ret << std::endl;
    }

    */

    return centrality_coe;
}

/** partition the current graph to a graph with n vertices **/
void Graph::partition(unsigned int n) {
    // the variable we want to set as our targets_map after paritioning vertices in our big graph into a subgraph
    std::unordered_map<std::string, std::vector<std::string>> toAssign;
    std::unordered_set<std::string> Vi;
    std::vector<std::pair<std::string, std::string>> Ei;

    std::string curr;

    // n in the amount of verticies we want to have after a parition
    while (Vi.size() < n) {
        auto it = targets_map.begin();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,targets_map.size()-1);
        std::advance(it, dist(rng));
        curr = it->first;

        while (toAssign.find(curr) != toAssign.end()) {
            auto it2 = targets_map.begin();
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist2(0,targets_map.size()-1);
            std::advance(it2, dist2(rng));
            curr = it2->first;
        }
        Vi.insert(curr);
        std::vector<std::string> toInsert;

        int i = 10;
        if (targets_map[curr].size() > 10)
            i = std::max(targets_map[curr].size() / 10, targets_map[curr].size());
        int count = 0;
        for (auto p : targets_map[curr]) {
            if (count == i) break;
            if (Vi.size() < n) {
                toInsert.push_back(p);
                Vi.insert(p);
                Ei.push_back(std::make_pair(curr, p));
                count++;
            }
        }
        toAssign.insert({curr, toInsert});
    }

    targets_map = toAssign;
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
    reverse_targets_map = reverse_toAssign;
}

/** Getter functions for Edges and Vertices **/
std::vector<std::pair<std::string, std::string>>& Graph::getE() {
    return E;
}

std::unordered_set<std::string>& Graph::getV() {
    return V;
}

