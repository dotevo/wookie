#pragma once

enum WindowMode
{
    WINDOWED,
    FULLSCREEN
};

class Context
{
public:
    virtual ~Context() = default;

    virtual int width() const = 0;

    virtual int height() const = 0;

    virtual WindowMode mode() const = 0;

    virtual void setWindowTitle(std::string&) = 0;

    virtual void update() = 0;

    virtual void clear() = 0;
};
