#pragma once
#include "Block.hpp"
#include "Grid.hpp"

namespace den {
    class Grid;
    
    struct Offset;
    struct Piece {
        uint j[4];
        uint i[4];
        uint modI, modJ;
        uint type, pivot;
        
        
        
        Piece(uint t_);
        void GetPos(uint n, uint *x, uint *y);
        
        void moveI(int qnt);
        void moveJ(int qnt);
        
        void SortDown();
        void SortRight();
        void SortLeft();
    };
}
