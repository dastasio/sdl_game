#include "Piece.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#define INIT_I 2
#define INIT_J 0

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
                this->off[0] = 0;   this->off[1] = 1;   this->off[2] = 2;   this->off[3] = 3;
                break;
            case 1:
                this->off[0] = 1;   this->off[1] = 10;  this->off[2] = 11;  this->off[3] = 12;
                break;
            case 2:
                this->off[0] = 0;   this->off[1] = 1;   this->off[2] = 10;  this->off[3] = 11;
                break;
            case 3:
                this->off[0] = 0;   this->off[1] = 1;   this->off[2] = 11;  this->off[3] = 12;
                break;
            case 4:
                this->off[0] = 1;   this->off[1] = 2;   this->off[2] = 10;  this->off[3] = 11;
                break;
            case 5:
                this->off[0] = 0;   this->off[1] = 10;  this->off[2] = 11;  this->off[3] = 12;
                break;
            case 6:
                this->off[0] = 2;   this->off[1] = 10;  this->off[2] = 11;  this->off[3] = 12;
            default:
#ifndef NDEBUG
                std::cout << "[ERROR] Requested inexisting type '" << type << "'" << std::endl;
#endif
                break;
        }
    }
};

den::Piece::Piece(uint t_) {
    this->type = t_;
    Offset offs(this->type);
    
    for (int k = 0; k < 4; ++k) {
        this->i[k] = INIT_I + (offs[k] % 10);
        this->j[k] = INIT_J + ((offs[k] - (offs[k] % 10)) / 10);
    }
}

void den::Piece::GetPos(uint n, uint *x, uint *y) {
    *x = this->i[n];
    *y = this->j[n];
}
