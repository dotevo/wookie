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
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDLcontext::~SDLcontext(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void SDLcontext::setWindowTitle(std::string&){
}

void SDLcontext::update(){
    SDL_RenderPresent(m_renderer);
    //Events
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        handleEvent(&e);
    }
}

void SDLcontext::clear(){
    SDL_RenderClear(m_renderer);
}

void SDLcontext::handleEvent(SDL_Event *event){
    if(event->type == SDL_WINDOWEVENT) {
        if(event->window.windowID == SDL_GetWindowID(m_window)){
            switch (event->window.event) {
            /*
                case SDL_WINDOWEVENT_SHOWN:
                    onShow();
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    onHide();
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    onExpose();
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    onMove(event->window.data1, event->window.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    onResize(event->window.data1, event->window.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    onMinimize();
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    onMaximize();
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    onRestore();
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    onEnter();
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    onLeave();
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    onFocusIn();
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    onFocusOut();
                    break;
                    */
                case SDL_WINDOWEVENT_CLOSE:
                    onClose();
                    break;
                default:
                    break;
                }
        }
    }
}
