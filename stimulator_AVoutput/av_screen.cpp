
#include "av_screen.h"



AVScreen::AVScreen() {
    window = SDL_CreateWindow("SDL_test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface( window );
}

void AVScreen::loadConfig(ScreenConfig *screenConfig) {
    width = screenConfig->width;
    height = screenConfig->height;
    if (screenConfig->fullscreen)
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    else
        SDL_SetWindowFullscreen(window,0);
    SDL_FreeSurface(surface);
    surface = SDL_GetWindowSurface( window );

    int length = screenConfig->outputs.size();
    for (int i = 0; i < length; ++i) {

    }
}
