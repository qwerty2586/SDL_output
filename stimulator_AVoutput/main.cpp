#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "av_screen.h"
#include "test_config.h"

int main( int argc, char* args[] ) {

    if (SDL_Init( SDL_INIT_EVERYTHING )==-1) {
        std::cout << "Something went wrong!" << SDL_GetError() << std::endl;
    } else {

        int imgFlags = IMG_INIT_JPG + IMG_INIT_PNG;

        if( ( IMG_Init( imgFlags ) & imgFlags ) ) {


            AVScreen *avScreen = new AVScreen();
            avScreen->clearScreen();
            avScreen->loadConfig(testConfig());

            testLoop(avScreen);

            SDL_Delay(1000);
            delete avScreen;
            SDL_Quit();


        }



    }



    return 0;
}