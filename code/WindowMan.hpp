#pragma once
#include "InputMan.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace den {
    
    class Window {
    public:
        ~Window();
        
        static Window* Get(const char* title,
                          int w = 1024, int h = 720,
                          int x = SDL_WINDOWPOS_UNDEFINED,
                          int y = SDL_WINDOWPOS_UNDEFINED);
        
        void StartLoop() { this->Loop(); }
    private:
        Window(const char* title,
               int w, int h,
               int x, int y );
        
        void Loop();
        
        SDL_Window* win;
        SDL_Renderer* renderer;
        
        static void InitSDL();
        static bool sdl_init;
    };
    
    bool Window::sdl_init = false;
}
