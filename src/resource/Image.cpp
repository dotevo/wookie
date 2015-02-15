#include <wookie/resource/Image.h>
#include <lodepng.h>
#include <stdexcept>

Image::Image(std::string path) {
#ifdef HAVE_SDL
    surface = IMG_Load(path.c_str());
#endif
    uint32_t error = lodepng::decode(m_image, m_width, m_height, path.c_str());
    if (error != 0)
        throw std::runtime_error {lodepng_error_text(error)};
}

unsigned char const* Image::img() const {
    return m_image.data();
}
