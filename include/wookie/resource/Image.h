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

    virtual ~Image() = default;

    unsigned char const* data() const;

private:
#ifdef HAVE_SDL
    SDL_Surface *surface;
#endif
    uint32_t m_width;
    uint32_t m_height;
    std::vector<unsigned char> m_image;
};
