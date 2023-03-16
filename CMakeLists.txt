cmake_minimum_required(VERSION 3.22)
project(ftp-client LANGUAGES CXX)

add_executable(app main.cpp src/net.cpp)
target_include_directories(app PRIVATE header/)