
#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "drawing.hpp"
bool compareCoeff(const Vertex& l, const Vertex& r);
bool compareCoeff(const Vertex& l, const Vertex& r) { return l.bc_coeff < r.bc_coeff;}

Drawing::Drawing(const Image& picture, unsigned max) {
    picture_ = Image(picture);
    max_ = max;
}


int Drawing::addSticker(Image& sticker, int x, int y) {
    if (stickers_.size() == max_ || max_ == 0) {
        return -1;
    }
    
    //Image* to_stick = new Image(sticker);
    //Image imagen = Image(sticker);
    Image* to_stick = &sticker;
    
    

    stickers_.push_back(to_stick);
    coords_.push_back(std::make_pair(x,y));
    
    return stickers_.size() - 1;
    
    
}



void Drawing::removeSticker(unsigned index) {

    if (index == 0 && stickers_.size() == 1) {
        stickers_.clear();
    }
    if (stickers_.size() > 0 && index >= 0) {
        // delete stickers_[index];
        stickers_[index] = nullptr;
        stickers_.erase(stickers_.begin() + index);
        
        coords_.erase(coords_.begin() + index);
    }
    
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

    Image vert_png;
    vert_png.readFromFile("../src/vert.png");

    vert_png.scale(0.07);


    
    std::unordered_map<std::string, double> map_coeffs = graph.betweenness_centrality_opt();        //receiving mapping of vertex name to its bc_coeff
    
    
    for(std::string each : graph.getV()) {                                                  // draws each vertex


        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist1(0,INT_MAX);
        int x = 100 + dist1(rng) % (picture_.height() - 300);

        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,INT_MAX);
        int y = 100 + dist2(rng) % (picture_.width() - 300);

        Vertex vert = Vertex(each, x, y);
        
        vert.bc_coeff = map_coeffs[vert.source];
        
        vertices.insert(vert);              

        addSticker(vert_png, vert.x, vert.y);
    }

    std::vector<Vertex> vec;
    for (auto each: vertices) {
        vec.push_back(each);
    }
    std::sort(vec.begin(), vec.end(), compareCoeff);          // sorting Vertex objects by bc_coeff
    // std::reverse(vec1.begin(), vec1.end());                  // reverse function to change order of sort


    std::cout << "Node with highest betweenness centrality coefficient is " + vec[vec.size() - 1].source + ", and its BC-Coefficient is: " << vec[vec.size() - 1].bc_coeff << '\n' <<std::endl;

    std::cout << "Top ten percent nodes with highest betweenness centrality coefficients, and their values:" << '\n' <<std::endl;
    for (size_t i = vec.size()* 0.90; i < vec.size(); i++) {                                            
        std::cout << "Source: " + vec[i].source + " | " << "BC-Coefficient: " << vec[i].bc_coeff << std::endl;
    }
    
    Image vert2;                                                                        //only #1 highest betweenness centrality gets highlighted with different image
    vert2.readFromFile("../src/biggestcentrality.png");
    vert2.scale(0.5);
    addSticker(vert2, vec[vec.size() - 1].x -50, vec[vec.size() - 1].y -50);


    for(std::pair<std::string, std::string> each : graph.getE()) {                  //this creates the pairs of Vertex objects for the edges structures      
        Vertex found1 = Vertex("Default", 0, 0); 
        Vertex found2 = Vertex("Default2", 0, 0); 

        for ( Vertex vertex : vertices ) {
            if (vertex.source == each.first) {
                found1 = vertex;
            }
            if (vertex.source == each.second) {
                found2 = vertex;
            }
        }
        
        edges.push_back(std::make_pair(found1, found2));
        int start_x = found1.x;
        int start_y = found2.y;
    }

    for(std::pair<Vertex, Vertex> each : edges) {                                               //drawing each edge
        int dist = distance(each.first, each.second);
        double slope = double(each.second.x - each.first.x) / (each.second.y - each.first.y);           //using slope for line drawing
        int start_x = each.first.x + (vert_png.height() / 2);
        int start_y = each.first.y + (vert_png.width()/ 2);                     //adjust so that edge begins in center of vertex


        cs225::HSLAPixel black = cs225::HSLAPixel(0, 1, 0);
        cs225::HSLAPixel red = cs225::HSLAPixel(0, 1, 0.5);

        int bound = abs( each.second.y + int(vert_png.width()/ 2) - start_y );                      
        if (each.second.y > each.first.y) {                                                     
            for (int i = 0; i < bound; i++) {
                for (int k = -1; k < 2; k++) {
                    cs225::HSLAPixel & new_pixel = picture_.getPixel(start_x + k + int(i*slope), start_y + i + k);
            
                    if (i < bound / 2) {
                        new_pixel = red;
                    
                    } else {
                        new_pixel = black;
                    
                    }
                }
            }
        } else {
            for (int i = 0; i < abs( (each.second.y + int(vert_png.width()/ 2) - start_y )); i++) {
                for (int k = -1; k < 2; k++) {
                    cs225::HSLAPixel & new_pixel = picture_.getPixel(start_x + k - int(i*slope), start_y - i + k);
                    if (i < bound / 2) {
                        new_pixel = red;
                    
                    } else {
                        new_pixel = black;
                    
                    }
                }
            }
        }   
    }
    render().writeToFile("../tests/example.png");
}


int Drawing::distance(Vertex vert1, Vertex vert2) {                 
    int x_diff = vert1.x - vert2.x;
    int y_diff = vert1.y - vert2.y;

    return int(sqrt( std::pow(x_diff, 2) + std::pow(y_diff, 2)));
}




