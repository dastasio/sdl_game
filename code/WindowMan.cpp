#include "WindowMan.hpp"
#include <iostream>

den::Window::Window(const char* title,
                    int w, int h,
                    int x, int y) {
    
    if (!Window::sdl_init)
        Window::InitSDL();
    
    this->win = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
    if (this->win == nullptr) {
        std::cerr << "[ERROR] Could not create window '" << title << "':\n" << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    
    this->renderer = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) {
        std::cerr << "[ERROR] Could not create renderer for window '" << title << "':\n" << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}


void den::Window::InitSDL() {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        std::cerr << "Could not initialize SDL:\n" << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        int flags = IMG_INIT_PNG | IMG_INIT_JPG;
        if ( !(IMG_Init(flags)) & flags) {
            std::cerr << "Could not initialize SDL_image:\n" << IMG_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        else {
            Window::sdl_init = true;
        }
    }
}



void den::Window::Loop() {
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
    SDL_Delay(2000);
}
