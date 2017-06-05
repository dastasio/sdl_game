#pragma once
#include "Grid.hpp"

namespace den {
    class Grid;
    
    struct Offset;
    
    class Piece {
        friend class Grid;
    public:
        Piece(int type, Grid* parent_grid);
        ~Piece();
        
    protected:
        SDL_Point* tiles;
    private:
        Grid* p_grid;
    };
}
