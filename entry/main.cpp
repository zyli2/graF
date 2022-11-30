#include <iostream>

#include "../src/graph.hpp"
#include "../src/utilities.hpp"

int main() {

  Graph graph("../a.csv");
  std::vector<std::string> vect = graph.BFS("uiuc", "texas");
  // std::cout << graph.print1() << std::endl;
  // std::cout << graph.print2() << std::endl;
  for (std::string s : vect) 
    std::cout << s << "=>";
  
  std::cout << vect.size() << std::endl;
  return 0;
}