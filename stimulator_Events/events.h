#ifndef SDL_OUTPUT_EVENTS_H
#define SDL_OUTPUT_EVENTS_H


#include <thread>

#define KEY_0 SDLK_0
#define KEY_1 SDLK_1
#define KEY_2 SDLK_2
#define KEY_3 SDLK_3
#define KEY_4 SDLK_4
#define KEY_5 SDLK_5
#define KEY_6 SDLK_6
#define KEY_7 SDLK_7
#define KEY_CLEAR SDLK_c
#define KEY_EXIT_SCANCODE SDL_SCANCODE_ESCAPE

namespace EVENT_CODES {
    static const int NOTHING = -100;

    static const int HW_CLOSE = -1;
    static const int EXIT_KEY = -2;

    static const int GPIO_EVENT_0 = 0;
    static const int GPIO_EVENT_1 = 1;
    static const int GPIO_EVENT_2 = 2;
    static const int GPIO_EVENT_3 = 3;
    static const int GPIO_EVENT_4 = 4;
    static const int GPIO_EVENT_5 = 5;
    static const int GPIO_EVENT_6 = 6;
    static const int GPIO_EVENT_7 = 7;

    static const int GPIO_EVENT_END = -3;

    static const int KEY_EVENT_0 = 10;
    static const int KEY_EVENT_1 = 11;
    static const int KEY_EVENT_2 = 12;
    static const int KEY_EVENT_3 = 13;
    static const int KEY_EVENT_4 = 14;
    static const int KEY_EVENT_5 = 15;
    static const int KEY_EVENT_6 = 16;
    static const int KEY_EVENT_7 = 17;

    static const int KEY_EVENT_END = -4;

    static const int KEY_EVENT_CLEAR_SCREEN = -5;


}



class Events {

public:
    bool start();
    void stop();
    Uint32 gpio_event_type = ((Uint32)-1);
    static Events& instance();

    int get_event(); // cekaci musi bezet v main threadu

protected:
    Events() {};

private:
    std::thread gpio_thread;
    void gpio_loop();
    int key_now = -1000;
    int key_last = -1000;
    bool running = false;
};



#endif //SDL_OUTPUT_EVENTS_H
