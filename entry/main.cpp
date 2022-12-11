#include <iostream>
#include "../src/Image.h"
#include "../cs225/PNG.h"
#include "../src/graph.hpp"
#include "../src/utilities.hpp"

using namespace cs225;
int main() {

  Graph graph("../a.csv");
  std::vector<std::string> vect = graph.BFS("uiuc", "texas");
  // std::cout << graph.print1() << std::endl;
  // std::cout << graph.print2() << std::endl;
  for (std::string s : vect) 
    std::cout << s << "=>";
  
  std::cout << vect.size() << std::endl;
  
  Image image = Image();
  image.readFromFile("white.png");

  Drawing drawing = Drawing(image, 50);
 
  drawing.testDraw()
  
  drawing.writeToFile("../tests/example.png");

  return 0;
}