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
        void SetPos(uint n, uint i_, uint j_);
        bool IsPartOf(uint i_, uint j_);
        
        void SortDown();
        void SortRight();
        void SortLeft();
    };
}
