
#ifndef SDL_OUTPUT_TEST_CONFIG_H
#define SDL_OUTPUT_TEST_CONFIG_H


#include <SDL2/SDL_events.h>
#include "screen_config.h"
#include "av_screen.h"
#include "../stimulator_Events/events.h"

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

    Events &events =  Events::instance();
    events.start();
    while(1) {
        int event = events.get_event();
        switch (event) {
            case EVENT_CODES::KEY_EVENT_0:
            case EVENT_CODES::KEY_EVENT_1:
            case EVENT_CODES::KEY_EVENT_2:
            case EVENT_CODES::KEY_EVENT_3:
            case EVENT_CODES::KEY_EVENT_4:
            case EVENT_CODES::KEY_EVENT_5:
            case EVENT_CODES::KEY_EVENT_6:
            case EVENT_CODES::KEY_EVENT_7: avScreen->activateOutput(event - EVENT_CODES::KEY_EVENT_0);
                break;
            case EVENT_CODES::KEY_EVENT_END: avScreen->activateOutput(AVScreen::NO_OUTPUT);
                break;
            case EVENT_CODES::EXIT_KEY   :
                return;

        }
    }


/*

    bool exitLoop = false;
    SDL_Event event;

    int key_last=-2;
    int key_now =-2;

    while (!exitLoop) {
       // SDL_WaitEvent()
        while(SDL_WaitEvent(&event)){
            std::cout << ".";
            if(event.type == SDL_QUIT  ||  event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                return ;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_0: { key_now=0; break; }
                    case SDLK_1: { key_now=1; break; }
                    case SDLK_2: { key_now=2; break; }
                    case SDLK_3: { key_now=3; break; }
                    case SDLK_4: { key_now=4; break; }
                    case SDLK_5: { key_now=5; break; }
                    case SDLK_6: { key_now=6; break; }
                    case SDLK_7: { key_now=7; break; }
                }
                if (key_now != key_last) {
                    avScreen->activateOutput(key_now);
                    key_last = key_now;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {

                    case SDLK_c: { avScreen->clearScreen();     break; }
                    case SDLK_q: { exitLoop = true; break; }
                    default:  {
                        key_now = AVScreen::NO_OUTPUT;
                        if (key_now != key_last) {
                            avScreen->activateOutput(key_now);
                            key_last = key_now;
                        }
                        break;
                    }
                }
            }
        }

    }
*/
};


#endif //SDL_OUTPUT_TEST_CONFIG_H
