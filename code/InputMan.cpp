#include "InputMan.hpp"
#include <SDL2/SDL.h>

bool den::InputMan::process(Grid* g) {
    SDL_Event e;
    static Uint32 previous = SDL_GetTicks();
    static Uint32 lag = 0;
    Uint32 current = SDL_GetTicks();
    Uint32 elapsed = current - previous;
    previous = current;
    lag += elapsed;
    
    while( SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            return false;
    }
    g->setSpeed(false);
    if (lag > 100) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        
        if (state[SDL_SCANCODE_RIGHT]) {
            g->QueueMove(DIR_RIGHT);
        }
        if (state[SDL_SCANCODE_LEFT]) {
            g->QueueMove(DIR_LEFT);
        }
        if (state[SDL_SCANCODE_DOWN]) {
            g->setSpeed(true);
        }
        lag -= 100;
    }
    return true;
}
