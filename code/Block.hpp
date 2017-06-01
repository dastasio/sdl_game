#pragma once
#include <SDL2/SDL.h>

namespace den {
    class Block {
    public:
        Block(SDL_Texture *tx,
              int x, int y,
              int w, int h);
        ~Block();
        
        void Draw(SDL_Renderer* r);
        
        virtual bool Collides() =0;
        
    private:
        SDL_Texture* texture;
        int w, h;
        
        SDL_Point center;
        
        bool shown;
    };
}

