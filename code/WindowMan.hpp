#pragma once
#include "InputMan.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace den {
    
    class Window {
    public:
        Window(const char* title,
                  int w = 1024, int h = 720,
                  int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);
        ~Window();
        
        
        void StartLoop() { this->Loop(); }
    private:
        void Loop();
        
        SDL_Window* win;
        SDL_Renderer* renderer;
        
        static void InitSDL();
        static bool sdl_init;
    };
    
    bool Window::sdl_init = false;
}
