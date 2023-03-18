cmake_minimum_required(VERSION 3.22)
project(ftp-client LANGUAGES CXX)

add_executable(app main.cpp src/net.cpp src/common.cpp src/ftp_client.cpp)

target_include_directories(app PRIVATE header/)