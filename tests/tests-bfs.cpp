#include <catch2/catch_test_macros.hpp>
#include <../src/graph.hpp>

TEST_CASE("BFS-a-dataset", "[weight=1][part=1]") {
  Graph graph("../a.csv");

  std::vector<std::string> vect1 = graph.BFS("uiuc", "texas");
  std::vector<std::string> ans1 = {"uiuc","cs","128","howdy","texas"};
  std::vector<std::string> vect2 = graph.BFS("uiuc", "graph");

  REQUIRE( vect1.at(3) == ans1.at(3) );
  REQUIRE( vect1.at(4) == ans1.at(4) );
  REQUIRE( vect2.size() == 4 );
}

TEST_CASE("BFS-b-dataset", "[weight=1][part=1]") {
  Graph graph("../b.csv");

  std::vector<std::string> vect1 = graph.BFS("0", "6");
  std::vector<std::string> vect2 = graph.BFS("2", "5");

  REQUIRE( vect1.size() == 5 );
  REQUIRE( vect2.size() == 3 );
}