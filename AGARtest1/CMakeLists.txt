cmake_minimum_required(VERSION 3.7)
project(AGARtest1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /home/jafar/Qt5.7.0/5.7/gcc_64/)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network Multimedia)

set(SOURCE_FILES main.cpp headers/Client.h sources/Client.cpp sources/Login.cpp headers/Login.h sources/connection.cpp headers/connection.h sources/GamePage.cpp headers/GamePage.h sources/InterFace.cpp headers/InterFace.h)
add_executable(AGARtest1 ${SOURCE_FILES})

target_link_libraries(AGARtest1 Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network Qt5::Multimedia)