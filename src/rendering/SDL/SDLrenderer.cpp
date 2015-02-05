#ifdef HAVE_SDL
#include <wookie/rendering/SDL/SDLrenderer.h>

SDLrenderer::SDLrenderer(){

}

void SDLrenderer::initialize(std::unique_ptr<Context>& context) {
    m_context = (SDLcontext*)context.get();
}

void SDLrenderer::render(Renderable const&) {

    SDL_FillRect( m_context->getSurface(), NULL, SDL_MapRGB( m_context->getSurface()->format, 0xFF, 0xFF, 0xFF ) );
    m_context->update();
}

#endif
