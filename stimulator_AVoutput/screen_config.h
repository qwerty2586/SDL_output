#ifndef SDL_OUTPUT_SCREEN_CONFIG_H
#define SDL_OUTPUT_SCREEN_CONFIG_H

#include <c++/string>
#include <c++/vector>

class ScreenConfig {

public:
    static const int TYPE_UNKNOWN = 0;
    static const int TYPE_IMAGE = 1;
    static const int TYPE_AUDIO = 2;
    static const int TYPE_VIDEO = 3;
    static const int TYPE_OTHER = 4;


    bool fullscreen;
    int width,height;
    double volume;


    struct Output {
        bool enabled;
        int type;
        std::string filename;
    };
    std::vector<Output> outputs;

};

#endif //SDL_OUTPUT_SCREEN_CONFIG_H
