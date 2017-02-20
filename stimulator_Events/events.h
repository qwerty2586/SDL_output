/**
 * \class Events
 * \ingroup stimulator_Events
 *
 * Třída obsluhuje vstupy z klávesnice a z GPIO u RASPBERRY PI.
 * Může být rozšířena aby obsluhovala další zdroje, třeba linuxové signály.
 * Používá SDL_WaitEvent() k blokujícímu čekání na vstup. Externí vstupy
 * jako GPIO můžou použít SDL_PushEven(). Tato funkce obsahuje thread-safe
 * mechanismus a je možná použít z kteréhokoli vlákna.
 *
 * K připojení GPIO využíváme knihovnu wiringPi a její funkci wiringPiISR(),
 * která generuje přerušení na hraně pinu.
 *
 * Číslování pinů ve wiring PI odpovídá následujíécím pinům
 * ze schématu níže

 *  wiringPi 0 = pin 11 = GPIO 17
 *  wiringPi 1 = pin 12 = GPIO 18
 *  wiringPi 2 = pin 13 = GPIO 27
 *  wiringPi 3 = pin 15 = GPIO 22

 *  detailní schéma zapojení je na adrese http://wiringpi.com/pins/

           RASPI 2 B+ PINOUT

               Pin 1 Pin2
           +3V3 [ ] [ ] +5V
 SDA1 / GPIO  2 [ ] [ ] +5V
 SCL1 / GPIO  3 [ ] [ ] GND
        GPIO  4 [ ] [ ] GPIO 14 / TXD0
            GND [ ] [ ] GPIO 15 / RXD0
        GPIO 17 [ ] [ ] GPIO 18
        GPIO 27 [ ] [ ] GND
        GPIO 22 [ ] [ ] GPIO 23
           +3V3 [ ] [ ] GPIO 24
 MOSI / GPIO 10 [ ] [ ] GND
 MISO / GPIO  9 [ ] [ ] GPIO 25
 SCLK / GPIO 11 [ ] [ ] GPIO  8 / CE0#
            GND [ ] [ ] GPIO  7 / CE1#
ID_SD / GPIO  0 [ ] [ ] GPIO  1 / ID_SC
        GPIO  5 [ ] [ ] GND
        GPIO  6 [ ] [ ] GPIO 12
        GPIO 13 [ ] [ ] GND
 MISO / GPIO 19 [ ] [ ] GPIO 16 / CE2#
        GPIO 26 [ ] [ ] GPIO 20 / MOSI
            GND [ ] [ ] GPIO 21 / SCLK
             Pin 39 Pin 40

 */


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

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3

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

// globální promněná s číslem eventu
static Uint32 gpio_event_type = ((Uint32) -1);

class Events {

public:
    bool start();

    void stop();

    static Events &instance();

    /// čekání v hlavním vlákně
    int get_event();

protected:
    Events() {};

private:
    /// nastavaví interupt z GPIO
    void setup_interrupt();

    int key_now = -1000;
    int key_last = -1000;
    bool running = false;
};


#endif //SDL_OUTPUT_EVENTS_H
