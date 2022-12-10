#include "../drawing/drawing.hpp"
#include <utility>
#include <algorithm>
#include <iostream>
#include "vertex.hpp"
#include "../src/graph.hpp"

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
    for (unsigned i = 0; i < stickers_.size(); i++) {
        std::cout << stickers_[i]->width() << std::endl;
    }
    std::cout<< "\n" << std::endl;
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
    for (unsigned i = 0; i < stickers_.size(); i++) {
        std::cout << stickers_[i] << std::endl;
    }
    std::cout<< "\n" << std::endl;
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
}


// https://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf

void Drawing::forceDirected(Image canvas, Graph graph) {
    int area = canvas.width() * canvas.height();

    // randomize positions
    for(std::string each : graph.getV()) {
        int x = 30 + (rand() % canvas.width() - 30);
        int y = 30 + (rand() % canvas.height() - 30);
        vertices.insert(Vertex(each, x, y));
    }
    for(std::pair<std::string, std::string> each : graph.getE()) {
        Vertex vert1 = Vertex(each.first, 0, 0);                //placeholders for comparison
        Vertex vert2 = Vertex(each.second, 0, 0);
        edges.insert(std::make_pair(*std::find(vertices.begin(), vertices.end(), vert1), *std::find(vertices.begin(), vertices.end(), vert2)));
    }

    

   
    
    int k = sqrt(area / graph.getV().size());

    const int iters = 40;
    for (int i = 0; i < iters; i++) {
        for (Vertex v : vertices) {
            for (Vertex v2 : vertices) {
                if (v.source != v2.source) {
                    int diff = v.pos - v2.pos;
                    // v.disp = v.disp + ()
                }
            }
        }

        for (std::pair<Vertex, Vertex> e : edges) {
            int diff = e.first.pos - e.second.pos;
            // e.first.disp = e.first.disp - ((diff / ) * (std::pow(x, 2) / k));
            // e.second.disp = e.second.disp + ((diff / ) * (std::pow(k, 2) / x));

        }
    }


}


void Drawing::testDraw(Image& canvas, Graph graph) {
   
    Image vert_png;
    vert_png.readFromFile("../drawing/vert.png");

    Drawing test(canvas, 50);
    
    for(std::string each : graph.getV()) {
        int x = 30 + (rand() % canvas.width() - 30);
        int y = 30 + (rand() % canvas.height() - 30);
        Vertex vert = Vertex(each, x, y);
        vertices.insert(vert);

        test.addSticker(vert_png, vert.x, vert.y);
    }
    test.render().writeToFile("../tests/example.png");
  
  
}

