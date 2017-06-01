#pragma once

namespace den {
    
    class InputMan {
    public:
        
        static InputMan& instance() {
            static InputMan* inst = new InputMan();
            return *inst;
        }
        
        bool process();
    private:
        InputMan() {}
    };
}
