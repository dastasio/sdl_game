#include "Block.hpp"

void den::Block::Draw(SDL_Renderer *r) {
    // Rectangle where block will be drawn
    SDL_Rect dest;
    dest.x = this->center.x - (this->w / 2);
    dest.y = this->center.y - (this->h / 2);
    dest.w = this->w;
    dest.h = this->h;
    
    if (this->shown)
        SDL_RenderCopy(r, this->texture, NULL, &dest);
}

den::Block::Block(SDL_Texture *tx, int x, int y, int w, int h) {
    this->texture = tx;
    
    this->w = w;
    this->h = h;
    
    this->center.x = x;
    this->center.y = y;
    
    this->shown = true;
}
