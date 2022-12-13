#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "drawing.hpp"


Drawing::Drawing(const Image& picture) {
    picture_ = Image(picture);
}


int Drawing::addVertex(Image& sticker, int x, int y) {
    Image* to_stick = &sticker;
    
    stickers_.push_back(to_stick);
    coords_.push_back(std::make_pair(x,y));
    return stickers_.size() - 1;
}


Image Drawing::render() const {
    Image rendered = Image(picture_);
    for (size_t i = 0; i < stickers_.size(); i++) {
        Image* sticker = stickers_[i];
        int x = coords_[i].first;
        int y = coords_[i].second;
        if (sticker->width() + x > picture_.width()) { 
            rendered.scale(sticker->width() + x, picture_.height());
        }
        if (sticker->height() + y > picture_.height()) {
            rendered.scale(picture_.width(), sticker->height() + y);
        }        
        for (unsigned int g = 0; g < sticker->width(); g++) {
            for (unsigned int k = 0; k < sticker->height(); k++) {
                if (sticker->getPixel(g,k).a == 0) {
                    continue;
                }
                rendered.getPixel(x + g, y + k) = sticker->getPixel(g,k);           
            }
        }
    }
    return rendered;
}

void Drawing::testDraw(Graph graph) {

    // Load the image of the vertex
    Image vert_png;
    vert_png.readFromFile("../src/node.png");
    vert_png.scale(0.1);

    // Loop through all the vertices of the graph
    for(std::string each : graph.getV()) {
        
        // Random number generator for the coordinates of the vertex
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist1(0,INT_MAX);

        // Make sure the coordinates don't go out of bounds.
        int x = dist1(rng) % (picture_.height() - 100);
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,INT_MAX);
        int y = dist2(rng) % (picture_.width() - 100);
        Vertex vert = Vertex(each, x, y);

        // Update the vertices list 
        vertices.insert(vert);

        // Draw the vertices 
        addVertex(vert_png, vert.x, vert.y);
    }

    // Loop through all the edges of the graph
    for(std::pair<std::string, std::string> each : graph.getE()) {

        // Default vertices of the edge
        Vertex found1 = Vertex("Default", 0, 0); 
        Vertex found2 = Vertex("Default2", 0, 0);

        // Finding the actual vertices of the edge. 
        for ( Vertex vertex : vertices ) {
            if (vertex.source == each.first) {
                found1 = vertex;
            }
            if (vertex.source == each.second) {
                found2 = vertex;
            }
        }
        
        // Update the edges list 
        edges.push_back(std::make_pair(found1, found2));
        int start_x = found1.x;
        int start_y = found2.y;
    }

    // Drawing the edges 
    for(std::pair<Vertex, Vertex> each : edges) {
        double slope = double(each.second.x - each.first.x) / (each.second.y - each.first.y);

        // Take the node's height and width into account
        int start_x = each.first.x + (vert_png.height() / 2);
        int start_y = each.first.y + (vert_png.width()/ 2);


        // The starting point will be marked red and the destination will be marked black.
        cs225::HSLAPixel black = cs225::HSLAPixel(0, 1, 0);
        cs225::HSLAPixel red = cs225::HSLAPixel(0, 1, 0.5);

        // Calculate the length of the edge (on the canvas)
        int bound = abs( each.second.y + int(vert_png.width()/ 2) - start_y );

        // Determine the direction of the edge based on calculated slope
        if (each.second.y > each.first.y) {
            for (int i = 0; i < bound; i++) {
                for (int j = -1; j < 2; ++j) {
                    cs225::HSLAPixel & new_pixel = picture_.getPixel(start_x + j + int(i*slope), start_y + i);
                    if (i < bound / 2) new_pixel = red;
                    else new_pixel = black;
                }
            }
        } else {
            for (int i = 0; i < bound; i++) {
                for (int j = -1; j < 2; ++j) {
                    cs225::HSLAPixel & new_pixel = picture_.getPixel(start_x + j - int(i*slope), start_y - i);
                    if (i < bound / 2) new_pixel = red;
                    else new_pixel = black;
                }
            }
        }   
    }
    render().writeToFile("../tests/example.png");
}

