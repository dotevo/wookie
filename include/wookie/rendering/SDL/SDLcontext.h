#pragma once
#ifdef HAVE_SDL

#include <string>
#include <wookie/rendering/RenderContext.h>
#include <SDL2/SDL.h>

class SDLcontext: public RenderContext
{
public:
    SDLcontext();

    ~SDLcontext();

    int width() const {return m_width;}

    int height() const {return m_height;}

    WindowMode mode() const {return m_mode;}

    void setWindowTitle(std::string&);

    SDL_Surface * getSurface() const { return m_screenSurface; }

    void update();

    void clear() {}
private:
    SDL_Window* m_window;
    SDL_Surface * m_screenSurface;

    WindowMode m_mode {WINDOWED};
    std::string m_windowTitle {"myGame"};
    int m_width {1024};
    int m_height {768};
    void handleEvent(SDL_Event *e);
};

#endif //HAVE_SDL
