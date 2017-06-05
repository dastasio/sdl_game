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
    this->grid = new Block**[10];
    
    for (int i = 0; i < N_COLS; ++i) {
        this->grid[i] = new Block*[20];
        
        for (int j = 0; j < N_ROWS; ++j) {
            this->grid[i][j] = nullptr;
        }
    }
}

void den::Grid::Update() {
    /* for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            int type = rand() % 7;
            std::cout << type << std::endl;
            this->grid[i][j] = new Block(type, tile_s);
        }
    } */
    static Piece* p = nullptr;
    if (p == nullptr) {
        std::cout << time(0) << std::endl;
        p = new Piece(rand() % 7);
    }
    for (int k = 0; k < 4; ++k) {
        uint i, j;
        p->GetPos(k, &i, &j);
        this->NewBlock(p->type, i, j);
    }
    
}


bool den::Grid::ApplyGravity(den::Piece *p) {
    // BEFORE MOVING, ALL CURRENT BLOCKS NEED TO BE SET TO NULLPTR
    return true;
}

bool den::Grid::CheckCollision(uint i, uint j) {
    if ( i <= N_COLS && j <= N_COLS && this->grid[i][j] != nullptr)
        return true;
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
    if (!CheckCollision(i, j)) {
        this->grid[i][j] = new Block(type, tile_s);
        return true;
    }
    else
        return false;
}

void den::Grid::SetBlock(uint i, uint j, den::Block *val) {
    if (!this->CheckCollision(i, j)) {
        this->grid[i][j] = val;
    }
    else {
#ifndef NDEBUG
        std::cout << "[GAME INFO] Tried to move to occupied block (" << i << "; " <<
        j << ")" << std::endl;
#endif
    }
}
