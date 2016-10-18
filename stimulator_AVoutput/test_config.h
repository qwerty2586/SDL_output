
#ifndef SDL_OUTPUT_TEST_CONFIG_H
#define SDL_OUTPUT_TEST_CONFIG_H


#include <SDL2/SDL_events.h>
#include "screen_config.h"
#include "av_screen.h"

ScreenConfig* testConfig() {
    ScreenConfig* r = new ScreenConfig();
    r->fullscreen = false;
    r->width = 800  ;
    r->height = 600 ;

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
    SDL_Event event;

    int last=-2;
    int now =-2;
    while (!exitLoop) {
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT  ||  event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                return ;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_0: { now=0; break; }
                    case SDLK_1: { now=1; break; }
                    case SDLK_2: { now=2; break; }
                    case SDLK_3: { now=3; break; }
                    case SDLK_4: { now=4; break; }
                    case SDLK_5: { now=5; break; }
                    case SDLK_6: { now=6; break; }
                    case SDLK_7: { now=7; break; }
                }
                if (now != last) {
                    avScreen->activateOutput(now);
                    last = now;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {

                    case SDLK_c: { avScreen->clearScreen();     break; }
                    case SDLK_q: { exitLoop = true; break; }
                    default:  {
                        now = AVScreen::NO_OUTPUT;
                        if (now != last) {
                            avScreen->activateOutput(now);
                            last = now;
                        }

                        break; }
                }
            }
        }

    }

};


#endif //SDL_OUTPUT_TEST_CONFIG_H
