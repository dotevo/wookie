#include <iostream>
#include <wookie/resource/Image.h>

Image::Image(std::string path) {
#ifdef HAVE_SDL
    surface = IMG_Load(path.c_str());
#endif
}

Image::~Image() {
}
