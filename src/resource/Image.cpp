#include <iostream>
#include <wookie/resource/Image.h>

Image::Image(std::string path) {
    surface = IMG_Load(path.c_str());
}

Image::~Image() {
}
