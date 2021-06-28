# CMakeLists
project(AsmVsZombies)

cmake_minimum_required (VERSION 3.0)

add_definitions(-std=c++17)

set(CMAKE_CXX_COMPILER "g++")

add_compile_definitions(VERSION_1_0_0_1051_EN)

# build libavz.dll
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
# include_directories(include)
aux_source_directory(./src avz_srcs)
add_library(avz MODULE
        #src/pvz/base.cpp
        ${avz_srcs}
)
target_include_directories(avz PUBLIC include)


# build injector.exe
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_CXX_FLAGS -static)
include_directories(./injector/inc)
aux_source_directory(./injector/src injector_srcs)
add_executable(injector ${injector_srcs})
