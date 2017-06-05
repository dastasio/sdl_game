#include "Piece.hpp"
#ifndef NDEBUG
#include <iostream>
#endif

struct den::Offset {
    int off[4];
    
    int operator[](int n) {
        if (n >= 0 && n < 4)
            return this->off[n];
        else
#ifndef NDEBUG
            std::cout << "[ERROR] Type requested is inexisting" << std::endl;
#endif
        return -1;
    }
    
    Offset(int type) {
        switch (type) {
            case 0:
                this->off[0] = 0;
                this->off[1] = 1;
                this->off[2] = 2;
                this->off[3] = 3;
                break;
            case 1:
                this->off[0] = 1;
                this->off[1] = 10;
                this->off[2] = 11;
                this->off[3] = 12;
                break;
            case 2:
                this->off[0] = 0;
                this->off[1] = 1;
                this->off[2] = 10;
                this->off[3] = 11;
                break;
            case 3:
                this->off[0] = 0;
                this->off[1] = 1;
                this->off[2] = 11;
                this->off[3] = 12;
                break;
            case 4:
                this->off[0] = 1;
                this->off[1] = 2;
                this->off[2] = 10;
                this->off[3] = 11;
                break;
            case 5:
                this->off[0] = 0;
                this->off[1] = 10;
                this->off[2] = 11;
                this->off[3] = 12;
                break;
            case 6:
                this->off[0] = 2;
                this->off[1] = 10;
                this->off[2] = 11;
                this->off[3] = 12;
            default:
#ifndef NDEBUG
                std::cout << "[ERROR] Requested inexisting type '" << type << "'" << std::endl;
#endif
                break;
        }
    }
};

den::Piece::Piece(int type, Grid* parent_grid) {
    this->p_grid = parent_grid;
    this->tiles = new SDL_Point[4];
    
    Offset offsets(type);
    
    /* generating blocks */
    for (int tile_num = 0; tile_num < 4; ++tile_num) {
        std::cout << type << "." << tile_num << " = " << offsets[tile_num] << std::endl;
        this->tiles[tile_num] = this->p_grid->NewBlock(offsets[tile_num], type);
    }
}
