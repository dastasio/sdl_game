#include "WindowMan.hpp"
#include <iostream>

using namespace den;

int main() {
    Window* w = Window::Get("Tetris", 400, 800, 0, 0);
    
    w->StartLoop();
    
}
