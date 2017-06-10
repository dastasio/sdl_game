#include "Grid.hpp"
#include <iostream>
#include <cstdlib>
#define N_ROWS 20
#define N_COLS 10

/* Constructor: Grid
 * ----------------------------------------------
 * r:        renderer used for rendering blocks
 * tilesize: length of side of blocks (which are squares)
 */
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


/* Func: Update
 * -------------------------------------------------
 * Applies physics and game mechanics to grid
 *
 * returns: false if game is over; else true
 */
bool den::Grid::Update(bool vertical) {
    /* static tetramino,
     * all physics will be applied to it,
     * until it reaches bottom and a new one is created
     */
    static Piece* p = nullptr;
    if (p == nullptr) {
        this->CheckGoal();
        /* new (random) tetramino is created if active one becomes 'null' */
        p = new Piece(rand() % 7);
    }
    else {
        /* applying horizontal movement */
        if (!vertical) {
            while (this->move_queue.size() > 0) {
                this->Move(p, move_queue.back());
                this->move_queue.erase(this->move_queue.end());
            }
            while (this->rot_queue.size() > 0) {
                /* deleting before rotation */
                for (int k = 0; k < 4; ++k ) {
                    int i, j;
                    p->GetPos(k, &i, &j);
                    this->grid[i][j] = nullptr;
                }
                p->RotateClockwise();
                this->rot_queue.erase(this->rot_queue.end());
            }
            CheckDownCollision(p);
        }
        else {
            /* if tetramino is not new and enough time has passed, gravity is applied to it */
            p = ApplyGravity(p);
        }
    }
    
    /* if tetramino is null, then the tiles that made it up 
     * are already in the grid and won't need to be recreated;
     * else, all tiles of the current tetramino are created anew
     */
    if (p != nullptr) {
        /* game is over if the place where the new tetramino is
         * is already occupied
         */
        bool game_over = false;
        for (int k = 0; k < 4 && !game_over; ++k) {
            int i, j;
            p->GetPos(k, &i, &j);
            if (this->CheckCollision(i, j))
                game_over = true;
        }
        if (game_over) {
            std::cout << "GAME OVER!" << std::endl;
            return false;
        }
        else {
            /* if game is not over, tiles are generated to be rendered */
            for (int k = 0; k < 4 && p != nullptr; ++k) {
                int i, j;
                p->GetPos(k, &i, &j);
                this->NewBlock(p->type, i, j);
            }
        }
    }
    
    /* returning true to indicate that game continues */
    return true;
}


/* Func: ApplyGravity
 * -------------------------------------------------------
 * Checks if given tetramino has reached bottom
 * and applies gravity accordingly
 *
 * p: active tetramino, to which gravity will be applied
 *
 * returns:
 * - nullptr, if tetramino has reached bottom and can't fall anymore
 * - pointer to updated tetramino, if gravity has been applied successfully
 */
den::Piece* den::Grid::ApplyGravity(den::Piece *p) {
    /* if there is no downward collision,
     * the tetramino will be moved
     */
    if (this->CheckDownCollision(p)) {
        for (int k = 0; k < 4; ++k) {
            int i, j;
            p->GetPos(k, &i, &j);
            this->NewBlock(p->type, i, j);
        }
        return nullptr;
    }
    else {
        /* incrementing 'j' value(row) */
        p->moveJ(1);
    }
    return p;
}


void den::Grid::QueueMove(bool dir) {
    this->move_queue.push_back(dir);
}

void den::Grid::QueueRotate() {
    this->rot_queue.push_back(true);
}

void den::Grid::Move(Piece* p, bool dir) {
    if (!this->CheckHorCollision(p, dir)) {
        int d = (dir * 2) - 1;
        p->moveI(d);
    }
}

/* Func: CheckDownCollision
 * -----------------------------------------------------
 * Checks wether given tetramino can move downward
 * after having deleted all its tiles from the grid
 *
 * p: tetramino to be checked
 *
 * returns: true if any of the blocks in the tetramino can't move down; else false
 */
