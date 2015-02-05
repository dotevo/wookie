#pragma once

#include <string>
#include <wookie/resource/Resource.h>
#ifdef HAVE_SDL
#include <SDL2/SDL_image.h>
#endif

class Image: public Resource{
public:
    Image(std::string path);
    virtual ~Image();
private:
#ifdef HAVE_SDL
    SDL_Surface *surface;
#endif
};
