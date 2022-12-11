/**
 
 * Contains your declaration of the interface for the Image class.
 */
#include "../cs225/PNG.h"
class Image : public cs225::PNG { 
    public:
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void illinify();
        void rotateColor(double degrees);

        void scale(double factor);
        void scaleUp(double factor, PNG& oldImage);
        void scaleDown(double factor, PNG& oldImage);

        void scale(unsigned w, unsigned h);

        void rotateRight(PNG& oldImagen);

};

#pragma once