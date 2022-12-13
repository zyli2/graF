#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "../src/graph.hpp"
#include "../src/drawing.hpp"

TEST_CASE("BFS-a-dataset", "[weight=1][part=1]") {
  Graph graph("../tests/a.csv");

  std::vector<std::string> vect1 = graph.BFS("uiuc", "texas");
  std::vector<std::string> ans1 = {"uiuc","cs","128","howdy","texas"};
  std::vector<std::string> vect2 = graph.BFS("uiuc", "graph");
  
  // Making sure the path is correct
  REQUIRE( vect1.at(3) == ans1.at(3) );
  REQUIRE( vect1.at(4) == ans1.at(4) );

  // Making sure the length of the path is correct
  REQUIRE( vect1.size() == 5 );
  REQUIRE( vect2.size() == 4 );

  // Edge case 1: When either the starting point or destination is not valid 
  std::vector<std::string> vect3 = graph.BFS("error", "texas");
  std::vector<std::string> vect4 = graph.BFS("texas", "error");
  REQUIRE( vect3.size() == 0 );
  REQUIRE( vect4.size() == 0 );

  // Edge case 2: When there's no path between two nodes
  std::vector<std::string> vect5 = graph.BFS("idk", "233");
  std::vector<std::string> vect6 = graph.BFS("Howdy", "cs");
  REQUIRE( vect5.size() == 0 );
  REQUIRE( vect6.size() == 0 );
}

TEST_CASE("getTargets_map()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");
    std::unordered_map<std::string, std::vector<std::string>> matrix = graph.getTargets_map();

    // Calling on an invalid node
    std::vector<std::string> vect = matrix["CS"];
    REQUIRE( vect.size() == 0);

    // Making sure the vector is the right size
    std::vector<std::string> vect1 = matrix["cs"];
    std::vector<std::string> vect2 = matrix["idk"];
    REQUIRE( vect1.size() == 3);
    REQUIRE( vect2.size() == 0); // No neighbor

    // Making sure the vector contains the right neighbors
    std::vector<std::string>::iterator it;

    REQUIRE( std::find(vect1.begin(), vect1.end(), "225") != vect1.end());
    REQUIRE( std::find(vect1.begin(), vect1.end(), "128") != vect1.end());
    REQUIRE( std::find(vect1.begin(), vect1.end(), "233") != vect1.end());
    REQUIRE( std::find(vect1.begin(), vect1.end(), "Howdy") == vect1.end());
}

TEST_CASE("getR_Targets_map()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");
    std::unordered_map<std::string, std::vector<std::string>> matrix = graph.getR_Targets_map();

    // Calling on an invalid node
    std::vector<std::string> vect = matrix["CS"];
    REQUIRE( vect.size() == 0);

    // Making sure the vector is the right size
    std::vector<std::string> vect1 = matrix["128"];
    std::vector<std::string> vect2 = matrix["225"];
    REQUIRE( vect1.size() == 1);
    REQUIRE( vect2.size() == 1); // No neighbor

    // Making sure the vector contains the right neighbors
    std::vector<std::string>::iterator it;

    REQUIRE( std::find(vect1.begin(), vect1.end(), "cs") != vect1.end());
    REQUIRE( std::find(vect1.begin(), vect1.end(), "texas") == vect1.end());
}

TEST_CASE("num_OutgoingEdges()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");

    // Calling on an invalid node
    int node_count = graph.num_OutgoingEdges("CS");
    REQUIRE( node_count == 0);

    int node_count1 = graph.num_OutgoingEdges("cs");
    int node_count2 = graph.num_OutgoingEdges("idk"); // No outgoing edge

    REQUIRE( node_count1 == 3);
    REQUIRE( node_count2 == 0);
}

TEST_CASE("num_IncomingEdges()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");

    // Calling on an invalid node
    int node_count = graph.num_IncomingEdges("CS");
    REQUIRE( node_count == 0);

    int node_count1 = graph.num_IncomingEdges("texas");
    int node_count2 = graph.num_IncomingEdges("idk");
    int node_count3 = graph.num_IncomingEdges("uiuc"); // No incoming edge

    REQUIRE( node_count1 == 2);
    REQUIRE( node_count2 == 1);
    REQUIRE( node_count3 == 0);
}

// Optimized version of betweenness centrality
TEST_CASE("betweenness_centrality_opt()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");

    std::unordered_map<std::string, double> map = graph.betweenness_centrality_opt();

    // Invalid input
    REQUIRE( map["CS"] == 0.0);

    REQUIRE( map["cs"] == 8.0);
    REQUIRE( map["idk"] == 0.0);
    REQUIRE( map["225"] == 4.0);
}

TEST_CASE("betweenness_centrality()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");

    // Testing for invalid input
    double num0 = graph.betweenness_centrality("CS");

    double num1 = graph.betweenness_centrality("cs");
    double num2 = graph.betweenness_centrality("uiuc");

    REQUIRE( num0 == 0.0);
    REQUIRE( num1 == 8.0);
    REQUIRE( num2 == 0.0); 
}

TEST_CASE("degree_Centrality()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");

    // Testing for invalid input
    std::string string = graph.degree_Centrality();

    REQUIRE( string == "cs" );
}


TEST_CASE("number_vertices()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");

    unsigned int num = graph.number_vertices();
    REQUIRE( num == 10 );
}

TEST_CASE("getE()", "[weight=1][part=1]") {
    Graph graph("../tests/a.csv");
    std::vector<std::pair<std::string, std::string>> vect = graph.getE();

    REQUIRE( vect.size() == 10);
}


TEST_CASE("BFS-b-dataset", "[weight=1][part=1]") {
  Graph graph("../tests/b.csv");

  std::vector<std::string> vect1 = graph.BFS("0", "6");
  std::vector<std::string> vect2 = graph.BFS("2", "5");

  REQUIRE( vect1.size() == 5 );
  REQUIRE( vect2.size() == 3 );
}

// This test case will run for around 2 minutes
// TEST_CASE("Betweenness-Centrality-Big", "[weight=1][part=1]") {
//   Graph graph("../data/ttt.csv");

//   REQUIRE( graph.betweenness_centrality("dogecoin") == graph.betweenness_centrality_opt()["dogecoin"] );
// }
