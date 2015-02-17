#include <wookie/resource/Image.h>
#include <lodepng.h>
#include <stdexcept>

Image::Image(std::string path) {
#ifdef HAVE_SDL
    surface = IMG_Load(path.c_str());
#else
    uint32_t error = lodepng::decode(m_image, m_width, m_height, path.c_str());
    if (error != 0)
        throw std::runtime_error {lodepng_error_text(error)};
#endif
}

unsigned char const* Image::data() const {
#ifndef HAVE_SDL
    return m_image.data();
#else
    return (unsigned char const*)surface->pixels;
#endif
}
