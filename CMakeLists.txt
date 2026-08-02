cmake_minimum_required(VERSION 3.21...3.25)
project(harmonic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SndFile CONFIG REQUIRED)

find_path(AUBIO_INCLUDE_DIR NAMES aubio/aubio.h REQUIRED)
find_library(AUBIO_LIBRARY NAMES aubio REQUIRED)

add_executable(harmonic src/main.cpp)

target_link_libraries(harmonic PRIVATE SndFile::sndfile)
target_include_directories(harmonic PRIVATE ${AUBIO_INCLUDE_DIR})
target_link_libraries(harmonic PRIVATE ${AUBIO_LIBRARY})
