#include "Grid.hpp"
#include <iostream>
#include <cstdlib>
#define N_ROWS 20
#define N_COLS 10
#define INIT_I 2
#define INIT_J 0

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
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            int type = rand() % 7;
            std::cout << type << std::endl;
            this->grid[i][j] = new Block(type, tile_s);
        }
    }
}


bool den::Grid::ApplyGravity(den::Piece *p) {
    /*for (int tile_num = 0; tile_num < 4; ++tile_num) {
        SDL_Point* pos = &p->tiles[tile_num];
        
        if (CheckCollision(pos->x, pos->y + 1))
            return false;
    }
    for (int tile_num = 0; tile_num < 4; ++tile_num) {
        SDL_Point* pos = &p->tiles[tile_num];
        this->SetBlock(pos->x, ++pos->y, this->grid[pos->x][pos->y - 1]);
        this->SetBlock(pos->x, pos->y - 1, nullptr);
    } */
    return true;
}

bool den::Grid::CheckCollision(uint i, uint j) {
    bool good_intervals = i <= N_COLS && j <= N_COLS;
    if (this->grid[i][j] != nullptr && good_intervals)
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

SDL_Point den::Grid::NewBlock(int offset, int type) {
    /* getting i_ and j_ offsets from given int offset */
    int i_ = offset % 10;
    int j_ = (offset - i_) / 10;
    
    if (this->grid[INIT_I + i_][INIT_J + j_] != nullptr) {
#ifndef NDEBUG
        std::cerr << "[GAME INFO] Tried to create block in occupied tile."
        " GAME OVER!!" << std::endl;
#endif
        SDL_Point tbr;
        tbr.x = -1;
        tbr.y = -1;
        return tbr;
    }
    else {
        SDL_Point pos;
        pos.x = INIT_I + i_;
        pos.y = INIT_J + j_;
        this->grid[pos.x][pos.y] = new Block(type, tile_s);
        return pos;
    }
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
