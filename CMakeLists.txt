cmake_minimum_required(VERSION 3.17)
project(learn-c-untime C)

set(CMAKE_C_STANDARD 99)

add_executable(server tcp/server.c)
add_executable(client tcp/client.c)