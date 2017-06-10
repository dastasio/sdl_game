#pragma once
#include "Block.hpp"
#include "Grid.hpp"

namespace den {
    class Grid;
    
    struct Offset;
    struct Piece {
        int j[4];
        int i[4];
        int modI, modJ;
        uint type, pivot;
        
        
        
        Piece(uint t_);
        void GetPos(uint n, int *x, int *y);
        
        void moveI(int qnt);
        void moveJ(int qnt);
        
        void RotateClockwise();
        
        void SortDown();
        void SortRight();
        void SortLeft();
    };
}
