#pragma once
#include "Block.hpp"
#include "Piece.hpp"

namespace den {
    struct Piece;
    class Grid {
        friend class Piece;
    public:
        Grid(SDL_Renderer* r, int tilesize);
        ~Grid();
        
        void Draw();
        void Update();
    private:
        Block*** grid;
        
        SDL_Renderer* renderer;
        
        bool CheckCollision(uint i, uint j);
        bool ApplyGravity(Piece* p);
        void SetBlock(uint i, uint j, Block* val);
        
        int tile_s;
    protected:
        SDL_Point NewBlock(int offset, int type);
    };
}
