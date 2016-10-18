
#include "av_screen.h"
#include <SDL2/SDL_image.h>

AVScreen::AVScreen() {
    window = SDL_CreateWindow("SDL_test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface( window );
}

void AVScreen::loadConfig(ScreenConfig *screenConfig) {
    width = screenConfig->width;
    height = screenConfig->height;
    SDL_SetWindowSize(window,width,height);
    if (screenConfig->fullscreen)
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    else
        SDL_SetWindowFullscreen(window,0);
    SDL_FreeSurface(surface);
    surface = SDL_GetWindowSurface( window );
    clearScreen();

    int length = screenConfig->outputs.size();

    for (int i = 0; i < length; ++i) {
        types[i] = screenConfig->outputs[i].type;
        if (types[i] == ScreenConfig::TYPE_IMAGE) {
            SDL_Surface* temp = IMG_Load(screenConfig->outputs[i].filename.c_str());
            images[i] =SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
            double ratio = (double)temp->w / (double)temp->h;
            double screenRatio = (double) width / (double) height;
            SDL_Rect* rect = new SDL_Rect();
            if (ratio<screenRatio) {
                rect->h = height;
                rect->w = (int)((double)height * ratio);
                rect->x = (width - rect->w) /2;
                rect->y = 0;

            } else {
                rect->w = width;
                rect->h = (int)((double)width / ratio);
                rect->x = 0;
                rect->y = (height - rect->h) / 2;
            }

            int val = SDL_UpperBlitScaled(temp, NULL,images[i],rect);
            SDL_FreeSurface(temp);
            delete rect;
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
    activeOutput = index;

}

void AVScreen::deactivateOutput() {
    if (types[activeOutput] == ScreenConfig::TYPE_IMAGE) {
        clearScreen();
    }
    activeOutput = NO_OUTPUT;

}
