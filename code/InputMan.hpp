#pragma once
#include "Grid.hpp"

namespace den {
    
    class InputMan {
    public:
        
        static InputMan& instance() {
            static InputMan* inst = new InputMan();
            return *inst;
        }
        
        bool process(Grid* g);
    private:
        InputMan() {}
    };
}
