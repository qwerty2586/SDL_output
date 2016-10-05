cmake_minimum_required(VERSION 3.5)
project(SDL_output)


set(SDL2_DIR "c:/qt/SDL2-2.0.4/i686-w64-mingw32/")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${SDL2_DIR}/include)
link_directories(${SDL2_DIR}/lib)

set(SOURCE_FILES stimulator_AVoutput/main.cpp stimulator_AVoutput/av_screen.cpp stimulator_AVoutput/av_screen.h stimulator_AVoutput/screen_config.cpp stimulator_AVoutput/screen_config.h)
add_executable(SDL_output ${SOURCE_FILES})

target_link_libraries(SDL_output SDL2Main SDL2)
