<<<<<<< HEAD
#include <iostream>
#include "../src/Image.h"
#include "../cs225/PNG.h"
#include "../src/graph.hpp"
#include "../src/utilities.hpp"
#include "../src/drawing.hpp"

using namespace cs225;
int main() {

  char decision;

  std::cout << "Do you want to see how our program on our reddit dataset or yours? Enter o for ours or y for yours" << std::endl;
  std::cout << "Enter o or y: ";

  std::cin >> decision;

  if (decision == 'y') {

    std::string data = "";

    std::cout << "Enter your dataset's name: ";

    std::cin.ignore();
    std::getline(std::cin, data);

    std::string dest = "../data/";

    dest += data;

    Graph graph(dest);

    char graf;
    std::cout << "Do you want to produce a graph, find the vertex with the highest betweenness centrality or find the shortest path between two vertices?" << std::endl;
    std::cout << "Enter g for graph, b for betweenness centrality or p for shortest path: ";
    std::cin >> graf;

    if (graf == 'g') {
      std::cout << "Producing image..." << std::endl;
      // enter the graph drawing code

      std::cout << "Image complete! it is in the graF directory and it's named output.png" << std::endl;
    } else if (graf == 'p') {
      std::string vertex1;
      std::string vertex2;

      std::cout << "Enter vertex 1: ";

      std::cin.ignore();
      std::getline(std::cin, vertex1);

      std::cout << "Enter vertex 2: ";

      std::cin.ignore();
      std::getline(std::cin, vertex2);

      std::cout << "if the output is blank, that means one of the vertices does not exist in your dataset" << std::endl;

      std::cout << "Shortest path is: " << std::endl;
    } else {
      // enter betweenness centrality code
    }

    std::cout << "The program has finished running. To run the program again, enter ./main in the terminal" << std::endl;
    std::cout << "Thank you!" << std::endl;

  } else if (decision == 'o') {

    Graph graph("../data/data_source_title_unrepeated.csv");

    char graf;
    std::cout << "Do you want to produce a graph, find the vertex with the highest betweenness centrality or find the shortest path between two vertices?" << std::endl;
    std::cout << "Enter g for graph, b for betweenness centrality or p for shortest path: ";
    std::cin >> graf;

    if (graf == 'g') {
      std::cout << "Producing image..." << std::endl;
      // enter the graph drawing code

      std::cout << "Image complete! it is in the graF directory and it's named output.png" << std::endl;
    } else if (graf == 'p'){
      std::string vertex1;
      std::string vertex2;

      std::cout << "Enter vertex 1: ";

      std::cin.ignore();
      std::getline(std::cin, vertex1);

      std::cout << "Enter vertex 2: ";

      std::cin.ignore();
      std::getline(std::cin, vertex2);

      std::cout << "if the output is blank, that means one of the vertices does not exist in your dataset" << std::endl;

      std::cout << "Shortest path is: " << std::endl;
    } else {
      // enter betweenness centrality code
    }

    std::cout << "The program has finished running. To run the program again, enter ./main in the terminal" << std::endl;
    std::cout << "Thank you!" << std::endl;

  } else {
    std::cout << "Invalid input. Please run the program again by entering in the terminal ./main" << std::endl;
  }
  

  // Graph graph("../data_source_title_unrepeated.csv");
  // // Graph graph("../a.csv");

  // // std::vector<std::string> vect = graph.BFS("uiuc", "texas");
  // // std::cout << graph.print1() << std::endl;
  // // std::cout << graph.print2() << std::endl;
  // // for (std::string s : vect) 
  // //   std::cout << s << "=>";

  
  // // std::cout << vect.size() << std::endl;

  // // std::cout << "Size: " << graph.number_vertices() << std::endl;
  // graph.partition( 100 );

  // std::cout << "Size: " << graph.number_vertices() << std::endl;
  // /*
  
  // Image image = Image();
  // image.readFromFile("white.png");

  // Drawing drawing = Drawing(image, 50);
 
  // drawing.testDraw()
  
  // drawing.writeToFile("../tests/example.png");
  // */ 

  // Image drawing = Image();

  // drawing.readFromFile("../entry/Solid_white (1).png");
  // drawing.scale(20);


  // Drawing object = Drawing(drawing, 50);
 

  // object.testDraw(graph);

  // std::cout << "Size: " << graph.number_vertices() << std::endl;

  // // drawing.writeToFile("../tests/example.png");

  return 0;
=======
#include <iostream>
#include "../src/Image.h"
#include "../cs225/PNG.h"
#include "../src/graph.hpp"
#include "../src/utilities.hpp"
#include "../src/drawing.hpp"

using namespace cs225;
int main() {
  

  Graph graph("../data_source_title_unrepeated.csv");
  // Graph graph("../a.csv");

  // std::vector<std::string> vect = graph.BFS("uiuc", "texas");
  // std::cout << graph.print1() << std::endl;
  // std::cout << graph.print2() << std::endl;
  // for (std::string s : vect) 
  //   std::cout << s << "=>";

  
  // std::cout << vect.size() << std::endl;

  // std::cout << "Size: " << graph.number_vertices() << std::endl;
  graph.partition( 20 );

  std::cout << "Size: " << graph.number_vertices() << std::endl;
  /*
  
  Image image = Image();
  image.readFromFile("white.png");

  Drawing drawing = Drawing(image, 50);
 
  drawing.testDraw()
  
  drawing.writeToFile("../tests/example.png");
  */ 

  Image drawing = Image();

  drawing.readFromFile("../entry/Solid_white (1).png");
  drawing.scale(20);


  Drawing object = Drawing(drawing);
 

  object.testDraw(graph);

  std::cout << "Size: " << graph.number_vertices() << std::endl;

  // drawing.writeToFile("../tests/example.png");

  return 0;
>>>>>>> 1a00dfe22018f88c890b4f932c4f0f674671a586
}