/**
 * Trida spravuje okno, ktere zobrazuje vystupy.
 */

#ifndef SDL_OUTPUT_AV_SCREEN_H
#define SDL_OUTPUT_AV_SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "screen_config.h"

/// defaultni rozliseni
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

/// celkovy pocet vystupu
#define OUTPUT_MAX_COUNT 8

class AVScreen  {
public:
    explicit AVScreen();
    ~AVScreen();
    /// nacteni konfigurace, seznamu vstupu, rozliseni, etc.
    void loadConfig(ScreenConfig *screenConfig);
    void clearScreen();

    /// prepnuti vystupu, NO_OUTPUT znamena zadny vystup zadny zvuk
    void activateOutput(int index);
    static constexpr int NO_OUTPUT = -1;

private:

    SDL_Window *window;
    SDL_Renderer *renderer;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    Mix_Music *audios[OUTPUT_MAX_COUNT];
    SDL_Texture *images[OUTPUT_MAX_COUNT];
    int types[OUTPUT_MAX_COUNT];
    int activeOutput = NO_OUTPUT;

};

#endif //SDL_OUTPUT_AV_SCREEN_H
