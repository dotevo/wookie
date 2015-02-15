#pragma once

#include <string>

enum WindowMode
{
    WINDOWED,
    FULLSCREEN
};

class RenderContext
{
public:
    virtual ~RenderContext() = default;

    virtual int width() const = 0;

    virtual int height() const = 0;

    virtual WindowMode mode() const = 0;

    virtual void setWindowTitle(std::string&) = 0;

    virtual void update() = 0;

    virtual void clear() = 0;
};
