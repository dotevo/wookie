#ifdef HAVE_SDL
#include <wookie/rendering/SDL/SDLTileRenderer.h>

SDLTileRenderer::SDLTileRenderer(){

}

void SDLTileRenderer::initialize(std::unique_ptr<RenderContext>& context) {
    m_context = (SDLcontext*)context.get();
}

void SDLTileRenderer::render(Renderable const&, Camera const&) {

    SDL_FillRect( m_context->getSurface(), NULL, SDL_MapRGB( m_context->getSurface()->format, 0xFF, 0xFF, 0xFF ) );
    m_context->update();
}

#endif
