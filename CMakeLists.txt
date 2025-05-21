cmake_minimum_required(VERSION 3.30)
project(tt_fb_mpmc)

set(CMAKE_CXX_STANDARD 20)

add_executable(tt_fb_mpmc main.cpp
        utils/Worker.cpp
        utils/Worker.h
        utils/SharedQueue.h)
