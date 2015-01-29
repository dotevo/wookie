#pragma once

#include <wookie/core/WObject.h>
#include <wookie/core/Window.h>

class RenderContext: public WObject
{
public:
    RenderContext();

    ~RenderContext() = default;

    Window& window();

    bool update();

private:
    Window m_window;
};
