
#include "av_screen.h"
#include <SDL2/SDL_image.h>
#include <iostream>


AVScreen::AVScreen(int width, int height, bool fullscreen, bool hw) {
    this->width = width;
    this->height = height;
    this->hw = hw;
    Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL : 0;
    window = SDL_CreateWindow("SDL_output", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (hw) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        surface = SDL_GetWindowSurface(window);
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
    }



}

void AVScreen::loadConfig(ScreenConfig *screenConfig) {
    clearScreen();
    for (int i = 0; i < OUTPUT_MAX_COUNT; ++i) {
        audios[i] = nullptr;
        images[i] = nullptr;
        images_s[i] = nullptr;
    }

    int length = screenConfig->outputs.size();

    for (int i = 0; i < length; ++i) {
        types[i] = screenConfig->outputs[i].type;
        if (types[i] == ScreenConfig::TYPE_IMAGE) {
            SDL_Surface *img = IMG_Load(screenConfig->outputs[i].filename.c_str());
            if (!img) {
                // when cant load image fill with red color
                std::cout << "IMG_Load error: " << IMG_GetError() << std::endl;
                img = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
                SDL_FillRect(img, NULL, SDL_MapRGB(img->format, 255, 0, 0));
            }
            SDL_Surface *temp = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
            double ratio = (double) img->w / (double) img->h;
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
            SDL_UpperBlitScaled(img, NULL, temp, rect);
            if (screenConfig->test_enabled) {
                SDL_Surface *white_surface = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
                SDL_FillRect(white_surface, NULL, 0xFFFFFFFF);

                SDL_Rect *white_rect = new SDL_Rect();
                white_rect->w = 200;
                white_rect->h = 200;
                white_rect->x = temp->w - 250;
                white_rect->y = temp->h - 250;

                SDL_BlitSurface(white_surface, NULL, temp, white_rect);
                SDL_FreeSurface(white_surface);
                delete white_rect;
            }

            if (hw) {
                images[i] = SDL_CreateTextureFromSurface(renderer, temp);
            } else {
                images_s[i] = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
                SDL_BlitSurface(temp, nullptr, images_s[i], nullptr);
            }
            SDL_FreeSurface(img);
            SDL_FreeSurface(temp);
            delete rect;
        }
        if (types[i] == ScreenConfig::TYPE_AUDIO) {
            audios[i] = Mix_LoadMUS(screenConfig->outputs[i].filename.c_str());
            if (!audios[i]) {
                std::cout << "Mix_LoadMUS error: " << Mix_GetError() << std::endl;
            }
        }

    }



}


AVScreen::~AVScreen() {
    if (Mix_PlayingMusic()) Mix_PauseMusic();
    for (int i = 0; i < OUTPUT_MAX_COUNT; ++i) {
        if (images[i]) SDL_DestroyTexture(images[i]);
        if (audios[i]) Mix_FreeMusic(audios[i]);
        if (images_s[i]) SDL_FreeSurface(images_s[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();

}

void AVScreen::clearScreen() {
    if (hw) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    } else {
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
        SDL_UpdateWindowSurface(window);
    }
}

void AVScreen::activateOutput(int index) {
    if (index == NO_OUTPUT) {
        if (types[activeOutput] == ScreenConfig::TYPE_IMAGE) {
            clearScreen();
        } else if (types[activeOutput] == ScreenConfig::TYPE_AUDIO) {
            //Mix_PauseMusic();
        }
    } else if (types[index] == ScreenConfig::TYPE_IMAGE) {
        if (hw) {
            SDL_RenderCopy(renderer,images[index],NULL,NULL);
            SDL_RenderPresent(renderer);
        } else {
            SDL_BlitSurface(images_s[index], nullptr, surface, nullptr);
            SDL_UpdateWindowSurface(window);
            //SDL_RenderPresent(renderer);
        }
    } else if (types[index] == ScreenConfig::TYPE_AUDIO) {
        if (!audios[index]) {
            Mix_FadeOutMusic(0);
        } else {
            Mix_PlayMusic(audios[index], 1);
        }
    }
    activeOutput = index;

}

