#include "Block.hpp"
SDL_Texture* den::Block::texture;

void den::Block::Draw(SDL_Renderer *r, uint _x, uint _y) {
    // Rectangle where block will be drawn
    SDL_Rect dest;
    dest.x = _x;
    dest.y = _y;
    dest.w = this->size;
    dest.h = this->size;
    
    SDL_RenderCopy(r, Block::texture, &this->orig, &dest);
}

den::Block::Block(int type, uint block_size) {
    this->size = block_size;
    
    this->orig.w = TEXTURE_SIZE;
    this->orig.h = TEXTURE_SIZE;
    this->orig.y = 0;
    this->orig.x = type * TEXTURE_SIZE;
}
