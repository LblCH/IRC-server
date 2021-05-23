cmake_minimum_required(VERSION 3.19)
project(IRCC)

set(CMAKE_CXX_STANDARD 14)

add_executable(IRCC main.cpp Channel.cpp Client.cpp Msg.cpp Server.cpp)