#define SDL_MAIN_HANDLED
#include "WindowMan.hpp"
#include <iostream>

using namespace den;

int main() {
	SDL_SetMainReady();

    Window* w = Window::Get("Tetris", 400, 800);
    
    w->StartLoop();
    
	return 0;
}
