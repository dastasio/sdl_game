#include "Piece.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#define INIT_I 3
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
                break;
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

void den::Piece::SetPos(uint n, uint i_, uint j_) {
    this->i[n] = i_;
    this->j[n] = j_;
}

bool den::Piece::IsPartOf(uint i_, uint j_) {
    for (int k = 0; k < 4; ++k) {
        if (this->i[k] == i_ && this->j[k] == j_)
            return true;
    }
    return false;
}

void den::Piece::SortDown() {
    for (int n = 0; n < 4; ++n) {
        for (int k = 3; k > (0 + n); --k) {
            if (this->j[k] > this->j[k - 1]) {
                uint swp_i = this->i[k];
                uint swp_j = this->j[k];
                
                this->i[k] = this->i[k-1];
                this->j[k] = this->j[k-1];
                this->i[k-1] = swp_i;
                this->j[k-1] = swp_j;
            }
        }
    }
}

void den::Piece::SortRight() {
    for (int n = 0; n < 4; ++n) {
        for (int k = 3; k > (0 + n); --k) {
            if( this->i[k] > this->i[k - 1]) {
                uint swp_i = this->i[k];
                uint swp_j = this->j[k];
                
                this->i[k] = this->i[k - 1];
                this->j[k] = this->j[k - 1];
                this->i[k - 1] = swp_i;
                this->j[k - 1] = swp_j;
            }
        }
    }
}

void den::Piece::SortLeft() {
    for (int n = 0; n < 4; ++n) {
        for (int k = 3; k > (0 + n); --k) {
            if( this->i[k] < this->i[k - 1]) {
                uint swp_i = this->i[k];
                uint swp_j = this->j[k];
                
                this->i[k] = this->i[k - 1];
                this->j[k] = this->j[k - 1];
                this->i[k - 1] = swp_i;
                this->j[k - 1] = swp_j;
            }
        }
    }
}

