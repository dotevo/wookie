#pragma once

#include <wookie/resource/Image.h>

struct Tile {
    Tile(int x, int y, Image const *img) :
        gridX(x), gridY(y), img(img) {}

    int gridX;
    int gridY;
    Image const *img;
};
