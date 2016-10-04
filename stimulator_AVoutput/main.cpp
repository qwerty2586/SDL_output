#include <iostream>
#include <SDL2/SDL.h>
#include "av_screen.h"

int main() {
    if (SDL_Init( SDL_INIT_EVERYTHING )==-1) {
        std::cout << "Something went wrong!" << SDL_GetError() << std::endl;
    } else {
        AVScreen *avScreen = new AVScreen();
    }


    return 0;
}