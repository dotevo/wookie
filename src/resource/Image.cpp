#include <wookie/resource/Image.h>
#include <lodepng.h>
#include <stdexcept>
#include <iostream>

Image::Image(std::string path) {
    std::cout << path << std::endl;

#ifdef HAVE_SDL
    std::vector<unsigned char> m_image;
#endif

    uint32_t error = lodepng::decode(m_image, m_width, m_height, path.c_str());
    if (error != 0)
        throw std::runtime_error {lodepng_error_text(error)};
#ifdef HAVE_SDL
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    int depth = 32;
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_width, m_height, depth, rmask, gmask, bmask, amask);
    SDL_LockSurface(surface);

    unsigned char * pixelPointer = static_cast<unsigned char *>(surface->pixels);
    for (std::vector<unsigned char>::iterator iter = m_image.begin();
                iter != m_image.end();
                ++iter)
    {
        *pixelPointer = *iter;
        ++pixelPointer;
    }
    SDL_UnlockSurface(surface);
#endif
}

Image::~Image() {
#ifdef HAVE_SDL
    SDL_FreeSurface(surface);
#endif
}

unsigned char const* Image::data() const {
#ifndef HAVE_SDL
    return m_image.data();
#else
    return (unsigned char const*)surface->pixels;
#endif
}
