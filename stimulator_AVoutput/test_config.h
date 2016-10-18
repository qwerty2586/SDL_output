//
// Created by qwerty on 18. 10. 2016.
//

#ifndef SDL_OUTPUT_TEST_CONFIG_H
#define SDL_OUTPUT_TEST_CONFIG_H


#include <SDL2/SDL_events.h>
#include "screen_config.h"
#include "av_screen.h"

ScreenConfig* testConfig() {
    ScreenConfig* r = new ScreenConfig();
    r->fullscreen = false;
    r->width = 640;
    r->height = 480;

    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_IMAGE,"output_test/0.bmp"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_IMAGE,"output_test/1.jpg"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_IMAGE,"output_test/2.jpg"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_IMAGE,"output_test/3.png"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_IMAGE,"output_test/4.jpg"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_IMAGE,"output_test/5.jpg"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_AUDIO,"output_test/6.mp3"});
    r->outputs.push_back((ScreenConfig::Output) {true,ScreenConfig::TYPE_AUDIO,"output_test/7.mp3"});

    return r;

}

void testLoop(AVScreen* avScreen) {

    bool exitLoop = false;
    for (SDL_Event event; !exitLoop;) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_0: { avScreen->activateOutput(0); break; }
                case SDLK_1: { avScreen->activateOutput(1); break; }
                case SDLK_2: { avScreen->activateOutput(2); break; }
                case SDLK_3: { avScreen->activateOutput(3); break; }
                case SDLK_4: { avScreen->activateOutput(4); break; }
                case SDLK_5: { avScreen->activateOutput(5); break; }
                case SDLK_6: { avScreen->activateOutput(6); break; }
                case SDLK_7: { avScreen->activateOutput(7); break; }
                case SDLK_c: { avScreen->clearScreen();     break; }

                case SDLK_q: { exitLoop = true; break; }
            }
        }
    }

};


#endif //SDL_OUTPUT_TEST_CONFIG_H
