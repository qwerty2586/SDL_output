#ifndef SDL_OUTPUT_AV_SCREEN_H
#define SDL_OUTPUT_AV_SCREEN_H

#include <SDL2/SDL.h>
#include "screen_config.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

class AVScreen  {
public:
    explicit AVScreen();
    ~AVScreen();
    void loadConfig(ScreenConfig *screenConfig);

private:
    SDL_Window* window;
    SDL_Surface* surface;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;


};

#endif //SDL_OUTPUT_AV_SCREEN_H
