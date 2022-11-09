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
        matrix[source_subreddit][target_subreddit] =
            matrix[target_subreddit][source_subreddit] = true;
    }
}

std::map<std::string, bool>& Graph::GetAdjacencyMap(const std::string& source) { return matrix[source];}
