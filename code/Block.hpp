#pragma once
#include <SDL2/SDL.h>
#define TEXTURE_SIZE 200

namespace den {
    class Block {
    public:
        Block(uint type, uint block_size);
        ~Block();
        
        void Draw(SDL_Renderer* r, uint _x, uint _y);
        
        bool Collides();
        
        static SDL_Texture* texture;
    private:
        uint size;
        
        SDL_Rect orig;
    };
    
    
}

