cmake_minimum_required(VERSION 3.9)
project(createremotethread)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_GENERATOR_PLATFORM x86)

add_executable(createremotethread main.cpp Injector.cpp Injector.h VC.cpp VC.h VCMethod.cpp VCMethod.h CPlayer.h CPlayer.cpp MemoryReader.cpp MemoryReader.h CPed.cpp CPed.h CVehicle.cpp CVehicle.h)
add_library(dll SHARED dll.cpp)
