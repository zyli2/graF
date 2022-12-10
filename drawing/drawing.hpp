 #include "../drawing/Image.h"
 #include <vector>
 #include <unordered_set>
#include "../drawing/vertex.hpp"

class Drawing {
    public:
        Drawing(const Image & picture, unsigned max);
        void forceDirected(Image canvas, Graph graph);
        void removeSticker(unsigned index);
        int addSticker(Image& sticker, int x, int y);
        
        void testDraw(Image& canvas, Graph graph);
        Image render() const;
        bool translate(unsigned index, unsigned x, unsigned y);
    private:

        std::unordered_set<Vertex> vertices;
        std::unordered_set<std::pair<Vertex, Vertex>> edges;
        Image picture_ = Image();
        unsigned max_ = 0;
        std::vector<Image*> stickers_;
        std::vector<std::pair<int, int>> coords_;
};
#pragma once