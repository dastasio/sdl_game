#include "WindowMan.hpp"
#include <iostream>

using namespace den;

int main() {
    Window* w = new Window("hello");
    
    w->StartLoop();
    
}
