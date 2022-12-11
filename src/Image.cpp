#include "Image.h"

void Image::lighten() {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).l + 0.1 <= 1) {
                getPixel(col, row).l += 0.1;
            } else {
                // l should be capped at 1
                getPixel(col, row).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).l + amount <= 1) {
                getPixel(col, row).l += amount;
            } else {
                getPixel(col, row).l = 1;
            }
        }
    }
}

void Image::darken() {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).l - 0.1 >= 0) {
                getPixel(col, row).l -= 0.1;
            } else {
                getPixel(col, row).l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).l - amount >= 0) {
                getPixel(col, row).l -= amount;
            } else {
                getPixel(col, row).l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).s + 0.1 <= 1) {
                getPixel(col, row).s += 0.1;
            } else {
                getPixel(col, row).s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).s + amount <= 1) {
                getPixel(col, row).s += amount;
            } else {
                getPixel(col, row).s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).s - 0.1 >= 0) {
                getPixel(col, row).s -= 0.1;
            } else {
                getPixel(col, row).s = 0;
            }
        }
    }
}


void Image::desaturate(double amount) {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            if (getPixel(col, row).s - amount >= 0) {
                getPixel(col, row).s -= amount;
            } else {
                getPixel(col, row).s = 0;
            }
        }
    }
}

// Set all saturation to 0
void Image::grayscale() {
    // row = y; column = x 
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            getPixel(col, row).s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            getPixel(col, row).h += degrees;
            getPixel(col,row).h = int(getPixel(col,row).h) % 360;
            if (getPixel(col,row).h < 0) {
                getPixel(col,row).h = 360 - getPixel(col,row).h * -1;
            }
        }
    }
}

void Image::illinify() {
    for (size_t row = 0; row < height(); ++row) {
        for (size_t col = 0; col < width(); ++col) {
            // "Illini Orange" = 11 and "Illini Blue" = 216
            int dif_orange = abs(int(getPixel(col,row).h - 11));
            int dif_blue = abs(int(getPixel(col,row).h - 216));
            if (dif_orange < dif_blue) {
                getPixel(col,row).h = 11;
            } else {
                getPixel(col,row).h = 216;
            }
        }
    }
}

// Do something 
void Image::scale(double factor) {
    // make a copy

    if (factor == 1.0) {
        return;
    }

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
    // shouldn't exceed the ratio
    double temp_width_ratio = double(w) / width();
    double temp_height_ratio = double(h) / height();
    
    if (temp_width_ratio < temp_height_ratio) {
        scale(temp_width_ratio);
        // resize(w, w/ratio);
    } else  {
        scale(temp_height_ratio);
        // resize(h/ratio, h);
    }
}

void Image::rotateRight(PNG& oldImagen) {
    PNG oldImage = PNG(oldImagen);
    double m = width() - 1;

    for (double i = 0; i < width(); i++) {
        double n = 0;
        for (double k = 0; k < height(); k++) {
            getPixel(m, n) = oldImage.getPixel(i,k);
        }
        n++;
    }
    m--;
}
