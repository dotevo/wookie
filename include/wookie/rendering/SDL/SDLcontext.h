#pragma once
#ifdef HAVE_SDL

#include <string>
#include <wookie/rendering/Context.h>
#include <SDL2/SDL.h>

class SDLcontext: public Context
{
public:
    SDLcontext();

    ~SDLcontext();

    int width() const {return m_width;}

    int height() const {return m_height;}

    WindowMode mode() const {return m_mode;}

    void setWindowTitle(std::string&);

    SDL_Surface * getSurface() const { return m_screenSurface; }

    void update() { SDL_UpdateWindowSurface( m_window ); }
private:
    SDL_Window* m_window;
    SDL_Surface * m_screenSurface;

    WindowMode m_mode {WINDOWED};
    std::string m_windowTitle {"myGame"};
    int m_width {1024};
    int m_height {768};
};

#endif //HAVE_SDL
