/**
 * \ingroup stimulator_AVoutput
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
#include <getopt.h>
#include "av_screen.h"
#include "test_config.h"

#define EXIT_NO_OUTPUT_LIST 100

#define EXIT_SDL_INIT_ERROR 200
#define EXIT_SDL_IMG_INIT_ERROR 201
#define EXIT_SDL_MIX_INIT_ERROR 202
static struct option longOpts[] = {
        {"fullscreen", no_argument,       NULL, 'f'},
        {"windowed",   no_argument,       NULL, 'w'},
        {"window",     no_argument,       NULL, 'w'},
        {"width",      required_argument, NULL, 'x'},
        {"height",     required_argument, NULL, 'y'},
        {"config",     required_argument, NULL, 'c'},
        {"test",       no_argument,       NULL,  't'},
        {"help",       no_argument,       NULL, 'h'},
        {NULL,         no_argument,       NULL, 0}
};

int main(int argc, char *argv[]) {




    ScreenConfig *screenConfig = new ScreenConfig();
    int c;
    char *config_filename = NULL;
    while ((c = getopt_long(argc, argv, "fwx:y:c:th", longOpts, NULL)) != -1) {
        switch (c) {
            case 'f':
                screenConfig->fullscreen = true;
                break;
            case 'w':
                screenConfig->fullscreen = false;
                break;
            case 'x':
                screenConfig->width = atoi(optarg);
                break;
            case 'y':
                screenConfig->height = atoi(optarg);
                break;
            case 'c' :
                config_filename = optarg;
                break;
            case 't' :
                screenConfig->test_enabled = true;
                break;
            case 'h': // print help;
                break;
        }
    }


    if (!config_filename) {
        std::cout << "Config file must be specified!" << std::endl;
        return EXIT_NO_OUTPUT_LIST;
    }

    screenConfig->load_outputs_xml(config_filename); // nacte z XML

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
        return EXIT_SDL_INIT_ERROR;
    } else {

        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

        if (IMG_Init(imgFlags) & imgFlags) {
            if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != -1) {
                int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC;
                int initted=Mix_Init(mixFlags);

                if ((mixFlags&initted) == mixFlags) {

                    AVScreen *avScreen = new AVScreen(screenConfig->width,screenConfig->height,screenConfig->fullscreen);
                    avScreen->loadConfig(screenConfig);

                    testLoop(avScreen);
                    delete avScreen;
                    delete screenConfig;

                    IMG_Quit();
                    Mix_Quit();
                    SDL_Quit();

                } else {
                    std::cout << "SDL_mixer error: " << Mix_GetError() << std::endl;
                    return EXIT_SDL_MIX_INIT_ERROR;
                }
            } else {
                fprintf(stderr, "Mix_OpenAudio() error: %s\n", SDL_GetError());
                return EXIT_SDL_MIX_INIT_ERROR;
            }


        } else {
            std::cout << "SDL_image error: " << IMG_GetError() << std::endl;
            return EXIT_SDL_IMG_INIT_ERROR;
        }
    }

    return 0;
}