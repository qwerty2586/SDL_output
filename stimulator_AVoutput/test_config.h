
#ifndef SDL_OUTPUT_TEST_CONFIG_H
#define SDL_OUTPUT_TEST_CONFIG_H


#include <SDL2/SDL_events.h>
#include "screen_config.h"
#include "av_screen.h"
#include "../stimulator_Events/events.h"


/// testovaci konfigurace pomoci prilozenych souboru
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
/// hlavni programova smycka, preklada SDL eventy na cinosti obrazovky
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
            case EVENT_CODES::GPIO_EVENT_0:
            case EVENT_CODES::GPIO_EVENT_1:
            case EVENT_CODES::GPIO_EVENT_2:
            case EVENT_CODES::GPIO_EVENT_3:
            case EVENT_CODES::GPIO_EVENT_4:
            case EVENT_CODES::GPIO_EVENT_5:
            case EVENT_CODES::GPIO_EVENT_6:
            case EVENT_CODES::GPIO_EVENT_7: avScreen->activateOutput(event - EVENT_CODES::GPIO_EVENT_0);
                break;
            case EVENT_CODES::GPIO_EVENT_END: avScreen->activateOutput(AVScreen::NO_OUTPUT);
                break;
            case EVENT_CODES::EXIT_KEY   :
                return;
        }
    }
};


#endif //SDL_OUTPUT_TEST_CONFIG_H
