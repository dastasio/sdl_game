#include "InputMan.hpp"
#include <SDL2/SDL.h>

bool den::InputMan::process(Grid* g) {
    SDL_Event e;
    
    while( SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            return false;
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    if (state[SDL_SCANCODE_RIGHT])
        g->QueueMove(DIR_RIGHT);
    if (state[SDL_SCANCODE_LEFT])
        g->QueueMove(DIR_LEFT);
    return true;
}