bool den::Grid::CheckDownCollision(den::Piece *p) {
    p->SortDown();
    // current tiles are deleted before checking for collision
    for (int k = 0; k < 4; ++k) {
        int i, j;
        p->GetPos(k, &i, &j);
        this->grid[i][j] = nullptr;
    }
    
    /* there is no collision only if all tiles can move down */
    for (int k = 0; k < 4; ++k) {
        int i, j;
        p->GetPos(k, &i, &j);
        if (j >= (N_ROWS - 1) || this->grid[i][j + 1] != nullptr)
            return true;
    }
    return false;
}


bool den::Grid::CheckHorCollision(den::Piece *p, bool dir) {
    // sorting tiles in appropriate order
    dir == DIR_RIGHT ? p->SortRight():p->SortLeft();
    int d = (dir * 2) - 1;
    
    for (int k = 0; k < 4; ++k) {
        int i, j;
        p->GetPos(k, &i, &j);
        this->grid[i][j] = nullptr;
    }
    
    for (int k = 0; k < 4; ++k) {
        int i, j;
        p->GetPos(k, &i, &j);
        // TODO: fix this cast to int
        if (int(i) + d < 0 || i + d >= N_COLS || this->grid[i + d][j] != nullptr)
            return true;
    }
    return false;
}


/* Func: CheckCollision
 * ------------------------------------------------------------
 * Checks if indicated tile is occupied in the grid
 *
 * i, j: column and row of the tile to be checked
 * returns: true if tile is occupied; else false
 */
bool den::Grid::CheckCollision(uint i, uint j) {
    if ( i >= N_COLS || j >= N_ROWS)
        return true;
    else if ( this->grid[i][j] != nullptr)
        return true;
    else
        return false;
}


/* Func: Draw
 * -------------------------------------------------------
 * goes through all blocks in the grid and calls their 'draw' function
 */
void den::Grid::Draw() {
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (this->grid[i][j] != nullptr)
                grid[i][j]->Draw(this->renderer, i * tile_s, j * tile_s);
        }
    }
}


/* Func: NewBlock
 * ---------------------------------------------------------
 * constructs new block in given position of the grid
 *
 * type: type of the tetramino the new block belongs to
 * i, j: position of the new block
 */
void den::Grid::NewBlock(uint type, uint i, uint j) {
    this->grid[i][j] = new Block(type, tile_s);
}


/* Func: SetBlock
 * ---------------------------------------------------------
 * sets given tile of the grid to an existing block
 *
 * i, j: position of the block in the grid
 * val:  value the block has to take
 */
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

Uint32 den::Grid::getMSperGravity() {
    return this->ms_per_gravity;
}

void den::Grid::setSpeed(bool quick) {
    ms_per_gravity = quick ? 17:900;
}


void den::Grid::CheckGoal() {
    std::vector<int> complete_rows;
    for (int row = 0; row < N_ROWS; ++row) {
        int i = 0;
        for (; i >= 0 && i < N_COLS; ++i) {
            if (this->grid[i][row] == nullptr)
                i = -2;
        }
        
        if (i != -1)
            complete_rows.push_back(row);
    }
    
    for (int k = 0; k < complete_rows.size(); ++k)
        this->DeleteRow(complete_rows[k]);
    complete_rows.clear();
}

void den::Grid::DeleteRow(int row) {
    for (int elem = 0; elem < N_COLS; ++elem)
        this->grid[elem][row] = nullptr;
    
    for (int i = 0; i < N_COLS; ++i) {
        for (int j = row; j > 0; --j) {
            this->grid[i][j] = this->grid[i][j-1];
        }
        
        this->grid[i][0] = nullptr;
    }
}

/* Deconstructor: Grid
 * -------------------------------------------------
 * deletes all blocks and deletes grid
 */
den::Grid::~Grid() {
    for (int i = 0; i < N_COLS; i++) {
        delete this->grid[i];
    }
    delete this->grid;
}
