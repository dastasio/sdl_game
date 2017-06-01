#include "InputMan.hpp"
#include <SDL2/SDL.h>

bool den::InputMan::process() {
    SDL_Event e;
    
    while( SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            return false;
    }
    return true;
}
