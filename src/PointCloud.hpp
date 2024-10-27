#pragma once

#include <vector>
#include <string>

struct Point {
    float x;
    float y;
    float data;
};

class PointCloud {
    std::vector<Point> _cloud;
    float _x_min;
    float _x_max;
    float _y_min;
    float _y_max;

public:
    PointCloud();
    void add(Point point);
    void render(std::string filename);

    std::vector<Point>::iterator begin() { return _cloud.begin(); }
    std::vector<Point>::iterator end() { return _cloud.end(); }
    
    std::vector<Point>::const_iterator begin() const { return _cloud.begin(); }
    std::vector<Point>::const_iterator end() const { return _cloud.end(); }
};