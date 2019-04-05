#pragma once
#include <SDL2/SDL.h>
#define TEXTURE_SIZE 200

namespace den {
    class Block {
    public:
        Block(int type, Uint32 block_size);
        ~Block();
        
        void Draw(SDL_Renderer* r, Uint32 _x, Uint32 _y);
        
        static SDL_Texture* texture;
    private:
        Uint32 size;
        
        SDL_Rect orig;
    };
    
    
}

