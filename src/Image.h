<<<<<<< HEAD
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

=======
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

>>>>>>> 1a00dfe22018f88c890b4f932c4f0f674671a586
#pragma once