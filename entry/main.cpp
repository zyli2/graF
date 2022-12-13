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

    std::cout << "Make sure you provide the entire csv file's name including the filename extension .csv" << std::endl;

    std::cout << "Enter your dataset's name: ";

    std::cin.ignore();
    std::getline(std::cin, data);

    std::string dest = "../data/";

    dest += data;

    Graph graph(dest);

    char graf;
    std::cout << "Do you want to produce a graph, find the vertex with the highest betweenness centrality or find the shortest path between two vertices?" << std::endl;
    std::cout << "Our graph prints the vertex with the highest betweenness centrality in the terminal as well as highlighting it in the output picture" << std::endl;
    std::cout << "For betweennness centrality, make sure your dataset has less than 5k vertices or it will be super slow." << std::endl;
    std::cout << "For graph drawing, make sure your dataset has vertices less than 500." << std::endl;
    std::cout << "Enter g for graph, b for betweenness centrality or p for shortest path: ";
    std::cin >> graf;

    if (graf == 'g') {
      std::cout << "Producing image..." << std::endl;

      Image drawing = Image();
      drawing.readFromFile("../entry/Solid_white (1).png");
      drawing.scale(20);
      Drawing object = Drawing(drawing);
      object.testDraw(graph);

      std::cout << "Image complete! it is in the graF directory and it's named output.png" << std::endl;
    } else if (graf == 'p') {
      std::cin.ignore();
      std::vector<std::string> vert;
      int i = 1;

      while(i < 3) {
            std::string vertex;
            std::cout << "Enter Vertex " << i << ": ";
            std::getline(std::cin, vertex);
            vert.push_back(vertex);
            ++i;
      }

      std::cout << "If the output is blank, that means one of the vertices does not exist in your dataset or there isn't a path" << std::endl;

      std::vector<std::string> vect = graph.BFS(vert[0],  vert[1]);
      for (std::string s : vect) {
        std::cout << s << "=>";
      }
      std::cout << " Path Length: " <<  vect.size() << std::endl;

    } else {
      std::cout << "The vertex with the best betweenness centrality is..." << std::endl;

      graph.betweenness_centrality_opt();
    }

    std::cout << "The program has finished running. To run the program again, enter ./main in the terminal" << std::endl;
    std::cout << "Thank you!" << std::endl;

  } else if (decision == 'o') {

    Graph graph("../data/data_source_title_unrepeated.csv");

    char graf;
    std::cout << "Do you want to produce a graph, find the vertex with the highest betweenness centrality or find the shortest path between two vertices?" << std::endl;
    std::cout << "Our graph prints the vertex with the highest betweenness centrality in the terminal as well as highlighting it in the output picture" << std::endl;
    std::cout << "For betweennness centrality, make sure your dataset has less than 5k vertices or it will be super slow." << std::endl;
    std::cout << "For graph drawing, make sure your dataset has vertices less than 500." << std::endl;
    std::cout << "Enter g for graph, b for betweenness centrality or p for shortest path: ";
    std::cin >> graf;

    if (graf == 'g') {
      std::cout << "Producing image... (our original dataset is too big so here's a drawing of the partitioned original dataset)" << std::endl;

      Graph graph2("../data/attiro.csv");

      Image drawing = Image();
      drawing.readFromFile("../entry/Solid_white (1).png");
      drawing.scale(20);
      Drawing object = Drawing(drawing);
      object.testDraw(graph2);

      std::cout << "Image complete! it is in the graF directory and it's named output.png" << std::endl;
    } else if (graf == 'p'){

      std::cin.ignore();
      std::vector<std::string> vert;
      int i = 1;

      while(i < 3) {
            std::string vertex;
            std::cout << "Enter Vertex " << i << ": ";
            std::getline(std::cin, vertex);
            vert.push_back(vertex);
            ++i;
      }

      std::cout << "If the output is blank, that means one of the vertices does not exist in your dataset or there isn't a path" << std::endl;

      std::vector<std::string> vect = graph.BFS(vert[0],  vert[1]);
      for (std::string s : vect) {
        std::cout << s << "=>";
      }
      std::cout << " Path Length: " <<  vect.size() << std::endl;
    } else {
      std::cout << "The vertex with the best betweenness centrality is..." << std::endl;

      Graph graph3("../data/ttt.csv");

      graph3.betweenness_centrality_opt();
    }

    std::cout << "The program has finished running. To run the program again, enter ./main in the terminal" << std::endl;
    std::cout << "Thank you!" << std::endl;

  } else {
    std::cout << "Invalid input. Please run the program again by entering in the terminal ./main" << std::endl;
  }

  return 0;
}