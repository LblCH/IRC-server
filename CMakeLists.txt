cmake_minimum_required(VERSION 3.17)
project(ft_irc)

set(CMAKE_CXX_STANDARD 14)

add_executable(ft_irc main.cpp define_error.h Server.cpp Server.hpp Msg.cpp Msg.hpp Client.hpp Client.cpp Channel.cpp Channel.hpp)