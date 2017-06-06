#pragma once
#include "Piece.hpp"

namespace den {
    struct Piece;
    class Grid {
    public:
        Grid(SDL_Renderer* r, int tilesize);
        ~Grid();
        
        void Draw();
        void Update();
    private:
        Block*** grid;
        
        SDL_Renderer* renderer;
        
        bool CheckDownCollision(Piece* p);
        bool CheckCollision(uint i, uint j);
        Piece* ApplyGravity(Piece* p);
        void SetBlock(uint i, uint j, Block* val);
        
        int tile_s;
        
        bool NewBlock(uint type, uint i, uint j);
    };
}
