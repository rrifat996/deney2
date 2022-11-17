cmake_minimum_required(VERSION 3.23)
project(deneme)

set(CMAKE_CXX_STANDARD 14)

add_executable(deneme main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(deneme sfml-system sfml-window sfml-graphics sfml-audio)