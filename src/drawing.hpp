<<<<<<< HEAD
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
        Drawing(const Image & picture, unsigned max);
        void forceDirected(Image canvas, Graph graph);
        void removeSticker(unsigned index);
        int addSticker(Image& sticker, int x, int y);
        
        void testDraw(Graph graph);
        Image render() const;
        bool translate(unsigned index, unsigned x, unsigned y);
        
    private:

        std::set<Vertex> vertices;
        std::vector<std::pair<Vertex, Vertex>> edges;
        Image picture_ = Image();
        unsigned max_ = 0;
        std::vector<Image*> stickers_;
        std::vector<std::pair<int, int>> coords_;

        int distance(Vertex vert1, Vertex vert2);
        double angle(double x_diff, double y_diff);
        Image base;
        
};


=======
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


>>>>>>> 1a00dfe22018f88c890b4f932c4f0f674671a586
