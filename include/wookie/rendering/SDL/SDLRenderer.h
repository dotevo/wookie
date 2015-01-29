#pragma once
#ifdef HAVE_SDL

#include <wookie/rendering/Renderer.h>
#include <wookie/rendering/Renderable.h>

class SDLRenderer : public Renderer
{
public:
    SDLRenderer();
    virtual ~SDLRenderer() = default;

    virtual void render(Renderable&) override;
};


#endif
