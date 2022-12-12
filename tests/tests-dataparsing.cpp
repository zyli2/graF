#include <catch2/catch_test_macros.hpp>
#include "../src/graph.hpp"

// TEST_CASE("data-parsing-8-edge", "[weight=1][part=1]") {
//   Graph graph("../a.csv");


//   // Has now changed to adjacency list
//   REQUIRE( graph.getMatrix()["cs"]["225"] == true);
//   REQUIRE( graph.getMatrix()["225"]["graph"] == true);
//   REQUIRE( graph.getMatrix()["cs"]["128"] == true);
//   REQUIRE( graph.getMatrix()["cs"]["223"] == true);
//   REQUIRE( graph.getMatrix()["128"]["howdy"] == true);
//   REQUIRE( graph.getMatrix()["233"]["idk"] == true);
//   REQUIRE( graph.getMatrix()["howdy"]["texas"] == true);
//   REQUIRE( graph.getMatrix()["uiuc"]["cs"] == true);
// }

// TEST_CASE("data-parsing-8-vertex-source", "[weight=1][part=1]") {
//   Graph graph("../a.csv");

//   std::vector<std::string> source;
//   for (auto key_val : graph.getMatrix()) {
//     source.push_back(key_val.first);
//   }

//   REQUIRE(source.size() == 6);
// }

// TEST_CASE("data-parsing-8-vertex-target", "[weight=1][part=1]") {
//   Graph graph("../a.csv");

//   std::vector<std::string> target;
//   for (auto key_val : graph.getReverseMatrix()) {
//     target.push_back(key_val.first);
//   }

//   REQUIRE(target.size() == 8);
// }