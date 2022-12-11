
#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "drawing.hpp"


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
    // for (unsigned i = 0; i < stickers_.size(); i++) {
    //     std::cout << stickers_[i]->width() << std::endl;
    // }
    // std::cout<< "\n" << std::endl;
    return stickers_.size() - 1;
    
    
}

// void StickerSheet::changeMaxStickers(unsigned max) {
//     if (max < max_ && stickers_.size() > max) {
//         std::cout <<max << "  " <<  max_ << "  " << stickers_.size()<< std::endl;
//         for (unsigned i = 0; i < max - stickers_.size() && stickers_.size() > 0; i++) {
//             std::cout << stickers_.size() << std::endl;
//             // delete stickers_[stickers_.size() - 1];
//             stickers_[stickers_.size() - 1] = nullptr;
//             stickers_.pop_back();
//             max_--;
//         }
//         max_ = max;
//     } else {
//         max_ = max;
//     }
// }

// Image* StickerSheet::getSticker(unsigned index) {
//     if (stickers_.size() == 0) {
//         return NULL;
//     }
//     if (index < 0 || index > stickers_.size() - 1 || stickers_[index] == nullptr) {
//         return NULL;
//     }
//     return stickers_[index];
// }	

void Drawing::removeSticker(unsigned index) {
    // if (stickers_.size() == 0 || index < 0 || index >= stickers_.size()) {
    //     return;
    // }
    if (index == 0 && stickers_.size() == 1) {
        stickers_.clear();
    }
    if (stickers_.size() > 0 && index >= 0) {
        // delete stickers_[index];
        stickers_[index] = nullptr;
        stickers_.erase(stickers_.begin() + index);
        
        coords_.erase(coords_.begin() + index);
    }
    // for (unsigned i = 0; i < stickers_.size(); i++) {
    //     std::cout << stickers_[i] << std::endl;
    // }
    // std::cout<< "\n" << std::endl;
}



bool Drawing::translate(unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index > stickers_.size() - 1 || stickers_.size() == 0) {
        return false;
    }
    coords_[index].first = x;
    coords_[index].second = y;
    return true;
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
    
    /* 
    Image background = base;

    // loop through the stickers vector
    for (unsigned int i = 0; i < stickers_.size(); ++i) {

    // checks that layer is not empty
    if (stickers_[i] != NULL) {
    // check if resizing is necessary
    // how to check? check if the length and height at that specific point is enough for the sticker to be added so.
    // available space = background.width/height - coordnate's index's width/height <= (*stickers[i]).width/height
    // actual resizing = scale(background.widhth + availble space - stickers[i].width, background.height + availble space - stickers[i].height)
    
        int available_space_w = background.width() - coords_[i].first; // 900 - 800 = 100
        int available_space_y = background.height() - coords_[i].second; // 600 - 200 = 400

    // this means the pixels are at a coordinate outside of the base image

        if ((available_space_w < 0) && (available_space_y < 0)) {
            background.resize(background.width() + abs(available_space_w) + (*stickers_[i]).width(),
                            background.height() + abs(available_space_y) + (*stickers_[i]).height());
        } else if ((available_space_w < 0)) {
            background.resize(background.width() + abs(available_space_w) + (*stickers_[i]).width(), background.height());
        } else if ((available_space_y < 0)) {
            background.resize(background.width(), background.height() + abs(available_space_y) + (*stickers_[i]).height());
        } else if ((available_space_w < int((*stickers_[i]).width()) && available_space_y < int((*stickers_[i]).height()))) {
            background.resize(background.width() + (*stickers_[i]).width() - available_space_w,
                            background.height() + (*stickers_[i]).height() - available_space_y);
        } else if (available_space_w < int((*stickers_[i]).width())) { // 100 < 226
            background.resize(background.width() + (*stickers_[i]).width() - available_space_w, background.height());
            // width scale: 900 + 226 - 100 = 1026
            // height scale: 600;
        } else if (available_space_y < int((*stickers_[i]).height())) {
            background.resize(background.width(), background.height() + (*stickers_[i]).height() - available_space_y);
        }

            for (unsigned int y = 0; y < (*stickers_[i]).height(); ++y) {
                for (unsigned int x = 0; x < (*stickers_[i]).width(); ++x) {
                    if ((*stickers_[i]).getPixel(x, y).a == 0) {
                        continue;
                    } else {
                        background.getPixel(x + coords_[i].first, y + coords_[i].second).h = (*stickers_[i]).getPixel(x, y).h;
                        background.getPixel(x + coords_[i].first, y + coords_[i].second).l = (*stickers_[i]).getPixel(x, y).l;
                        background.getPixel(x + coords_[i].first, y + coords_[i].second).s = (*stickers_[i]).getPixel(x, y).s;
                    }
                }
            }
            
        }
    }
    return background;
    */
}


// https://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf

// void Drawing::forceDirected(Image canvas, Graph graph) {
//     int area = canvas.width() * canvas.height();

