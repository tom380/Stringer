#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>

struct Point {
    float x;
    float y;
    float data;
};

struct BoundingBox {
    float x_min;
    float x_max;
    float y_min;
    float y_max;
};

class PointCloud {
    std::vector<Point> _cloud;
    BoundingBox _boundingBox;

public:
    PointCloud() {
        _boundingBox.x_min = std::numeric_limits<float>::max();
        _boundingBox.x_max = std::numeric_limits<float>::lowest();
        _boundingBox.y_min = std::numeric_limits<float>::max();
        _boundingBox.y_max = std::numeric_limits<float>::lowest();
    }

    void add(Point point) {
        _cloud.push_back(point);

        if (_boundingBox.x_min > point.x) _boundingBox.x_min = point.x;
        if (_boundingBox.x_max < point.x) _boundingBox.x_max = point.x;
        if (_boundingBox.y_min > point.y) _boundingBox.y_min = point.y;
        if (_boundingBox.y_max < point.y) _boundingBox.y_max = point.y;
    }

    void render(std::string filename) {
        const unsigned int width = static_cast<unsigned int>(_boundingBox.x_max - _boundingBox.x_min + 1);
        const unsigned int height = static_cast<unsigned int>(_boundingBox.y_max - _boundingBox.y_min + 1);
        
        // Grayscale + Alpha (2 bytes per pixel), initialized to fully transparent
        unsigned char* image = new unsigned char[width * height * 2]();
        
        for (Point point : _cloud) {
            const unsigned int u = static_cast<unsigned int>(point.x - _boundingBox.x_min);
            const unsigned int v = static_cast<unsigned int>(point.y - _boundingBox.y_min);
            
            if (u < width && v < height) {  // Bounds check
                unsigned int index = (v * width + u) * 2;
                image[index] = static_cast<unsigned char>(point.data * 255);    // Brightness channel
                image[index + 1] = 255;  // Alpha channel (fully opaque for this pixel)
            }
        }

        stbi_write_png(filename.c_str(), width, height, 2, image, width * 2);
        delete[] image;
    }
};