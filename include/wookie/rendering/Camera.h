#pragma once

#include <wookie/ecs/Component.h>

struct Camera : public Component<Camera>
{
private:

    struct Position
    {
        float x {0.0f};
        float y {0.0f};
    };

    struct FOV {
        float left {-1.0f};
        float right {1.0f};
        float bottom {-1.0f};
        float top {1.0f};
    };

public:

    using Rotation = float;
    using Scale = float;

    FOV fov;
    Position offset;
    Rotation angle {0.0f};
    Scale factor {1.0f};

    bool active {true};
};
