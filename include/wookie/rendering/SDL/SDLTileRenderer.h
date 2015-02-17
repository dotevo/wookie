#pragma once
#ifdef HAVE_SDL

#include <wookie/rendering/SDL/SDLcontext.h>
#include <wookie/rendering/Renderer.h>
#include <wookie/game/isometric/Renderable.h>

struct Camera;

class SDLTileRenderer : public Renderer
{
public:
    SDLTileRenderer();
    virtual ~SDLTileRenderer() = default;
    virtual void initialize(std::unique_ptr<RenderContext>&) override;
    virtual void render(Renderable const&, Camera const&) override;
private:
    SDLcontext * m_context;
};


#endif
