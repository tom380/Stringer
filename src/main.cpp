
#include <iostream>
#include <string>
#include <math.h>

#include "Stopwatch.hpp"
#include "Image.hpp"
#include "PointCloud.hpp"

#define PI 3.14159265359
#define TAU 6.28318530718

#define NAILS 100
#define THREAD_WIDTH 1 // Pixels

auto start = std::chrono::high_resolution_clock::now();

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


    // double* intensity = new double[img.width() * img.height()];

    // for (int x = 0; x < img.width(); x++) {
    //     for (int y = 0; y < img.height(); y++) {
    //         intensity[y*img.width() + x] = img.intensity(x, y);
    //     }
    // }
    // timer.lap("Intensity calculation");

    // unsigned char* grayscale = new unsigned char[img.width() * img.height()];

    // for (int x = 0; x < img.width(); x++) {
    //     for (int y = 0; y < img.height(); y++) {
    //         grayscale[y*img.width() + x] = (unsigned char)(255 * intensity[y*img.width() + x]);
    //     }
    // }
    // timer.lap("Convert to greyscale");

    // stbi_write_png("grayChopper.png", img.width(), img.height(), 1, grayscale, img.width());
    // // delete[] grayscale;
    // timer.lap("Saving grayscale image");

    // int centre_x = img.width() / 2;
    // int centre_y = img.height() / 2;
    // int radius = std::min(centre_x, centre_y);
    // int radius_sqr = radius * radius;

    // for (int x = 0; x < img.width(); x++) {
    //     for (int y = 0; y < img.height(); y++) {
    //         if ((x - centre_x)*(x - centre_x) + (y - centre_y)*(y - centre_y) <= radius_sqr) {

    //         }
    //         else grayscale[y*img.width() + x] = 0;
    //     }
    // }
    // timer.lap("Create cutout");

    // stbi_write_png("cutoutChopper.png", img.width(), img.height(), 1, grayscale, img.width());
    // delete[] grayscale;
    // timer.lap("Saving cutout image");

    

    // for (int i = 0; i < NAILS / 2; i++) {
    //     const float angle = (float)i / NAILS * TAU;
    //     const float cos = std::cos(angle);
    //     const float sin = std::sin(angle);
    //     for (int x = 0; x < img.width(); x++) {
    //         for (int y = 0; y < img.height(); y++) {
    //             const double brightness = grayscale[y*img.width() + x];
    //             if (brightness != 0) {
    //                 const float projection = x * cos + y * sin;


    //             }
    //         }
    //     }
    // }
    // timer.lap("Loop");

    


    timer.stop("Total");
    return 0;
}
