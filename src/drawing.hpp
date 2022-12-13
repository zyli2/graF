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
        /**
        * The main drawing function.
        *
        * @param picture The image to be drawn on.
        */
        Drawing(const Image & picture);

        /**
        * Add and store vertex and its coords. 
        *
        * @param sticker The node (picture)
        * @param x The x coordinate 
        * @param y The y coordinate 
        *
        * @return The number of vertices it currenting stored.
        */
        int addVertex(Image& sticker, int x, int y);

        /**
        * The main drawing function.
        *
        * @param graph The graph that will be used for drawing
        */
        void testDraw(Graph graph);

        /**
        *
        * @return The Image.
        */
        Image render() const;
        
    private:
        std::set<Vertex> vertices;
        std::vector<std::pair<Vertex, Vertex>> edges;
        Image picture_ = Image();
        std::vector<Image*> stickers_;
        std::vector<std::pair<int, int>> coords_;
};


