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
        Uint32 type, pivot;
        
        
        
        Piece(Uint32 t_);
        void GetPos(Uint32 n, int *x, int *y);
        
        void moveI(int qnt);
        void moveJ(int qnt);
        
        void RotateClockwise();
        
        void SortDown();
        void SortRight();
        void SortLeft();
    };
}
