#ifndef SDL_OUTPUT_AV_SCREEN_H
#define SDL_OUTPUT_AV_SCREEN_H

class AVScreen  {
public:
    explicit AVScreen();

private:
    bool destroy_sdl_after_kill;
};

#endif //SDL_OUTPUT_AV_SCREEN_H
