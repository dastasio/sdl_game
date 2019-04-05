#include "Block.hpp"
SDL_Texture* den::Block::texture;

/* Func: Draw
 * --------------------------------------------------------
 * Renders block to given coordinates
 *
 * r:      renderer to be used for rendering
 * _x, _y: window coordinates where block will be drawn
 */
void den::Block::Draw(SDL_Renderer *r, Uint32 _x, Uint32 _y) {
    /* setting destination rectangle, where block will be drawn */
    SDL_Rect dest;
    dest.x = _x;
    dest.y = _y;
    dest.w = this->size;
    dest.h = this->size;
    
    /* rendering texture to given coordinates */
    SDL_RenderCopy(r, Block::texture, &this->orig, &dest);
}


/* Constructor: Block
 * --------------------------------------------------------
 * type:       type of tetramino this block belongs to
 * block_size: size of the block when it will be rendered
 */
den::Block::Block(int type, Uint32 block_size) {
    this->size = block_size;
    
    /* setting origin rectangle where texture will be read */
    this->orig.w = TEXTURE_SIZE;
    this->orig.h = TEXTURE_SIZE;
    this->orig.y = 0;
    this->orig.x = type * TEXTURE_SIZE;
}

/* Deconstructor: Block
 */
den::Block::~Block() {
    delete &this->size;
}
