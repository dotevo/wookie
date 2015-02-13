#pragma once

#include <string>
#include <vector>

#include <wookie/resource/Resource.h>
#ifdef HAVE_SDL
#include <SDL2/SDL_image.h>
#endif

class Image: public Resource{
public:
    Image(std::string path);
    virtual ~Image();

    unsigned char const* img() const;

private:
#ifdef HAVE_SDL
    SDL_Surface *surface;
#endif
    std::vector<unsigned char> m_image;
    uint32_t m_width;
    uint32_t m_height;
};
