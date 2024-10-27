#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <stdexcept>

Image::Image(const char* filename) {
    data = stbi_load(filename, &_width, &_height, &_channels, 0);

    if (data == nullptr) throw std::runtime_error("Could not load image");
}

Image::~Image() {
    stbi_image_free(data);
}


unsigned int Image::width() const {
    return (unsigned int)_width;
}

unsigned int Image::height() const {
    return (unsigned int)_height;
}

unsigned int Image::channels() const {
    return (unsigned int)_channels;
}


double Image::intensity(const unsigned int& x, const unsigned int& y) const {
    if (x > _width || y > _height) throw std::out_of_range("Invalid coordinates");

    unsigned char* pixel = data + x * _channels + y * _width * _channels;
    switch (_channels) {
        case 1:
            return (double)*pixel / 255;
        case 2:
            return (double)*pixel / 255 * (double)*(pixel + 1) / 255;
        case 3:
            return (double)(*pixel + *(pixel + 1) + *(pixel + 2)) / 3 / 255;
        case 4:
            return (double)(*pixel + *(pixel + 1) + *(pixel + 2)) / 3 / 255 * (double)*(pixel + 3) / 255;
        default:
            throw std::runtime_error("Unkown amount of channels");
    }
}