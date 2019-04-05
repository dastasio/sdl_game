#include "WindowMan.hpp"
#include "TextureMan.hpp"
#include "Grid.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/* Singleton GetInstance
 * --------------------------------------
 * Returns window instance
 *
 * title: title of the window to be created
 * w, h: width and height of the window (default: 1024x720)
 * x, y: x and y positions of the window (default: undefined)
 */
den::Window* den::Window::Get(const char* title,
                 int w, int h,
                 int x, int y) {
    
    static Window* instance = new Window(title, w, h, x, y);
    return instance;
}

/* Private Constructor: Window
 * --------------------------------------
 * Constructs Window instance and
 * creates window with given data
 *
 * title: title of the window to be created
 * w, h: width and height of the window
 * x, y: x and y positions of the window
 */
den::Window::Window(const char* title,
                    int w, int h,
                    int x, int y) {
    
    //if (!Window::sdl_init)  /* checking sdl init flag */
        Window::InitSDL();  /* if it hasn't been done, initalize SDL */
    
    
    this->win = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
    if (this->win == nullptr) { /* if window creation wasn't possible, report error and exit */
        std::cerr << "[ERROR] Could not create window '" << title << "':\n";
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    
    this->renderer = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) {
        std::cerr << "[ERROR] Could not create renderer for window '" << title << "':\n";
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); /* setting clear color to black */
    
    
    /* loading textures */
    TextureMan* tman = new TextureMan(this->renderer);
    Block::texture = tman->Load("blocks.png");
    
    /* setting random seed for tetraminos generation */
    srand(time(0));
    srand(rand() % rand());
    srand(rand());
}

/* Func: InitSDL
 * ---------------------------------------
 * Initializes SDL and SDL_image subsystem
 */
void den::Window::InitSDL() {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        std::cerr << "Could not initialize SDL:\n" << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        int flags = IMG_INIT_PNG | IMG_INIT_JPG;
        if ( !(IMG_Init(flags)) & flags) {
            std::cerr << "Could not initialize SDL_image:\n" << IMG_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        else {
            //Window::sdl_init = true; /* if init is successful, set flag to true */
        }
    }
}


/* Func: Loop
 * ---------------------------------------
 * Executes game loop,
 * it currently is the same for all windows
 * but flexibility may be added later
 */
void den::Window::Loop() {
    InputMan input = InputMan::instance();
    Grid* main_g = new Grid(this->renderer, 40);
    
    bool run = true;
    
    double previous = SDL_GetTicks();
    double lag = 0.0;
    while( input.process(main_g) && run) {
        Uint32 speed = main_g->getMSperGravity();
        
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        SDL_RenderClear(this->renderer);
        
        run = main_g->Update(false);
        while(lag >= speed) {
            run = main_g->Update(true);
            lag -= speed;
            if (speed < 900)
                lag = 0;
        }
        main_g->Draw();
        
        SDL_RenderPresent(this->renderer);
        SDL_Delay(1000/60);
    }
    
    delete main_g;
    delete this;
}


/* Deconstructor: Window
 * ----------------------------------------
 * Destroys window and frees memory
 */
den::Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->win);
}






