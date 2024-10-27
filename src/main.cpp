#include "Stopwatch.hpp"
#include "Image.hpp"
#include "PointCloud.hpp"

#include <algorithm>
#include <cmath>

#define PI 3.14159265359
#define TAU 6.28318530718

#define NAILS 100
#define THREAD_WIDTH 1 // Pixels

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

    for (int i = 0; i < NAILS / 2; i++) {
        const float angle = (float)i / NAILS * TAU;
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);

        for (Point point : pointCloud) {
            const float projection = point.x * cos + point.y * sin;
        }
    }
    timer.lap("Loop");

    timer.stop("Total");
    return 0;
}
