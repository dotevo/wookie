#include <wookie/rendering/SDL/SDLcontext.h>

SDLcontext::SDLcontext(){
    SDL_Init(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow(m_windowTitle.c_str(),
                              0, //x
                              0, //y
                              m_width, //width
                              m_height, //height
                              SDL_WINDOW_OPENGL);

    m_screenSurface = SDL_GetWindowSurface( m_window );
}

SDLcontext::~SDLcontext(){
    SDL_DestroyWindow(m_window);
}

void SDLcontext::setWindowTitle(std::string&){
}
