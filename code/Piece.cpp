#include "Piece.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#define INIT_I 3
#define INIT_J 0

struct den::Offset {
    int off[4];
    int pv;
    
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
                this->off[0] = 10;   this->off[1] = 11;   this->off[2] = 12;   this->off[3] = 13;
                this->pv = 1;
                break;
            case 1:
                this->off[0] = 1;   this->off[1] = 10;  this->off[2] = 11;  this->off[3] = 12;
                this->pv = 2;
                break;
            case 2:
                this->off[0] = 0;   this->off[1] = 1;   this->off[2] = 10;  this->off[3] = 11;
                this->pv = 3;
                break;
            case 3:
                this->off[0] = 0;   this->off[1] = 1;   this->off[2] = 11;  this->off[3] = 12;
                this->pv = 1;
                break;
            case 4:
                this->off[0] = 1;   this->off[1] = 2;   this->off[2] = 10;  this->off[3] = 11;
                this->pv = 0;
                break;
            case 5:
                this->off[0] = 0;   this->off[1] = 10;  this->off[2] = 11;  this->off[3] = 12;
                this->pv = 2;
                break;
            case 6:
                this->off[0] = 2;   this->off[1] = 10;  this->off[2] = 11;  this->off[3] = 12;
                this->pv = 2;
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
    this->pivot = offs.pv;
    for (int k = 0; k < 4; ++k) {
        this->i[k] = (offs[k] % 10);
        this->j[k] = ((offs[k] - (offs[k] % 10)) / 10);
    }
    
    this->modI = INIT_I;
    this->modJ = INIT_J;
}

void den::Piece::moveI(int qnt) {
    this->modI += qnt;
}

void den::Piece::moveJ(int qnt) {
    this->modJ += qnt;
}

void den::Piece::GetPos(uint n, int *x, int *y) {
    *x = this->i[n] + this->modI;
    *y = this->j[n] + this->modJ;
}


void den::Piece::RotateClockwise() {
    int pv_i, pv_j;
    this->GetPos(this->pivot, &pv_i, &pv_j);
    
    for (int k = 0; k < 4; ++k) {
        int swp_j = -this->j[k];
        this->j[k] = this->i[k];
        this->i[k] = swp_j;
    }
    
    this->modI = pv_i - this->i[this->pivot];
    this->modJ = pv_j - this->j[this->pivot];
}

void den::Piece::SortDown() {
    for (int n = 0; n < 4; ++n) {
        for (int k = 3; k > (0 + n); --k) {
            if (this->j[k] > this->j[k - 1]) {
                int swp_i = this->i[k];
                int swp_j = this->j[k];
                
                this->i[k] = this->i[k-1];
                this->j[k] = this->j[k-1];
                this->i[k-1] = swp_i;
                this->j[k-1] = swp_j;
                
                if (k - 1 == this->pivot)
                    this->pivot++;
                else if (k == this->pivot)
                    this->pivot--;
            }
        }
    }
}

void den::Piece::SortRight() {
    for (int n = 0; n < 4; ++n) {
        for (int k = 3; k > (0 + n); --k) {
            if( this->i[k] > this->i[k - 1]) {
                int swp_i = this->i[k];
                int swp_j = this->j[k];
                
                this->i[k] = this->i[k - 1];
                this->j[k] = this->j[k - 1];
                this->i[k - 1] = swp_i;
                this->j[k - 1] = swp_j;
                
                if (k - 1 == this->pivot)
                    this->pivot++;
                else if (k == this->pivot)
                    this->pivot--;
            }
        }
    }
}

void den::Piece::SortLeft() {
    for (int n = 0; n < 4; ++n) {
        for (int k = 3; k > (0 + n); --k) {
            if( this->i[k] < this->i[k - 1]) {
                int swp_i = this->i[k];
                int swp_j = this->j[k];
                
                this->i[k] = this->i[k - 1];
                this->j[k] = this->j[k - 1];
                this->i[k - 1] = swp_i;
                this->j[k - 1] = swp_j;
                
                if (k - 1 == this->pivot)
                    this->pivot++;
                else if (k == this->pivot)
                    this->pivot--;
            }
        }
    }
}

