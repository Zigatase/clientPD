cmake_minimum_required(VERSION 3.25)
project(clientPD)

set(CMAKE_CXX_STANDARD 17)

link_libraries(ws2_32 wsock32)

add_executable(clientPD src/main.cpp
        src/client/client.h
        src/client/client.cpp
        )
