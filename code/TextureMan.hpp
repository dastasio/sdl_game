#pragma once
#include "SDL2/SDL_image.h"

namespace den {
    
    class TextureMan {
    public:
        TextureMan(SDL_Renderer* r);
        ~TextureMan() {}
        
        SDL_Texture* Load(const char* path);
    private:
        SDL_Surface* Read(const char* path);
        
        SDL_Renderer* renderer;
    };
}
