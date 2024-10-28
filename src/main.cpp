#include "Stopwatch.hpp"
#include "Image.hpp"
#include "PointCloud.hpp"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <algorithm>
#include <cmath>

#define PI 3.14159265359
#define TAU 6.28318530718

#define NAILS 100
#define THREAD_WIDTH 1 // Pixels

struct Bin {
    float pos;
    float width;

    bool isIn(const float &point) {
        return (point > pos - width / 2) && (pos + width / 2 < point);
    }
};

int main() {
    Stopwatch timer;
    timer.start();

    Image img(ASSETS_PATH"/chopper.png");
    timer.lap("Loading image");


    int centre_x = img.width() / 2;
    int centre_y = img.height() / 2;
    int radius = std::min(centre_x, centre_y);
    int radius_sqr = radius * radius;

    PointCloud pointCloud;
    for (int u = 0; u < img.width(); u++) {
        for (int v = 0; v < img.height(); v++) {
            const float x = u - centre_x;
            const float y = v - centre_y;

            if (x*x + y*y <= radius_sqr)
                pointCloud.add(Point{x,y,(float)img.intensity(u, v)});
        }
    }
    timer.lap("Making pointcloud");

    pointCloud.render("cutoutChopper.png");
    timer.lap("Saving cutout image");

    std::vector<Bin> lines_on;
    for (int nail = 1; nail < NAILS / 2; nail++) {
        const float angle = (float)nail / NAILS * TAU;
        lines_on.push_back(Bin{std::cos(angle),1});
    }
    std::vector<Bin> lines_between;
    for (int nail = 0; nail < NAILS / 2; nail++) {
        const float angle = (nail + 0.5) / NAILS * TAU;
        lines_between.push_back(Bin{std::cos(angle),1});
    }
    timer.lap("Calculate bins");

    float line_intensities[NAILS][NAILS] = {0};
    float max_intensity = 0;
    for (int nail = 0; nail < NAILS / 2; nail++) {
        const float angle = (float)nail / NAILS * TAU;
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);

        for (Point point : pointCloud) {
            const float projection = point.x * cos + point.y * sin;
        
            for (int line = 0; line < lines_on.size(); line++) {
                if (lines_on[line].isIn(projection)) {
                    line_intensities[nail + line + 1][(NAILS + nail - line - 1) % NAILS] += point.data;
                    if (line_intensities[nail + line + 1][(NAILS + nail - line - 1) % NAILS] > max_intensity) {
                        max_intensity = line_intensities[nail + line + 1][(NAILS + nail - line - 1) % NAILS];
                    }
                }
            }
        }
    }
    timer.lap("Loop");

    unsigned char* image = new unsigned char[NAILS * NAILS]();
    for (int n1 = 0; n1 < NAILS; n1++) {
        for (int n2 = 0; n2 < NAILS; n2++) {
            image[n1 + NAILS * n2] = (unsigned char)(line_intensities[n1][n2] / max_intensity * 255);
        }
    }
    stbi_write_png("transform.png", NAILS, NAILS, 1, image, NAILS);
    delete[] image;
    timer.lap("Save transform");

    timer.stop("Total");
    return 0;
}
