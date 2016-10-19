#ifndef SDL_OUTPUT_AV_SCREEN_H
#define SDL_OUTPUT_AV_SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "screen_config.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#define OUTPUT_MAX_COUNT 8

class AVScreen  {
public:
    explicit AVScreen();
    ~AVScreen();
    void loadConfig(ScreenConfig *screenConfig);
    void clearScreen();

    void activateOutput(int index);
    static constexpr int NO_OUTPUT = -1;

private:

    SDL_Window *window;
    SDL_Surface *surface;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    SDL_Surface *images[OUTPUT_MAX_COUNT];
    Mix_Music *audios[OUTPUT_MAX_COUNT];
    int types[OUTPUT_MAX_COUNT];
    int activeOutput = NO_OUTPUT;

};

#endif //SDL_OUTPUT_AV_SCREEN_H
