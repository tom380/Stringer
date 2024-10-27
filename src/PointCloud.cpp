#include "PointCloud.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <limits>

PointCloud::PointCloud() {
    _x_min = std::numeric_limits<float>::max();
    _x_max = std::numeric_limits<float>::lowest();
    _y_min = std::numeric_limits<float>::max();
    _y_max = std::numeric_limits<float>::lowest();
}

void PointCloud::add(Point point) {
    _cloud.push_back(point);

    if (_x_min > point.x) _x_min = point.x;
    if (_x_max < point.x) _x_max = point.x;
    if (_y_min > point.y) _y_min = point.y;
    if (_y_max < point.y) _y_max = point.y;
}

void PointCloud::render(std::string filename) {
    const unsigned int width = static_cast<unsigned int>(_x_max - _x_min + 1);
    const unsigned int height = static_cast<unsigned int>(_y_max - _y_min + 1);
    
    unsigned char* image = new unsigned char[width * height * 2]();
    
    for (Point point : _cloud) {
        const unsigned int u = static_cast<unsigned int>(point.x - _x_min);
        const unsigned int v = static_cast<unsigned int>(point.y - _y_min);
        
        if (u < width && v < height) {
            unsigned int index = (v * width + u) * 2;
            image[index] = static_cast<unsigned char>(point.data * 255);
            image[index + 1] = 255;
        }
    }

    stbi_write_png(filename.c_str(), width, height, 2, image, width * 2);
    delete[] image;
}