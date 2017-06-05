#include "TextureMan.hpp"
#include <iostream>

den::TextureMan::TextureMan(SDL_Renderer* r) {
    this->renderer = r;
}


SDL_Texture* den::TextureMan::Load(const char* path) {
    SDL_Surface* surface = this->Read(path);
    
    return SDL_CreateTextureFromSurface(this->renderer, surface);
}


SDL_Surface* den::TextureMan::Read(const char* path) {
    
    SDL_Surface* surface = IMG_Load(path);
    
    if (surface == NULL) {
        std::cerr << "[WARNING] Texture '" << path << "' could not be read:\n" <<
        IMG_GetError() << std::endl;
    }
    
    return surface;
}
