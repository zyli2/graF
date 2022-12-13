#include "Image.h"


void Image::scale(double factor) {

    if (factor == 1.0) {
        return;
    }

    // Make a blank copy of the image.
    PNG newImage = PNG(int(width()*factor), int(height()*factor));

    for (size_t row = 0; row < newImage.height(); ++row) {
        for (size_t col = 0; col < newImage.width(); ++col) {
            newImage.getPixel(col,row) = getPixel(int(col/factor), int(row/factor));
        }
    }

    resize(int(width()*factor), int(height()*factor));
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            getPixel(col,row) = newImage.getPixel(col,row);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double ratio = width() / height();
    
    double temp_width_ratio = double(w) / width();
    double temp_height_ratio = double(h) / height();
    
    // Keep scaling until one of the dimension meets.
    if (temp_width_ratio < temp_height_ratio) {
        scale(temp_width_ratio);
    } else  {
        scale(temp_height_ratio);
    }
}
