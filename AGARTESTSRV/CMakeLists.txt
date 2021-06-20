cmake_minimum_required(VERSION 3.7)
project(AGARTESTSRV)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /home/jafar/Qt5.7.0/5.7/gcc_64/)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)

set(SOURCE_FILES main.cpp server.h Server.cpp game_data.h game_data.cpp)
add_executable(AGARTESTSRV ${SOURCE_FILES})

target_link_libraries(AGARTESTSRV Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)