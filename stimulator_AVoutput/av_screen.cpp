
#include "av_screen.h"
#include <SDL2/SDL_image.h>
#include <c++/iostream>

AVScreen::AVScreen() {
    window = SDL_CreateWindow("AVScreen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(window);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
}

void AVScreen::loadConfig(ScreenConfig *screenConfig) {
    width = screenConfig->width;
    height = screenConfig->height;
    SDL_SetWindowSize(window, width, height);
    if (screenConfig->fullscreen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    else
        SDL_SetWindowFullscreen(window, 0);
    SDL_FreeSurface(surface);
    surface = SDL_GetWindowSurface(window);
    clearScreen();

    for (int i = 0; i < OUTPUT_MAX_COUNT; ++i) {
        images[i] = NULL;
        audios[i] = NULL;
    }

    int length = screenConfig->outputs.size();

    for (int i = 0; i < length; ++i) {
        types[i] = screenConfig->outputs[i].type;
        if (types[i] == ScreenConfig::TYPE_IMAGE) {
            SDL_Surface *temp = IMG_Load(screenConfig->outputs[i].filename.c_str());
            images[i] = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
            double ratio = (double) temp->w / (double) temp->h;
            double screenRatio = (double) width / (double) height;
            SDL_Rect *rect = new SDL_Rect();
            if (ratio < screenRatio) {
                rect->h = height;
                rect->w = (int) ((double) height * ratio);
                rect->x = (width - rect->w) / 2;
                rect->y = 0;
            } else {
                rect->w = width;
                rect->h = (int) ((double) width / ratio);
                rect->x = 0;
                rect->y = (height - rect->h) / 2;
            }
            SDL_UpperBlitScaled(temp, NULL, images[i], rect);
            if (screenConfig->test_enabled) {
                SDL_Surface *white_surface = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
                SDL_FillRect(white_surface,NULL,0xFFFFFFFF);

                SDL_Rect *white_rect = new SDL_Rect();
                white_rect->w=200;
                white_rect->h=200;
                white_rect->x = images[i]->w - 250;
                white_rect->y = images[i]->h - 250;

                SDL_BlitSurface(white_surface,NULL,images[i],white_rect);
                SDL_FreeSurface(white_surface);
                delete white_rect;
            }
            SDL_FreeSurface(temp);
            delete rect;
        }
        if (types[i] == ScreenConfig::TYPE_AUDIO) {
            audios[i] = Mix_LoadMUS(screenConfig->outputs[i].filename.c_str());
        }

    }
}


AVScreen::~AVScreen() {
    if (Mix_PlayingMusic()) Mix_PauseMusic();
    for (int i = 0; i < OUTPUT_MAX_COUNT; ++i) {
        if (images[i]) SDL_FreeSurface(images[i]);
        if (audios[i]) Mix_FreeMusic(audios[i]);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_free(window);
    Mix_CloseAudio();

}

void AVScreen::clearScreen() {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(window);
}

void AVScreen::activateOutput(int index) {
    if (index == NO_OUTPUT) {
        if (types[activeOutput] == ScreenConfig::TYPE_IMAGE) {
            clearScreen();
        } else if (types[activeOutput] == ScreenConfig::TYPE_AUDIO) {
            //Mix_PauseMusic();
        }

    } else if (types[index] == ScreenConfig::TYPE_IMAGE) {
        SDL_BlitSurface(images[index], nullptr, surface, nullptr);
        SDL_UpdateWindowSurface(window);
    } else if (types[index] == ScreenConfig::TYPE_AUDIO) {
        Mix_PlayMusic(audios[index], 1);
    }
    activeOutput = index;

}

