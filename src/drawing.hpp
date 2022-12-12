#pragma once

#include <limits.h>
#include "Image.h"
#include "vertex.hpp"
#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <set>
#include <cmath>

class Drawing {
    public:
        Drawing(const Image & picture);
        int addVertex(Image& sticker, int x, int y);
        void testDraw(Graph graph);
        Image render() const;
        
    private:
        std::set<Vertex> vertices;
        std::vector<std::pair<Vertex, Vertex>> edges;
        Image picture_ = Image();
        std::vector<Image*> stickers_;
        std::vector<std::pair<int, int>> coords_;
};


