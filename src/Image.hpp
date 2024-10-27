#pragma once

class Image {
    private:
        int _width;
        int _height;
        int _channels;


    public:
        unsigned char* data;

        Image(const char* filename);
        ~Image();

        unsigned int width() const;
        unsigned int height() const;
        unsigned int channels() const;

        double intensity(const unsigned int& x, const unsigned int& y) const;
};