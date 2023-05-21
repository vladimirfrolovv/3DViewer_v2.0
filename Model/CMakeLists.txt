cmake_minimum_required(VERSION 3.22)
project(Model)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Model
        model.cc
        model.h
        ../Controller/controller.cc
        ../Controller/controller.h)
