#pragma once

#include "GameObject.h"

class Triangle : public GameObject
{
public:
    float vdata {
            0.0f, 0.8f, 0.0f,
            -0.8f,-0.8f, 0.0f,
            0.8f,-0.8f, 0.0f,
    };
};