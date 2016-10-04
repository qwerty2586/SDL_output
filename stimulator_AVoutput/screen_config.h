#ifndef SDL_OUTPUT_SCREEN_CONFIG_H
#define SDL_OUTPUT_SCREEN_CONFIG_H

#include <c++/string>
#include <c++/vector>

class ScreenConfig {

public:

    bool fullscreen;
    int width,height;
    double volume;

    std::vector<Output> outputs;
    struct Output {
        bool enabled;
        int type;
        std::string filename;
    }

};

#endif //SDL_OUTPUT_SCREEN_CONFIG_H
