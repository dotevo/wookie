#pragma once

#include <wookie/Window.h>

class RenderContext
{
public:
    RenderContext();

    ~RenderContext() = default;

    Window& window();

    bool update();

private:
    Window m_window;
};
