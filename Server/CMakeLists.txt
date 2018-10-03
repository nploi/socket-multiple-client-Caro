cmake_minimum_required(VERSION 3.9)
project(caro_server)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Source.cpp Player.cpp Match.cpp SocketServer.cpp ../lib/Map.cpp)
add_executable(caro_server ${SOURCE_FILES})



