#pragma once

#include <wookie/resource/Image.h>

struct Tile {
    Tile(int X, int Y, Image const& IMG) :
        gridX(X), gridY(Y), img(IMG) {}

    int gridX;
    int gridY;
    Image const& img;
};
