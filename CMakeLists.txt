# CMakeLists
project(AsmVsZombies)

cmake_minimum_required (VERSION 3.0)

add_definitions(-std=c++17)

set(CMAKE_CXX_COMPILER "g++")

# build libavz.dll
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

aux_source_directory(./src avz_srcs)
add_library(avz_1_0_0_1051_en MODULE
        ${avz_srcs}
)
target_compile_definitions(avz_1_0_0_1051_en PUBLIC VERSION=V_1_0_0_1051_EN)


# build injector.exe
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_CXX_FLAGS -static)
include_directories(./injector/inc)
aux_source_directory(./injector/src injector_srcs)
add_executable(injector ${injector_srcs})