//     // randomize positions
//     for(std::string each : graph.getV()) {
//         int x = 30 + (rand() % canvas.width() - 30);
//         int y = 30 + (rand() % canvas.height() - 30);
//         vertices.push_back(Vertex(each, x, y));
//     }
//     for(std::pair<std::string, std::string> each : graph.getE()) {
//         Vertex vert1 = Vertex(each.first, 0, 0);                //placeholders for comparison
//         Vertex vert2 = Vertex(each.second, 0, 0);
//         edges.push_back(std::make_pair(*std::find(vertices.begin(), vertices.end(), vert1), *std::find(vertices.begin(), vertices.end(), vert2)));
//     }

    
    
//     int k = sqrt(area / graph.getV().size());

//     const int iters = 40;
//     for (int i = 0; i < iters; i++) {
//         for (Vertex v : vertices) {
//             for (Vertex v2 : vertices) {
//                 if (v.source != v2.source) {
//                     int diff = v.pos - v2.pos;
//                     // v.disp = v.disp + ()
//                 }
//             }
//         }

//         for (std::pair<Vertex, Vertex> e : edges) {
//             int diff = e.first.pos - e.second.pos;
//             // e.first.disp = e.first.disp - ((diff / ) * (std::pow(x, 2) / k));
//             // e.second.disp = e.second.disp + ((diff / ) * (std::pow(k, 2) / x));
//         }
//     }
// }

void Drawing::testDraw(Graph graph) {

    Image vert_png;
    vert_png.readFromFile("../src/vert.png");

    vert_png.scale(0.05);

    // Drawing test(canvas, 50);

    for(std::string each : graph.getV()) {

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist1(0,INT_MAX);
        int x = dist1(rng) % (picture_.height() - 100);

        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,INT_MAX);
        int y = dist2(rng) % (picture_.width() - 100);
        Vertex vert = Vertex(each, x, y);
        vertices.insert(vert);

        addSticker(vert_png, vert.x, vert.y);
    }

    // std::cout << "Size: " << graph.getV().size() << std::endl;
    for(std::pair<std::string, std::string> each : graph.getE()) {

      
        Vertex found1 = Vertex("Default", 0, 0); 
        Vertex found2 = Vertex("Default2", 0, 0); 

        for ( Vertex vertex : vertices ) {
            if (vertex.source == each.first) {
                found1 = vertex;
                // std::cout << "X: " << found1.x << std::endl;
            }
            if (vertex.source == each.second) {
                found2 = vertex;
            }
        }
        
        edges.push_back(std::make_pair(found1, found2));
        int start_x = found1.x;
        int start_y = found2.y;
    }

    for(std::pair<Vertex, Vertex> each : edges) {
        int dist = distance(each.first, each.second);
        double slope = double(each.second.x - each.first.x) / (each.second.y - each.first.y);
        // std::cout << "Slope: " << slope << std::endl;
        int start_x = each.first.x + (vert_png.height() / 2);
        int start_y = each.first.y + (vert_png.width()/ 2);

        // std::cout << "( " << start_x << ", " << start_y << ")" << std::endl;

        cs225::HSLAPixel black = cs225::HSLAPixel(0, 1, 0);
        cs225::HSLAPixel red = cs225::HSLAPixel(0, 1, 0.5);

        int bound = abs( each.second.y + int(vert_png.width()/ 2) - start_y );
        if (each.second.y > each.first.y) {
            for (int i = 0; i < bound; i++) {
                cs225::HSLAPixel & new_pixel = picture_.getPixel(start_x + int(i*slope), start_y + i);
                cs225::HSLAPixel & new_pixel2 = picture_.getPixel(start_x + 1 + int(i*slope), start_y + i + 1);
                cs225::HSLAPixel & new_pixel3 = picture_.getPixel(start_x - 1 + int(i*slope), start_y + i - 1);
               
                if (i < bound / 2) {
                    new_pixel = red;
                    new_pixel2 = red;
                    new_pixel3 = red;
                } else {
                    new_pixel = black;
                    new_pixel2 = black;
                    new_pixel3 = black;
                }
            }
        } else {
            for (int i = 0; i < abs( (each.second.y + int(vert_png.width()/ 2) - start_y )); i++) {
                cs225::HSLAPixel & new_pixel = picture_.getPixel(start_x - int(i*slope), start_y - i);
                cs225::HSLAPixel & new_pixel2 = picture_.getPixel(start_x + 1 - int(i*slope), start_y - i);
                cs225::HSLAPixel & new_pixel3 = picture_.getPixel(start_x - 1 - int(i*slope), start_y - i);
               
                if (i < bound / 2) {
                    new_pixel = red;
                    new_pixel2 = red;
                    new_pixel3 = red;
                } else {
                    new_pixel = black;
                    new_pixel2 = black;
                    new_pixel3 = black;
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

double angle(double x_diff, double y_diff) {
    return atan( x_diff / y_diff );
}