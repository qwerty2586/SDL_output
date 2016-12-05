#include <SDL2/SDL_events.h>
#include <iostream>
#include "events.h"
#include <wiringPi.h>

bool Events::start() {
    if (running) return false;
    if (gpio_event_type ==((Uint32)-1)) gpio_event_type = SDL_RegisterEvents(1);
    gpio_thread = std::thread([&]() { gpio_loop(); });
    gpio_thread.detach();
    wiringPiSetup();
    auto lmbd = wiringPiISR(0,INT_EDGE_BOTH,[]{

    });
    return true;
}

void Events::stop() {
    if (!running) return;

    return;
}


int Events::get_event() {
    SDL_Event event;
    while(SDL_WaitEvent(&event)){
        std::cout << ".";
        if(event.type == SDL_QUIT  ||  event.key.keysym.scancode == KEY_EXIT_SCANCODE) {
            return EVENT_CODES::EXIT_KEY;
            break;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case KEY_0: { key_now=EVENT_CODES::KEY_EVENT_0; break; }
                case KEY_1: { key_now=EVENT_CODES::KEY_EVENT_1; break; }
                case KEY_2: { key_now=EVENT_CODES::KEY_EVENT_2; break; }
                case KEY_3: { key_now=EVENT_CODES::KEY_EVENT_3; break; }
                case KEY_4: { key_now=EVENT_CODES::KEY_EVENT_4; break; }
                case KEY_5: { key_now=EVENT_CODES::KEY_EVENT_5; break; }
                case KEY_6: { key_now=EVENT_CODES::KEY_EVENT_6; break; }
                case KEY_7: { key_now=EVENT_CODES::KEY_EVENT_7; break; }
            }
            if (key_now != key_last) {
                key_last = key_now;
                return key_now;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case KEY_CLEAR: {
                    return EVENT_CODES::KEY_EVENT_CLEAR_SCREEN; }
                default:  {
                    key_now = EVENT_CODES::KEY_EVENT_END;
                    if (key_now != key_last) {
                        key_last = key_now;
                        return key_now;
                    }
                    break;
                }
            }
        }
        else if (event.type == gpio_event_type) {
            // do something
        }

    }
}

void Events::gpio_loop() {

    // tady budou gpio eventy

}

Events &Events::instance() {
    static Events INSTANCE;
    return INSTANCE;
}
