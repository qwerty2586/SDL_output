#ifndef SDL_OUTPUT_SCREEN_CONFIG_H
#define SDL_OUTPUT_SCREEN_CONFIG_H

#include <string>
#include <vector>

#define DEFAULT_FULLSCREEN false
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFAULT_TEST_ENABLED false

class ScreenConfig {

public:

    // mozne typu vystupu zatim implementuji TYPE_IMAGE a TYPE_AUDIO
    static const int TYPE_UNKNOWN = 0;
    static const int TYPE_IMAGE = 1;
    static const int TYPE_AUDIO = 2;
    static const int TYPE_VIDEO = 3;
    static const int TYPE_OTHER = 4;

    static const std::string XML_TYPE_UNKNOWN;
    static const std::string XML_TYPE_IMAGE;
    static const std::string XML_TYPE_AUDIO;
    static const std::string XML_TYPE_VIDEO;
    static const std::string XML_TYPE_OTHER;


    bool fullscreen = DEFAULT_FULLSCREEN;
    bool test_enabled = DEFAULT_TEST_ENABLED;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    bool hw = true;
    double volume;


    // prepravka s konfiguraci jednoho vystupu
    struct Output {
        bool enabled;
        int type;
        std::string filename;
    };

    std::vector<Output> outputs;

    void load_outputs_xml(char *xml_filename);


};

#endif //SDL_OUTPUT_SCREEN_CONFIG_H
