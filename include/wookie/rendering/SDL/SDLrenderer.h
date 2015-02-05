#pragma once
#ifdef HAVE_SDL

#include <wookie/rendering/SDL/SDLcontext.h>
#include <wookie/rendering/Renderer.h>
#include <wookie/rendering/Renderable.h>

class SDLrenderer : public Renderer
{
public:
    SDLrenderer();
    virtual ~SDLrenderer() = default;
    virtual void initialize(std::unique_ptr<Context>&) override;
    virtual void render(Renderable const&) override;
private:
    SDLcontext * m_context;
};


#endif
