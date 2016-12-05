cmake_minimum_required(VERSION 3.0)
project(SDL_output)


# definice LINUX
if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()




# dirs for sdl2 and sdl2image are merged together on windows

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
if (WIN32)
	set(SDL2_DIR "c:/qt/SDL2-2.0.4/i686-w64-mingw32/")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32")
else () 
	set(SDL2_INCLUDE_DIR "/usr/include/SDL2")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lwiringPi")


endif ()


set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

if (WIN32)
	include_directories(${SDL2_DIR}/include)
	link_directories(${SDL2_DIR}/lib)
endif ()

if (LINUX)
#	find_package(SDL2 REQUIRED SDL2_image SDL2_mixer)
#	include_directories(${SDL2_INCLUDE_DIR})

include (FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2 SDL_Main)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)

endif ()

set(SOURCE_FILES stimulator_AVoutput/main.cpp stimulator_AVoutput/av_screen.cpp stimulator_AVoutput/av_screen.h stimulator_AVoutput/screen_config.cpp stimulator_AVoutput/screen_config.h stimulator_AVoutput/test_config.h stimulator_Events/events.cpp stimulator_Events/events.h)
add_executable(SDL_output ${SOURCE_FILES})

if  (WIN32)

	target_link_libraries(SDL_output SDL2Main SDL2_image SDL2_mixer SDL2)

endif ()

if (LINUX)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
target_link_libraries(SDL_output ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES})
endif ()
