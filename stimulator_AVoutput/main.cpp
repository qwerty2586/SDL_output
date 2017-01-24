/**
 * \ingroup stimulator_Events
 *
 * Program slouzi jako alternativa k LED vystupum
 * stimulatoru a zobrazovani obrazku a prehravani zvuku
 * pomoci knihovny SDL, a rozsiruje tim vystupy stimulatoru na monitor.
 *
 * Pouziva knihovny SDL2, wiringPi a pugixml
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "av_screen.h"
#include "test_config.h"

#define EXIT_SDL_INIT_ERROR 100
#define EXIT_SDL_IMG_INIT_ERROR 101
#define EXIT_SDL_MIX_INIT_ERROR 102

int main(int argc, char *args[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << "Something went wrong!" << SDL_GetError() << std::endl;
        return EXIT_SDL_INIT_ERROR;
    } else {

        int imgFlags = IMG_INIT_JPG + IMG_INIT_PNG;

        if (IMG_Init(imgFlags) & imgFlags) {

            int mixFlags = MIX_INIT_OGG + MIX_INIT_MP3 + MIX_INIT_FLAC;

            if (Mix_Init(mixFlags) & mixFlags) {

                AVScreen *avScreen = new AVScreen();

                avScreen->loadConfig(testConfig());

                testLoop(avScreen);

                SDL_Delay(1000);

                delete avScreen;

                IMG_Quit();
                Mix_Quit();
                SDL_Quit();

            } else {
                return EXIT_SDL_MIX_INIT_ERROR;
            }
        } else {
            return EXIT_SDL_IMG_INIT_ERROR;
        }
    }

    return 0;
}