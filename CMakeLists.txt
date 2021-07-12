project(AsmVsZombies LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/PvZLib)

# build libavz.dll
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(avz_sources
        src/dllmain.cpp
        )

add_library(avz_1_0_0_1051_en MODULE ${avz_sources})
target_link_libraries(avz_1_0_0_1051_en pvz_1_0_0_1051_en)

# build injector.exe
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS -static)
include_directories(./injector/inc)
aux_source_directory(./injector/src injector_srcs)
add_executable(injector ${injector_srcs})
