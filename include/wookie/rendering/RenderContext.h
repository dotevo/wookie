#pragma once

#include <wookie/core/WObject.h>
#include <string>

enum WindowMode
{
    WINDOWED,
    FULLSCREEN
};

class RenderContext :public WObject
{
public:
    virtual ~RenderContext() = default;

    virtual int width() const = 0;

    virtual int height() const = 0;

    virtual WindowMode mode() const = 0;

    virtual void setWindowTitle(std::string&) = 0;

    virtual void update() = 0;

    virtual void clear() = 0;

    sigslot::signal0<> onClose;
};
