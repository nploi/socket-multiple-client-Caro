cmake_minimum_required(VERSION 3.9)
project(caro_client)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Source.cpp SocketClient.cpp ../lib/Map.cpp)
add_executable(caro_client ${SOURCE_FILES})



