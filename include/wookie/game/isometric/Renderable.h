#pragma once

#include <memory>

#include <wookie/ecs/Component.h>
#include <wookie/resource/Image.h>

struct Renderable : public Component<Renderable>
{
    Renderable(int x, int y, Image const *img) :
        gridX(x), gridY(y), img(img) {}

    int gridX;
    int gridY;
    Image const *img;
};
