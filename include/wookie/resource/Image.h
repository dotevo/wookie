#pragma once

#include <string>
#include <vector>

#include <wookie/resource/Resource.h>

#ifdef HAVE_SDL
#include <SDL2/SDL.h>
#endif

class Image: public Resource{
public:
    Image(std::string path);

    virtual ~Image();

    int getHeight() const{return m_height;}
    int getWidth() const{return m_width;}
#ifdef HAVE_SDL
    SDL_Surface* getSurface() const{return surface;}
#endif
    unsigned char const* data() const;
private:
#ifdef HAVE_SDL
    SDL_Surface *surface;
#else
    std::vector<unsigned char> m_image;
#endif
    uint32_t m_width;
    uint32_t m_height;
};
