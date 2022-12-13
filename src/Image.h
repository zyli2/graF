#include "../cs225/PNG.h"

class Image : public cs225::PNG { 
    public:
        /**
        * Scale the image by the given factor.
        *
        * @param factor The scaling factor.
        */
        void scale(double factor);

        /**
        * Scale the image by the given width adnd height.
        *
        * @param w The new width of the image.
        * @param h The new height of the image.
        */
        void scale(unsigned w, unsigned h);
};

#pragma once