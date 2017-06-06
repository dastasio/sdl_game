#include "Grid.hpp"
#include <iostream>
#include <cstdlib>
#define N_ROWS 20
#define N_COLS 10

den::Grid::Grid(SDL_Renderer* r, int tilesize) {
    this->renderer = r;
    this->tile_s = tilesize;
    
    // initializing an empty grid
    // made of a matrix of Block pointers
    // Block*[i][j]
    // i = 10
    // j = 20
    this->grid = new Block**[N_COLS];
    
    for (int i = 0; i < N_COLS; ++i) {
        this->grid[i] = new Block*[N_ROWS];
        
        for (int j = 0; j < N_ROWS; ++j) {
            this->grid[i][j] = nullptr;
        }
    }
}

void den::Grid::Update() {
    static Piece* p = nullptr;
    if (p == nullptr) {
        p = new Piece(rand() % 7);
    }
    else {
        p = ApplyGravity(p);
    }
    
    for (int k = 0; k < 4 && p != nullptr; ++k) {
        this->NewBlock(p->type, p->i[k], p->j[k]);
    }
    
}

// returns new (updated)tetramino
den::Piece* den::Grid::ApplyGravity(den::Piece *p) {
    for (int k = 0; k < 4; ++k) {
        uint i, j;
        p->GetPos(k, &i, &j);
        if (!CheckCollision(i, ++j, p)) {
            this->SetBlock(i, j, this->grid[i][j-1]);
            this->SetBlock(i, j - 1, nullptr);
            
            p->SetPos(k, i, j);
        }
        else {
            for (int k1 = 0; k1 < 4; ++k1) {
                this->NewBlock(p->type, p->i[k], p->j[k]);
            }
            delete p;
            return nullptr;
        }
    }
    return p;
}

bool den::Grid::CheckCollision(uint i, uint j, Piece* p) {
    if ( i >= N_COLS || j >= N_ROWS)
        return true;
    else if ( this->grid[i][j] != nullptr) {
        bool same_tetramino = false;
        if (p != nullptr)
            same_tetramino = p->IsPartOf(i, j);
        return !same_tetramino;
    }
    else
        return false;
}

void den::Grid::Draw() {
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (this->grid[i][j] != nullptr)
                grid[i][j]->Draw(this->renderer, i * tile_s, j * tile_s);
        }
    }
}

bool den::Grid::NewBlock(uint type, uint i, uint j) {
    if (!CheckCollision(i, j, nullptr)) {
        this->grid[i][j] = new Block(type, tile_s);
        return true;
    }
    else
        return false;
}

void den::Grid::SetBlock(uint i, uint j, den::Block *val) {
    if (!this->CheckCollision(i, j, nullptr)) {
        this->grid[i][j] = val;
    }
    else {
#ifndef NDEBUG
        std::cout << "[GAME INFO] Tried to move to occupied block (" << i << "; " <<
        j << ")" << std::endl;
#endif
    }
}
