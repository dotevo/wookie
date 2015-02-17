#ifdef HAVE_SDL
#include <wookie/rendering/SDL/SDLTileRenderer.h>

SDLTileRenderer::SDLTileRenderer(){

}

void SDLTileRenderer::initialize(std::unique_ptr<RenderContext>& context) {
    m_context = (SDLcontext*)context.get();
}

void SDLTileRenderer::render(Renderable const& rend, Camera const&) {
    SDL_Rect DestR;
    DestR.x = 200+32*rend.gridX+32*rend.gridY;
    DestR.y = 200+16*rend.gridX-16*rend.gridY;
    DestR.w = rend.img->getWidth();
    DestR.h = rend.img->getHeight();

    SDL_Texture * tex = SDL_CreateTextureFromSurface(m_context->getRenderer(), rend.img->getSurface());
    SDL_RenderCopy(m_context->getRenderer(), tex, NULL, &DestR);
//    SDL_FillRect( m_context->getSurface(), NULL, SDL_MapRGB( m_context->getSurface()->format, 0xFF, 0xFF, 0xFF ) );
}

#endif
