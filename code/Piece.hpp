#pragma once
#include "Block.hpp"
#include "Grid.hpp"

namespace den {
    class Grid;
    
    struct Offset;
    struct Piece {
        uint j[4];
        uint i[4];
        uint type;
        
        Piece(uint t_);
        void GetPos(uint n, uint *x, uint *y);
    };
}
