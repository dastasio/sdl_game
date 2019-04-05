#pragma once
#include "Piece.hpp"
#include <vector>
#define DIR_RIGHT 1
#define DIR_LEFT  0

namespace den {
    struct Piece;
    class Grid {
    public:
        Grid(SDL_Renderer* r, int tilesize);
        ~Grid();
        
        void Draw();
        bool Update(bool vertical);
        void CheckGoal();
        
        void QueueMove(bool dir);
        void QueueRotate();
        
        Uint32 getMSperGravity();
        void setSpeed(bool quick);
    private:
        Block*** grid;
        
        SDL_Renderer* renderer;
        
        void DeleteRow(int row);
        
        void Move(Piece* p, bool dir);
        bool CheckHorCollision(Piece* p, bool dir);
        
        bool CheckDownCollision(Piece* p);
        Piece* ApplyGravity(Piece* p);
        
        bool CheckCollision(Uint32 i, Uint32 j);
        void SetBlock(Uint32 i, Uint32 j, Block* val);
        void NewBlock(Uint32 type, Uint32 i, Uint32 j);
        
        std::vector<bool> move_queue;
        std::vector<bool> rot_queue;
        Uint32 ms_per_gravity;
        int tile_s;
    };
}
