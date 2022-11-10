#include "utilities.hpp"

#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <map>
#include <list>

#include "edge.hpp"
#include "vertex.hpp"

class Graph {
public:
    Graph(const std::string& file);

private:
    std::map<std::string, bool>& GetAdjacencyMap(const std::string& source);
    std::map<std::string, std::map<std::string, bool>> matrix;
    
};



// list representation in case it's needed.
class GraphLists {                                          
    public:
        GraphLists(const std::string& file);

        struct Vertex {
            Vertex(std::string d, std::list<Edge> a) : data(d), adjacent(a) {}

            std::string data;
            std::list<Edge> adjacent;
            
        };

        struct Edge {
            Edge(Vertex* s, Vertex* e) : start(s), end(e) {}
            Edge(Vertex* s, Vertex* e, int w) : start(s), end(e), weight(w) {}

            int weight = 0;
            Vertex* start = NULL;
            Vertex* end = NULL;
        };


    private: 
        std::vector<Vertex*> vertices;
        std::list<Edge> edges;

};

