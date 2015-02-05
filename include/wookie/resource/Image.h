#pragma once

#include <string>
#include <wookie/resource/Resource.h>
#include <SDL2/SDL_image.h>

class Image: public Resource{
public:
    Image(std::string path);
    virtual ~Image();
private:
    SDL_Surface *surface;
};
