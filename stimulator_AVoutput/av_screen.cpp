
#include "av_screen.h"
#include <SDL2/SDL_image.h>



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
        types[i] = screenConfig->outputs[i].type;
        if (types[i] == ScreenConfig::TYPE_IMAGE) {
            images[i] = IMG_Load(screenConfig->outputs[i].filename.c_str());
        }

    }
}



AVScreen::~AVScreen() {
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_free(window);

}

void AVScreen::clearScreen() {
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0x00, 0x00, 0x00 ) );
    SDL_UpdateWindowSurface( window );
}

void AVScreen::activateOutput(int index) {
    if (types[index] == ScreenConfig::TYPE_IMAGE) {
        SDL_BlitSurface(images[index], nullptr, surface, nullptr);
        SDL_UpdateWindowSurface(window);
    }

}
