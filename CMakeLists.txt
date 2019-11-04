cmake_minimum_required(VERSION 3.15)
project(network_lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(network_lab1 main.cpp dealConnect.cpp dealConnect.h web_connect.h web_mes.hpp)