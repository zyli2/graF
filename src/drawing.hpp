#pragma once

#include <limits.h>
#include "Image.h"
#include "vertex.hpp"
#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <set>
#include <cmath>

class Drawing {                     // class based on the CS225 StickerSheet
    public:
        Drawing(const Image & picture, unsigned max);
        void removeSticker(unsigned index);
        int addSticker(Image& sticker, int x, int y);
        
        void testDraw(Graph graph);
        Image render() const;
        
    private:

        std::set<Vertex> vertices;
        std::vector<std::pair<Vertex, Vertex>> edges;
        Image picture_ = Image();
        unsigned max_ = 0;
        std::vector<Image*> stickers_;
        std::vector<std::pair<int, int>> coords_;

        int distance(Vertex vert1, Vertex vert2);
        
};


