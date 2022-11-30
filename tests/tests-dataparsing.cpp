#include <catch2/catch_test_macros.hpp>
#include <../src/graph.hpp>

TEST_CASE("data-parsing-8-edge", "[weight=1][part=1]") {
  Graph graph("../a.csv");

  REQUIRE( graph["cs"]["225"] == true);
  REQUIRE( graph["225"]["sucks"] == true);
  REQUIRE( graph["cs"]["128"] == true);
  REQUIRE( graph["cs"]["223"] == true);
  REQUIRE( graph["128"]["howdy"] == true);
  REQUIRE( graph["233"]["idk"] == true);
  REQUIRE( graph["howdy"]["texas"] == true);
  REQUIRE( graph["uiuc"]["cs"] == true);
}

TEST_CASE("data-parsing-8-vertex-source", "[weight=1][part=1]") {
  Graph graph("../a.csv");

  std::vector<std::string> source;
  for (auto key_val : graph.getMatrix()) {
    source.push_back(key_val.first);
  }

  REQUIRE(source.size() == 6);
}

TEST_CASE("data-parsing-8-vertex-target", "[weight=1][part=1]") {
  Graph graph("../a.csv");

  std::vector<std::string> target;
  for (auto key_val : graph.getReverseMatrix()) {
    target.push_back(key_val.first);
  }

  REQUIRE(source.size() == 8);
}